#include "mode_ctl.hpp"
#include <string>
/*
TODO:
Testzwecke master ctl via ROS
zu ueberlegen, auto master zu slave bzw slave zu master um schneller mehr daten zu bekommen
*/

template <typename T_>
void foo_(string *topic_, T_ *t, uint32_t vec_size){
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
          cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
          cout << "\nTOPIC: "<< *topic_++;
          cout << "\nDATA : "<< *p;
          ss_ << *p;
          //c->push_pub(*topic_++, ss_.str());
          //cout << ss_.str()
          ss_.str("");

      }else{
          for(uint32_t i = 0; i < vec_size; i++){
              cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
              cout << "\nvecTOPIC: "<< *topic_++;
              cout << "\nvecDATA : "<< *p++;
              ss_ << *p++;
              //c->push_pub(*topic_++, ss_.str());
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

fpga_mode::fpga_mode(hardware_interface *hw_, esp_mqtt_client_handle_t *mqttclient_){ //hw *hw_){
  mqttclient = mqttclient_;
  hw = hw_;

  id = hw->getID();//(uint8_t)(IORD(base_addr_, (uint32_t)(0x00<<8|0)));
  mode_pub = id;
  mode = mode_pub + 1; //has to be different to init as new mode*/

  pub_cnt = 0;

  register_sub("/topic/qos3", &fpga_mode::masterlist);

  struct msg_mqtt msg_mqtt;
  std::stringstream ss_buffer;

  //topic_list_sub[0] = ;
  //sub_func_list[0] =  ;


  //trans = hw->transmit;
  trans = new msg_gen(mqttclient);



  ss_buffer << "/triangulation/" << 0 << "ID/time_data/";
  trans->creat_topics(&system_pub_buff[0],ss_buffer.str(), msg_mqtt.time_msg.names, sizeof(msg_mqtt.time_msg.names));
  //hw.ros.creat_topics(&system_pub_buff[0],ss_buffer.str(), msg_mqtt.time_msg.names, sizeof(msg_mqtt.time_msg.names));
  ss_buffer.str("");
  ss_buffer << "/triangulation/" << 0 << "ID/ctl/";
  trans->creat_topics(&master_pub_buff[0],ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  //hw.ros.creat_topics(&master_pub_buff[0],ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  ss_buffer.str("");

  cout << "\n" << "===============================" << "\n";

  msg_mqtt.time_msg.id=(uint32_t)id;
  //push_vec(time_msg_pub.trigger_time, 0);
  //push_vec(time_msg_pub.master_identifier, current_master_id); //master id
  msg_mqtt.time_msg.trigger_time[0] = 0;
  msg_mqtt.time_msg.master_identifier[0] = (uint32_t)current_master_id;

  msg_mqtt.system_ctl.master_id=(uint32_t)id;
  msg_mqtt.system_ctl.enable_slave_input=0;
  //push_vec(system_ctl_msg_pubqos3.trigger_time, 0);
  msg_mqtt.system_ctl.trigger_time[0] = 0;

  //trans->pub_multi<struct time_msg>(&system_pub_buff[0],&msg_mqtt.time_msg,0);

  //trans->pub_multi(&master_pub_buff[0],&msg_mqtt.system_ctl,0);
  foo_(&master_pub_buff[0],&msg_mqtt.system_ctl,0);
  //foo_(&msg_mqtt.system_ctl);

}

/*
void fpga_mode::transmission_init(){
  esp_mqtt_client_register_event(*mqttclient, MQTT_EVENT_DATA, foo, *mqttclient);
  (void)esp_mqtt_client_subscribe(*mqttclient, "/topic/qos3", 0);
}*/

void fpga_mode::select_subf(uint32_t location, string data_){
  printf("\nsub subf\n");
  (*this.*sub_func_list[location])(data_);       //<--- her the overflow probably happens ...
}
void fpga_mode::masterlist(string data_){
  printf("\n------list\n");
  //std::vector<int> master_list;

}


void fpga_mode::register_sub(string topic_,funcPtr func_){
  topic_list_sub[pub_cnt] = topic_;//"/topic/qos3";
  sub_func_list[pub_cnt] = func_;//&fpga_mode::get_slav_time;

  //trans->creat_topics();
  pub_cnt++;
  ;
}
