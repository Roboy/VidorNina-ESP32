#ifndef TIME_SYNC_HPP_
#define TIME_SYNC_HPP_
#include <ros/ros.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <triangulation_msg/mode_msg.h>
#include <triangulation_msg/system_ctl.h>
#include <triangulation_msg/time_msg.h>
#include <triangulation_msg/time_sync_msg.h>
#include "mode_ctl.hpp"
#include "config.hpp"

#include "interface.hpp"

#include <unistd.h>
 
using namespace std;


struct time {
    double    sync_time_div;
    double    sys_time;
    uint32_t  cycle_cnt;
};

typedef struct time Time;

class time_sync
{
  public:
    time_sync(hardware_interface *hw_ = nullptr, uint8_t id = 0);

    uint32_t start_time_sync(bool is_master_mode_);

    Time time_data = {0,0,0};

    ros::NodeHandlePtr  nh;
    ros::Subscriber     time_ctl_sub,  sync_enable;
    ros::Publisher      time_pub;

    //subs
    void start_sync_mode();

    //pubs
    void update_time(bool is_master_mode_);

  private:
    int32_t *time_sync_base;
    hardware_interface *hw;
};
#endif
