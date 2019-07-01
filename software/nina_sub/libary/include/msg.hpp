#ifndef _MSG_HPP_
#define _MSG_HPP_

//#include <ros/ros.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>

#include <sstream>
#include <iostream>

#include "mqtt_client.h"

using namespace std;


#define MAX_VEC_SIZE 10
#define MAX_POINTER_SIZE 128

//template <typename T_, typename C>
//void foo_(string *topic_, T_ *t, uint32_t vec_size,C *c);

class msg_gen{
  public:
    msg_gen(esp_mqtt_client_handle_t *mqtt_client_);

    void push_pub(std::string topic, std::string data);
    template <typename T>
    void pub_multi(string *topic_, T *t, uint32_t vec_size);
    void creat_topics(string *ret_data,string base_topic, const char* names_[], uint32_t size_);


    //string topic_buff_pub[MAX_POINTER_SIZE];
    //string *topic_list_pub;
    //string topic_buff_sub[MAX_POINTER_SIZE];
    //string *topic_list_sub;

  private:
    esp_mqtt_client_handle_t *mqttclient;

};


struct msg_mqtt{
  struct master_list{
    uint32_t start_ptp_sync;
    uint32_t start_burst;
    uint32_t start_continiouse_mode;
    uint32_t burst_cycles;
    uint32_t master_id_list[MAX_VEC_SIZE];
    const char* names[6] = {
      "start_ptp_sync",
      "start_burst",
      "start_continiouse_mode",
      "burst_cycles",
      "#",
      "master_id_list"
    };
  }master_list;

  struct mode_msg{
    uint32_t id;
    //#0 master broadcast, 1 slave broadcast
    uint32_t mode;
    //#0 sync slave,       1 sync master
    uint32_t sync_mode;
    uint32_t sync_enable;
    const char* names[4] = {
      "id",
      //#0 master broadcast, 1 slave broadcast
      "mode",
      //#0 sync slave,       1 sync master
      "sync_mode",
      "sync_enable"
    };
  }mode_msg;

  struct system_ctl{
    uint32_t master_id;
    uint32_t enable_slave_input;
    float trigger_time[MAX_VEC_SIZE];
    const char* names[4] = {
      "master_id",
      "enable_slave_input",
      "#",
      "trigger_time"
    };
  }system_ctl;

  struct {
    uint32_t id;
    float trigger_time[MAX_VEC_SIZE];
    uint32_t master_identifier[MAX_VEC_SIZE];
    const char* names[5] = {
      "id",
      "#",
      "trigger_time",
      "#",
      "master_identifier"
    };
  }time_msg;

  struct time_sync_msg{
    uint32_t id;
    float sync_time_div[MAX_VEC_SIZE];
    uint32_t cycle_cnt[MAX_VEC_SIZE];
    float sys_time[MAX_VEC_SIZE];
    const char* names[7] = {
      "id",
      "#",
      "sync_time_div",
      "#",
      "cycle_cnt",
      "#",
      "sys_time"
    };
  }time_sync_msg;

};

/*
master_list master_list;
mode_msg mode_msg;
system_ctl system_ctl;
time_msg time_msg;
time_sync_msg time_sync_msg;
*/

#endif
