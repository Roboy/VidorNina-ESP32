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
#include <vector>
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

#define MAX_SUBS 7
#define MAX_MASTER_LIST_SIZE 20


//static struct msg_mqtt msg_mqtt;

class fpga_mode{
  public:
    fpga_mode(hardware_interface *hw_,msg_gen *trans_,esp_mqtt_client_handle_t *mqttclient_);

    uint8_t   current_master_id = 0;
    uint8_t   id, master_id;
    uint8_t   mode;
    bool      sync_mode, sync_enable, burst_enable;
    //string *system_pub, *master_pub;

  typedef void (fpga_mode::*funcPtr)(string);
  funcPtr sub_func_list[MAX_SUBS] = {};  // static array
  //string system_pub_buff[10], master_pub_buff[10];
  string topic_list_sub[MAX_SUBS];
  //string SUB_system_ctl_buff[10], SUB_master_list_buff[10];
  //  uint32_t system_pub_cnt = 0;
//    uint32_t master_pub_cnt = 0;

    void transmission_init(esp_mqtt_client_handle_t *mqttclient_);

    //void select_subf(uint32_t location,string data_);
    void register_sub(esp_mqtt_client_handle_t *mqttclient_,string topic_,funcPtr func_ = nullptr);

    void select_subf(uint32_t location, string data_);

    void get_masterlist(string data_);
    void start_burst(string data_);
    void start_continiouse(string data_);
    void start_ptp_sync(string data_);
    void burst_cycles(string data_);
    void allow_input(string data_);

    void send_time_frame(uint32_t time_);


    //void transmission_init();



    //struct msg_mqtt msg_mqtt;


  private:
    //hw *pctl;
    uint32_t pub_cnt = 0;
    uint8_t mode_pub = 0;

    hardware_interface *hw;
    msg_gen *trans;

    void (fpga_mode::*fp_start_conv)() = &fpga_mode::slave_init;
    void (fpga_mode::*fp_conv)();

    void slave_init();
    void master_init();

    void master_conv();
    void slave_conv();

    void start_conversation();
    void conversation();

    //esp_mqtt_client_handle_t *mqttclient;

    //struct msg_mqtt msg_mqtt = {};
    //struct mqtt_out msg_tx;
    //struct mqtt_in msg_rx;
    std::vector<uint8_t> masterlist;

    string time_frame_topic;
    //uint8_t

    //esp_mqtt_client_handle_t *mqttclient;

    //uint8_t mode_pub;

    void push_vec(vector<float>& vec, float data);
    void push_vec(vector<uint8_t>& vec, uint8_t data);
    void pop_vec(vector<uint8_t>& vec);


    //subs
};
#endif
