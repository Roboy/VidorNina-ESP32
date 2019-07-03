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


  std::stringstream ss_buffer;

  ss_buffer << "/triangulation/" << id << "/time_data/";
  time_frame_topic = ss_buffer.str();
  ss_buffer.str("");

}

void fpga_mode::transmission_init(esp_mqtt_client_handle_t *mqttclient_){
  //struct msg_mqtt msg_mqtt;
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
  register_sub(mqttclient_,"/triangulation/master/masterlist/", &fpga_mode::get_masterlist);
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
  (*this.*sub_func_list[location])(data_);       //<--- her the overflow probably happens ...
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
void fpga_mode::get_masterlist(string data_){ // Format "0,1,2,3,4;"
  printf("\n-==MASTERLIST===\n");
  //cout << "original data: " << data_ << "\n";
  const char *data_buffer = data_.c_str();
  uint8_t digit_buffer = 0;

  bool err_dat = false;

  for(uint8_t i = 0; i < 100; i++){
    if(*data_buffer != ',' && *data_buffer != ';'){
      if((uint8_t)*data_buffer > 57 || (uint8_t)*data_buffer < 48)
        return;
      digit_buffer += (uint8_t)*data_buffer - 48;
      //printf("\ncnt:  %d", i);
      //printf("\nSTRING DATA:  %c", *data_buffer);
      //printf("\nconv DATA:  %d", digit_buffer);
      //printf("\nraw conv DATA: %d", (uint8_t)*data_buffer);

      data_buffer++;
    }
    else{
      if(i == 0){
        cout << "\n[ERROR] MASTERLIST EMPTY";
        return;
      }
      cout<<"\nMaster ID: " << digit_buffer;
      push_vec(masterlist, digit_buffer);
      //*list++ = digit_buffer;
      digit_buffer = 0;
      if(*data_buffer == ';')
        break;

      data_buffer++;
    }
  }

  //cout << "\n==END MASTERLIST ==\n";
  /*for(uint8_t i = 0; i < 20; i++){
    //printf("\nList: (%d):  %d", i, masterlist[i]);
    printf("\nList: (%d):  %d", i, masterlist.front());
    //masterlist.pop_back();

  }*/

  //cout <<"\nList: (0)" << masterlist.at(0) << "..(1)" << masterlist.at(1);

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


//-------- void pub ...
void fpga_mode::send_time_frame(float time_){
  std::stringstream ss_buffer;
  ss_buffer << "[" << masterlist.front() << "]" << (uint32_t)time_;
  pop_vec(masterlist);

  trans->push_pub(time_frame_topic,ss_buffer.str());
}


void fpga_mode::pop_vec(vector<uint8_t>& vec){
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
  vec.pop_back();
  vec.resize(MAX_MASTER_LIST_SIZE);
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
}

//ring bufferd vector push
void fpga_mode::push_vec(vector<float>& vec, float data){
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
  vec.resize(MAX_MASTER_LIST_SIZE);
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }

  vec.push_back(data);
}

void fpga_mode::push_vec(vector<uint8_t>& vec, uint8_t data){
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
  vec.resize(MAX_MASTER_LIST_SIZE-1);
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }

  vec.push_back(data);
}
