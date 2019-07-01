#include "msg.hpp"


msg_gen::msg_gen(esp_mqtt_client_handle_t *mqtt_client_){
    mqttclient = mqtt_client_;
    //topic_list_pub = &topic_buff_pub[0];
    //topic_list_sub = &topic_buff_sub[0];
}


template <typename T>
void msg_gen::pub_multi(string *topic_, T *t, uint32_t vec_size){
    if(vec_size == 0)
      vec_size = 1;
    uint32_t name_cnt = 0;
    uint32_t num_arry_cnt = 0;

    name_cnt = sizeof(t->names)/sizeof(t->names[0]);
    cout << name_cnt << "\n";

    for(uint32_t i = 0; i < name_cnt; i++){
        if(*t->names[i] == '#'){
            num_arry_cnt++;
        }
    }

   //cout << "\n VEC SIZE: " << vec_size;
   //cout << "\n num_arry_cnt SIZE: " << num_arry_cnt;

   std::stringstream ss_;

   for (uint32_t *p = (uint32_t*)t;reinterpret_cast<uintptr_t>(p) < reinterpret_cast<uintptr_t>(t->names);p++){

        //const char *topic_ = *topic[data_cnt].c_str();
        //const char *pub_data = *data.c_str();

        if(reinterpret_cast<uintptr_t>(p)+(MAX_VEC_SIZE)*(4*num_arry_cnt)+4 < reinterpret_cast<uintptr_t>(t->names)){
            //cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
            //cout << "\nTOPIC: "<< *topic++;
            //cout << "\nDATA : "<< *p;
            ss_ << *p;
            push_pub(*topic_++, ss_.str());
            ss_.str("");

        }else{
            for(uint32_t i = 0; i < vec_size; i++){
                //cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
                //cout << "\nvecTOPIC: "<< *topic++;
                //cout << "\nvecDATA : "<< *p++;
                ss_ << *p++;
                push_pub(*topic_++, ss_.str());
                ss_.str("");

            }
            cout << "\n----\n";
            for(uint32_t i = 0; i < (MAX_VEC_SIZE-vec_size); i++){
                topic_++;
                p++;
            }
        }
    }
}

void msg_gen::creat_topics(string *ret_data,string base_topic, const char* names_[], uint32_t size_){

  uint32_t name_cnt = 0;

  name_cnt = size_/8;
  //cout << "\n CREATE TOPICS "<< name_cnt << "\n";

  for(uint32_t i = 0; i < name_cnt; i++){
    std::stringstream ss_;
    if(*names_[i] == '#'){
        i++;
        for(uint32_t j = 0; j < MAX_VEC_SIZE; j++){
            ss_ << base_topic <<names_[i]<<"/"<< j;
            //cout << ss_.str() << "\n";
            *ret_data++ = ss_.str();
            ss_.str("");
        }
    }else{
        ss_ << base_topic << names_[i];
        //cout << ss_.str() << "\n";;
        *ret_data++ = ss_.str();
    }

  }

}



 void msg_gen::push_pub(std::string topic, std::string data){
   int msg_id = 0;
   const char *topic_ = topic.c_str();
   const char *pub_data = data.c_str();
   //std::cout << "\nDATA: " << data;

   //esp_mqtt_client_stop(mqttclient);
   //esp_mqtt_client_start(mqttclient);

   //msg_id = esp_mqtt_client_publish(mqtt_client, topic_, pub_data, 0, 0, 1);
   msg_id = esp_mqtt_client_publish(*mqttclient, topic_, pub_data, 0, 0, 1);

   if(msg_id==0){
     printf("\nMSG COULDN'T BE PUBLISHED");
   }

 }

/*
 void ros_interface::push_pub_multi(std::string *topic, std::string *data,uint32_t size){
   int msg_id = 0;

   for(uint32_t i = 0; i < size; i++)
     const char *topic_ = *topic.c_str();
     const char *pub_data = *data.c_str();

     msg_id = esp_mqtt_client_publish(*mqttclient, topic_, pub_data, 0, 0, 1);
     topic++;
     data++;
     if(msg_id==0){
       printf("\nMSG COULDN'T BE PUBLISHED");
     }
  }

}*/
