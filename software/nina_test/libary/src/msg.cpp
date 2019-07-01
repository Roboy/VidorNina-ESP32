#include "msg.hpp"


msg_gen::msg_gen(ros_interface *transmit_){
    transmit = transmit_;
}

template <typename T>
void msg_gen::pub_multi(std::string *topic, T *t, uint32_t vec_size){
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

        if(reinterpret_cast<uintptr_t>(p)+(30)*(4*num_arry_cnt)+4 < reinterpret_cast<uintptr_t>(t->names)){
            //cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
            //cout << "\nTOPIC: "<< *topic++;
            //cout << "\nDATA : "<< *p;
            ss_ << *p;
            transmit.push_pub(*topic++, ss_.str());
            ss_.str("");

        }else{
            for(uint32_t i = 0; i < vec_size; i++){
                //cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
                //cout << "\nvecTOPIC: "<< *topic++;
                //cout << "\nvecDATA : "<< *p++;
                ss_ << *p++;
                transmit.push_pub(*topic++, ss_.str());
                ss_.str("");

            }
            cout << "\n----\n";
            for(uint32_t i = 0; i < (30-vec_size); i++){
                topic++;
                p++;
            }
        }
    }
}

void msg_gen::creat_topics(string *ret_data,string base_topic, const char* names_[], uint32_t size_){

  uint32_t name_cnt = 0;

  name_cnt = size_/8;
  cout << name_cnt << "\n";

  for(uint32_t i = 0; i < name_cnt; i++){
    std::stringstream ss_;
    if(*names_[i] == '#'){
        i++;
        for(uint32_t j = 0; j < 30; j++){
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
