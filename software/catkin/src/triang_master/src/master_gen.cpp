//#include "master_gen.hpp"

/*
master_gen::master_gen(uint8_t member_amount){

  master_list.start_ptp_sync = false;
  master_list.start_burst = false;
  master_list.burst_cycles = 3;
  master_list.start_continiouse_mode = false;
  for(uint8_t cnt=0; cnt <= member_amount-1; cnt++){
    master_list.master_id_list.push_back(cnt);
  }

  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "triangulation_system_GRAND_MASTERS");
  }
  nh = ros::NodeHandlePtr(new ros::NodeHandle);


  master_pub  = nh->advertise<triangulation_msg::master_list>("/triangulation/all/master_list", 1);
  master_pub.publish(master_list);
}

void master_gen::add_list_member(){
  uint8_t new_master_id = 0;
  */
  //TODO:assign new master id's
  /*
  if(){ //wait till sync is over to  create new member

  }

  */
  /*
  push_vec(master_list.master_id_list, new_master_id);
}
void master_gen::tgl_continiouse_mode(){
  master_list.start_continiouse_mode = !master_list.start_continiouse_mode;
  master_list.start_burst = false;
  master_list.start_ptp_sync=false;
  master_pub.publish(master_list);
}
void master_gen::time_sync_tgl(bool is_enable_){
  master_list.start_continiouse_mode = false;
  master_list.start_burst = false;
  master_list.start_ptp_sync = is_enable_;
  master_pub.publish(master_list);
}
void master_gen::start_burst_mode(){
  master_list.start_continiouse_mode = false;
  master_list.start_ptp_sync=false;
  master_list.start_burst = !master_list.start_burst;
  master_pub.publish(master_list);
}

//ring bufferd vector push
void master_gen::push_vec(vector<uint32_t>& vec, uint32_t data){
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }
  vec.resize(MASTER_LIST_SIZE);
  for (uint8_t vec_cnt = 0; vec_cnt < vec.size()/2; vec_cnt++){
    int buff;
    buff = vec[vec.size()-1-vec_cnt];
    vec[vec.size()-1-vec_cnt]=vec[vec_cnt];
    vec[vec_cnt]=buff;
  }

  vec.push_back(data);
}
*/
