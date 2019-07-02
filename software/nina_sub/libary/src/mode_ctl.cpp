#include "mode_ctl.hpp"
#include <string>
/*
TODO:
Testzwecke master ctl via ROS
zu ueberlegen, auto master zu slave bzw slave zu master um schneller mehr daten zu bekommen
*/



fpga_mode::fpga_mode(hardware_interface *hw_, msg_gen *trans_,esp_mqtt_client_handle_t *mqttclient_){ //hw *hw_){
  //mqttclient = mqttclient_;
  trans = trans_;
  hw = hw_;

  id = hw->getID();//(uint8_t)(IORD(base_addr_, (uint32_t)(0x00<<8|0)));
  mode_pub = id;
  mode = mode_pub + 1; //has to be different to init as new mode*/

  pub_cnt = 0;


}

void fpga_mode::transmission_init(esp_mqtt_client_handle_t *mqttclient_){
  struct msg_mqtt msg_mqtt;
  std::stringstream ss_buffer;




  ss_buffer << "/triangulation/" << id << "/time_data/";
  trans->push_pub(ss_buffer.str(),"time_data");
  ss_buffer.str("");

  /*

  struct simple_msg{
    struct mqtt_out{
      bool allow_input;
      float trigger_time[MAX_LIST_SIZE];
      uint8_t master_identifier[MAX_LIST_SIZE];
    }mqtt_out;
    struct mqtt_in{
      std::vector<uint8_t> masterlist;
      bool     start_burst;
      bool     start_continiouse;
      bool     start_ptp_sync;
      uint32_t burst_cycles;
    }mqtt_in;
  };


  */
  register_sub(mqttclient_,"/triangulation/master/masterlist/", &fpga_mode::masterlist);
  register_sub(mqttclient_,"/triangulation/master/start_burst/", &fpga_mode::start_burst);
  register_sub(mqttclient_,"/triangulation/master/start_continiouse/", &fpga_mode::start_continiouse);
  register_sub(mqttclient_,"/triangulation/master/start_ptp_sync/", &fpga_mode::start_ptp_sync);
  register_sub(mqttclient_,"/triangulation/master/burst_cycles/", &fpga_mode::burst_cycles);
  register_sub(mqttclient_,"/triangulation/master/allow_input/", &fpga_mode::allow_input);

}

/*
void fpga_mode::transmission_init(){
  esp_mqtt_client_register_event(*mqttclient, MQTT_EVENT_DATA, foo, *mqttclient);
  (void)esp_mqtt_client_subscribe(*mqttclient, "/topic/qos3", 0);
}*/

void fpga_mode::select_subf(uint32_t location, string data_){
  printf("\nsub subf\n");
  //(*this.*sub_func_list[location])(data_);       //<--- her the overflow probably happens ...
}

void fpga_mode::register_sub(esp_mqtt_client_handle_t *mqttclient_,string topic_,funcPtr func_){
  topic_list_sub[pub_cnt] = topic_;//"/topic/qos3";
  sub_func_list[pub_cnt] = func_;//&fpga_mode::get_slav_time;
  //const char *topic_buff = topic_.c_str();
  (void)esp_mqtt_client_subscribe(*mqttclient_, topic_.c_str(), 0);


  //trans->creat_topics();
  pub_cnt++;
}
//--------------------------------SUB - FUNCTIONS -----------
void fpga_mode::masterlist(string data_){
  printf("\n-==MASTERLIST===\n");
  //std::vector<int> master_list;

}
void fpga_mode::start_burst(string data_){
  printf("\n-==start_burst===\n");
}
void fpga_mode::start_continiouse(string data_){
  printf("\n-==start_continiouse===\n");
}
void fpga_mode::start_ptp_sync(string data_){
  printf("\n-==start_ptp_sync===\n");
}
void fpga_mode::burst_cycles(string data_){
  printf("\n-==burst_cycles===\n");
}
void fpga_mode::allow_input(string data_){
  printf("\n-==allow_input===\n");
}
