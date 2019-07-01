#include "mode_ctl.hpp"
#include <string>
/*
TODO:
Testzwecke master ctl via ROS
zu ueberlegen, auto master zu slave bzw slave zu master um schneller mehr daten zu bekommen
*/

static void foo(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data){
  printf("==== FUCK YEA === ");
  esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
  //foo(event_data);
  //esp_mqtt_event_handle_t event = event_data;

  printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
  printf("DATA=%.*s\r\n", event->data_len, event->data);
}

fpga_mode::fpga_mode(hardware_interface *hw_, esp_mqtt_client_handle_t *mqttclient_){ //hw *hw_){
  //mqttclient = mqttclient_;
  pub_cnt = 0;
  //hw = hw_;

  topic_list_sub[0] = "/topic/qos3";
  sub_func_list[0] =  &fpga_mode::masterlist;


  //typedef void (*funcPtr)(void);
  //funcPtr fpga_mode::*sub_func_list = (fpga_mode::*)malloc(sizeof(funcPtr) * 30);
  //fpga_mode::*sub_func_list = malloc(sizeof(void) * 30);
  //sub_func_list = (funcPtr)malloc(30*sizeof(funcPtr));  // heap dynamic array

  /*
  id = hw->getID();//(uint8_t)(IORD(base_addr_, (uint32_t)(0x00<<8|0)));
  mode_pub = id;
  mode = mode_pub + 1; //has to be different to init as new mode
  //pctl = pctl_;

  printf("\nID: %d", id);

  sync_enable = 0;*/


  //--------------------------------------------
  //        PUBS
  //--------------------------------------------

  //trans = new msg_gen(mqttclient);//&hw->transmit);
  //std::stringstream ss_buffer;
  /*
  trans = hw->transmit;
  //trans = hw->transmit;


  ss_buffer << "/triangulation/" << 0 << "ID/time_data/";
  trans->creat_topics(&system_pub_buff[0],ss_buffer.str(), msg_mqtt.time_msg.names, sizeof(msg_mqtt.time_msg.names));
  //hw.ros.creat_topics(&system_pub_buff[0],ss_buffer.str(), msg_mqtt.time_msg.names, sizeof(msg_mqtt.time_msg.names));
  ss_buffer.str("");
  ss_buffer << "/triangulation/" << 0 << "ID/ctl/";
  trans->creat_topics(&master_pub_buff[0],ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  //hw.ros.creat_topics(&master_pub_buff[0],ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  ss_buffer.str("");


  msg_mqtt.time_msg.id=(uint32_t)id;
  //push_vec(time_msg_pub.trigger_time, 0);
  //push_vec(time_msg_pub.master_identifier, current_master_id); //master id
  msg_mqtt.time_msg.trigger_time[0] = 0;
  msg_mqtt.time_msg.master_identifier[0] = (uint32_t)current_master_id;

  msg_mqtt.system_ctl.master_id=(uint32_t)id;
  msg_mqtt.system_ctl.enable_slave_input=0;
  //push_vec(system_ctl_msg_pub.trigger_time, 0);
  msg_mqtt.system_ctl.trigger_time[0] = 0;*/


  //system_pub.publish(time_msg_pub);
  //master_pub.publish(system_ctl_msg_pub);

  //trans->pub_multi(&system_pub_buff[0],&msg_mqtt.time_msg,0);
  //trans->pub_multi(&master_pub_buff[0],&msg_mqtt.system_ctl,0);



  //--------------------------------------------
  //        SUBS
  //--------------------------------------------



  //system_sub = nh->subscribe("/triangulation/" + std::to_string(current_master_id) + "ID/ctl", 1, &fpga_mode::get_syst_ctl, this);
  //start ptp time sync
  //time_sync_sub = nh->subscribe("/triangulation/all/master_list", 1, &fpga_mode::master_ctl, this);
  /*ss_buffer << "/triangulation/" << current_master_id << "ID/ctl";
  trans->creat_topics(&SUB_system_ctl_buff[0], ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  ss_buffer.str("");

  trans->creat_topics(&SUB_master_list_buff[0], ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));

  register_sub(ss_buffer.str(), &fpga_mode::get_syst_ctl);
  */

  //ss_buffer << "/triangulation/all/master_list";
  //register_sub(ss_buffer.str(), &fpga_mode::masterlist);
  //ss_buffer.str("");
  //topic_list_sub[0] = "/topic/qos3";
  //sub_func_list[0] =  &fpga_mode::get_slav_time;

}

/*
void fpga_mode::transmission_init(){
  esp_mqtt_client_register_event(*mqttclient, MQTT_EVENT_DATA, foo, *mqttclient);
  (void)esp_mqtt_client_subscribe(*mqttclient, "/topic/qos3", 0);
}*/
void fpga_mode::select_subf(uint32_t location){
  printf("\nsub subf\n");
  //(*this.*sub_func_list[location])(data_);       //<--- her the overflow probably happens ...
}
void fpga_mode::masterlist(){
  printf("\n------list\n");
  //std::vector<int> master_list;

}

/*
void fpga_mode::select_subf(uint32_t location, string data_){
  cout << "\nLokation: " << location;
  //(*this.*sub_func_list[location])(data_);       //<--- her the overflow probably happens ...
}

void fpga_mode::get_slav_time(string data_){
  //const esp_mqtt_client_config_t mqtt_cfg = {mqtt_event_handler ,NULL ,"mqtt://192.168.1.1", "mqtt://192.168.1.1"};
  printf("GET_SLAVE_TIME");
}


void fpga_mode::get_syst_ctl(string data_){
  printf("\nget_syst_ctl\n");

}
void fpga_mode::master_ctl(string data_){
  printf("\nmaster_ctl\n");
}
void fpga_mode::masterlist(string data_){
  printf("\n------list\n");
  uint32_t i;
	std::istringstream(data_) >> i;

  cout << i << "\n";

  //std::vector<int> master_list;

}


void fpga_mode::register_sub(string topic_,funcPtr func_){
  topic_list_sub[pub_cnt] = topic_;//"/topic/qos3";
  sub_func_list[pub_cnt] =  func_;//&fpga_mode::get_slav_time;

  //trans->creat_topics();
  pub_cnt++;
}
*/
