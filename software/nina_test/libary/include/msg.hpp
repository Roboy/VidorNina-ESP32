#ifndef MODE_CTL_HPP_
#define MODE_CTL_HPP_

//#include <ros/ros.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>

#include <sstream>
#include <iostream>

using namespace std;


#define MAX_VEC_SIZE 30

class msg_gen{
  public:
    msg_gen(ros_interface *transmit_);

    template <typename T>
    void pub_multi(std::string *topic, T *t, uint32_t vec_size);
    void creat_topics(string *ret_data,string base_topic, const char* names_[], uint32_t size_);

  private:
    ros_interface *transmit;

};


struct msg_mqtt{
  struct master_list{
    uint32_t start_ptp_sync;
    uint32_t start_burst;
    uint32_t start_continiouse_mode;
    uint32_t burst_cycles;
    uint32_t master_id_list[MAX_VEC_SIZE];
    const char* names[5] = {
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
    float32 trigger_time[MAX_VEC_SIZE];
    const char* names[3] = {
      "master_id",
      "enable_slave_input",
      "#",
      "trigger_time"
    };
  }system_ctl;

  struct {
    uint32_t id;
    float32 trigger_time[MAX_VEC_SIZE];
    uint32_t master_identifier[MAX_VEC_SIZE];
    const char* names[3] = {
      "id",
      "#",
      "trigger_time",
      "#",
      "master_identifier"
    };
  }time_msg;

  struct time_sync_msg{
    uint32_t id;
    float32 sync_time_div[MAX_VEC_SIZE];
    uint32 cycle_cnt[MAX_VEC_SIZE];
    float32 sys_time[MAX_VEC_SIZE];
    const char* names[4] = {
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
