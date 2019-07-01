#ifndef MODE_CTL_HPP_
#define MODE_CTL_HPP_

//#include <ros/ros.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>
#include "msg.hpp"

#include <sstream>
#include <iostream>
#include "mqtt_client.h"
#include "FpgaVidor.hpp"
//#include "time_controll.hpp"
/*#include <triangulation_msg/mode_msg.h>
#include <triangulation_msg/system_ctl.h>
#include <triangulation_msg/time_msg.h>
#include <triangulation_msg/time_sync_msg.h>
#include <triangulation_msg/master_list.h>
*/

//#include "interface.hpp"

using namespace std;

#define MAX_CLIENTS 16
#define MAX_TIME_STAMPS 64

#define MODE_MASTER 0
#define MODE_SLAVE 1
#define SYNC_MASTER 0
#define SYNC_SLAVE 1

class fpga_mode{
  public:
    fpga_mode(hardware_interface *hw_,esp_mqtt_client_handle_t *mqttclient_);

    uint8_t   current_master_id = 0;
    uint8_t   id, master_id;
    uint8_t   mode;
    bool      sync_mode, sync_enable, burst_enable;
    //string *system_pub, *master_pub;

  typedef void (fpga_mode::*funcPtr)(string);
  funcPtr sub_func_list[2] = {};  // static array
  string system_pub_buff[10], master_pub_buff[10];
  string topic_list_sub[10];
  string SUB_system_ctl_buff[10], SUB_master_list_buff[10];
  //  uint32_t system_pub_cnt = 0;
//    uint32_t master_pub_cnt = 0;


    //void select_subf(uint32_t location,string data_);
    void select_subf(uint32_t location, string data_);
    void get_slav_time(string data_);
    void get_syst_ctl(string data_);
    void master_ctl(string data_);
    void masterlist(string data_);

    //void transmission_init();

    void register_sub(string topic_,funcPtr func_ = nullptr);

    //struct msg_mqtt msg_mqtt;


  private:
    //hw *pctl;
    uint32_t pub_cnt = 0;
    uint8_t mode_pub = 0;

    hardware_interface *hw;
    msg_gen *trans;


    esp_mqtt_client_handle_t *mqttclient;

    //uint8_t mode_pub;


    //subs
};
#endif
