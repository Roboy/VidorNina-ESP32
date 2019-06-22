#include "mode_ctl.hpp"
#include <string>
/*
TODO:
Testzwecke master ctl via ROS
zu ueberlegen, auto master zu slave bzw slave zu master um schneller mehr daten zu bekommen
*/

fpga_mode::fpga_mode(hardware_interface *hw_){ //hw *hw_){

  hw = hw_;

  id = hw->getID();//(uint8_t)(IORD(base_addr_, (uint32_t)(0x00<<8|0)));
  mode_pub = id;
  mode = mode_pub + 1; //has to be different to init as new mode
  //pctl = pctl_;

  printf("\nID: %d", id);

  sync_enable = 0;

/*
  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "mode" + std::to_string(id));
  }
  nh = ros::NodeHandlePtr(new ros::NodeHandle);
  */

  /////------ROS ---PUBS ////

  trans = new msg_gen(&hw->ros);

  std::stringstream ss_buffer;
  ss_buffer << "/triangulation/" << 0 << "ID/time_data/";
  trans.creat_topics(&system_pub_buff[0],ss_buffer.str(), msg_mqtt.time_msg.names, sizeof(msg_mqtt.time_msg.names));
  //hw.ros.creat_topics(&system_pub_buff[0],ss_buffer.str(), msg_mqtt.time_msg.names, sizeof(msg_mqtt.time_msg.names));
  ss_buffer.str("");
  ss_buffer << "/triangulation/" << 0 << "ID/ctl/";
  trans.creat_topics(&master_pub_buff[0],ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  //hw.ros.creat_topics(&master_pub_buff[0],ss_buffer.str(), msg_mqtt.system_ctl.names, sizeof(msg_mqtt.system_ctl.names));
  ss_buffer.str("");


  //push_pub_multi(&system_pub_buff[0], &system_pub_buff[0], *data,1);
  //push_pub_multi(&master_pub_buff[0], &system_pub_buff[0], *data,1);


  //system_pub  = nh->advertise<triangulation_msg::time_msg>("/triangulation/" + std::to_string(id) + "ID/time_data", 1);
  //master_pub  = nh->advertise<triangulation_msg::system_ctl>("/triangulation/" + std::to_string(id) + "ID/ctl", 1);

  msg_mqtt.time_msg_pub.id=(uint32_t)id;
  //push_vec(time_msg_pub.trigger_time, 0);
  //push_vec(time_msg_pub.master_identifier, current_master_id); //master id
  msg_mqtt.time_msg_pub.trigger_time[0] = 0;
  msg_mqtt.time_msg_pub.master_identifier[0] = (uint32_t)current_master_id;

  msg_mqtt.system_ctl_msg_pub.master_id=(uint32_t)id;
  msg_mqtt.system_ctl_msg_pub.enable_slave_input=0;
  //push_vec(system_ctl_msg_pub.trigger_time, 0);
  msg_mqtt.system_ctl_msg_pub.trigger_time[0] = 0;


  //system_pub.publish(time_msg_pub);
  //master_pub.publish(system_ctl_msg_pub);

  trans.pub_multi(&system_pub_buff[0],&msg_mqtt.time_msg,0);
  trans.pub_multi(&master_pub_buff[0],&msg_mqtt.system_ctl,0);

  /////------ROS ---SUBS ////
  //Todo it is useless if system is current master
  system_sub = nh->subscribe("/triangulation/" + std::to_string(current_master_id) + "ID/ctl", 1, &fpga_mode::get_syst_ctl, this);
  //start ptp time sync
  time_sync_sub = nh->subscribe("/triangulation/all/master_list", 1, &fpga_mode::master_ctl, this);

  //TODO :: system sub soll sich die master liste von master_list.msg ziehen
  //system_sub = nh->subscribe("/triangulation/" + std::to_string(id) + "/mode", 1, &fpga_mode::get_mode, this);

  hw->piezo_set_burst_cycles(10000);
  hw->stop_US_out();
}

//==============================
//Interface
//==============================
void fpga_mode::start_conversation(){
  if(mode_pub != mode){
      mode = mode_pub;
    if(mode == MODE_MASTER){
      fp_start_conv = &fpga_mode::master_init;  //default &fpga_mode::slave_init
    } else {
      fp_start_conv = &fpga_mode::slave_init;  //default &fpga_mode::slave_init
    }

    ((*this).*(fp_start_conv))();
  }
}
void fpga_mode::conversation(){
  ((*this).*(fp_conv))();
}

//==============================
//Init routins
//==============================
void fpga_mode::master_init(){
  std::cout << "\nMASTER Init";

  fp_conv = &fpga_mode::master_conv;
  //for(uint8_t id_cnt = 0; id_cnt < MAX_CLIENTS; id_cnt++)
 //    system_sub[id_cnt] = nh->subscribe("/triangulation/" + std::to_string(id_cnt) + "/trigger_time", 1, &fpga_mode::get_slav_time, this);

  //system_pub.publish(system_ctl_msg_pub);
}

void fpga_mode::slave_init(){
  std::cout << "\nSLAVE Init";
  fp_conv = &fpga_mode::slave_conv;
  //system_pub  = nh->advertise<triangulation_msg::time_msg>("/triangulation/" + std::to_string(id) + "/time_data", 1);
  //system_sub[MAX_CLIENTS] = nh->subscribe("/triangulation/all/ctl", 1, &fpga_mode::get_syst_ctl, this); //Todo add sub function
  //system_pub.publish(time_msg_pub);
}

//==============================
//conversation routin
//==============================
void fpga_mode::master_conv(){
  cout << "\nstart master conversation: ";

  //enable slave
  system_ctl_msg_pub.enable_slave_input=true;
  master_pub.publish(system_ctl_msg_pub);
  //TODO: wait for response over ROS;
  //...
  //hw->start_US_out();
  hw->piezo_burst_out();

  push_vec(time_msg_pub.trigger_time, hw->US_start_time);
  push_vec(time_msg_pub.master_identifier, id); //master id

  system_pub.publish(time_msg_pub);


  usleep(10000);//Todo optimze this line
  hw->stop_US_out();
}

//-------------------------------
void fpga_mode::slave_conv(){
  std::cout << "\nstart slave conversation: ";

  //TODO: wait till slave allow;
  //....

  hw->allow_input_trigger(); //TODO ... do it via ros
  for(int time_out_cnt = 0; time_out_cnt <= 4294967294; time_out_cnt++){
    if(hw->rdy_to_read())
      break;
  }

  push_vec(time_msg_pub.trigger_time, hw->read_trigger_time());
  push_vec(time_msg_pub.master_identifier, current_master_id); //master id

  system_pub.publish(time_msg_pub);
}


//==============================
//common routin for ros
//==============================
/*void fpga_mode::get_mode(const triangulation_msg::master_list::ConstPtr& msg){
    .... msg->master_id_list;


    ROS_INFO("current mode: %d", msg->mode);
    mode_pub = msg->mode;
    sync_mode = msg->sync_mode;
    sync_enable = msg->sync_enable;
    ROS_INFO("sync enable: %d", msg->sync_enable);

}*/

void fpga_mode::get_slav_time(const triangulation_msg::time_msg::ConstPtr& msg){
  std::cout << "\n" << msg->id;
}
void fpga_mode::get_syst_ctl(const triangulation_msg::system_ctl::ConstPtr& msg){
  std::cout << "\nmaster ID: " << msg->master_id;
}
void fpga_mode::master_ctl(const triangulation_msg::master_list::ConstPtr& msg){
  sync_enable = msg->start_ptp_sync;
  hw->piezo_set_burst_cycles(msg->burst_cycles);
  burst_enable = msg->start_burst;
  if(msg->start_continiouse_mode)
    hw->start_US_out();
  else
    hw->stop_US_out();

  //TODO readout list
  //master_list = msg->master_id_list;
}

//ring bufferd vector push
void fpga_mode::push_vec(vector<float>& vec, float data){
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
  vec.resize(MAX_TIME_STAMPS);
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }

  vec.push_back(data);
}

void fpga_mode::push_vec(vector<uint32_t>& vec, uint32_t data){
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
  vec.resize(MAX_TIME_STAMPS);
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }

  vec.push_back(data);
}
