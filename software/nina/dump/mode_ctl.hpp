#ifndef MODE_CTL_HPP_
#define MODE_CTL_HPP_

#include <ros/ros.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>
//#include "time_controll.hpp"
#include <triangulation_msg/mode_msg.h>
#include <triangulation_msg/system_ctl.h>
#include <triangulation_msg/time_msg.h>
#include <triangulation_msg/time_sync_msg.h>
#include <triangulation_msg/master_list.h>

#include "interface.hpp"

using namespace std;

#define MAX_CLIENTS 16
#define MAX_TIME_STAMPS 64

#define MODE_MASTER 0
#define MODE_SLAVE 1
#define SYNC_MASTER 0
#define SYNC_SLAVE 1

class fpga_mode{
  public:
    fpga_mode(hardware_interface *hw_ = nullptr);
    uint8_t   current_master_id = 0;
    uint8_t   id, master_id;
    uint8_t   mode;
    bool      sync_mode, sync_enable, burst_enable;
    std::vector<int> master_list;

    ros::NodeHandlePtr  nh;
    ros::Subscriber     system_sub, time_sync_sub;//module_mode_sub; //system_sub[MAX_CLIENTS + 1]
    ros::Publisher      system_pub, master_pub;

    void start_conversation();
    void conversation();

  private:
    //hw *pctl;
    hardware_interface *hw;

    uint8_t mode_pub;

    void (fpga_mode::*fp_start_conv)() = &fpga_mode::slave_init;
    void (fpga_mode::*fp_conv)();

    void slave_init();
    void master_init();

    void master_conv();
    void slave_conv();

    triangulation_msg::system_ctl   system_ctl_msg_pub;
    triangulation_msg::time_msg     time_msg_pub;

    //subs
    void get_slav_time(const triangulation_msg::time_msg::ConstPtr& msg);
    void get_syst_ctl(const triangulation_msg::system_ctl::ConstPtr& msg);
    void master_ctl(const triangulation_msg::master_list::ConstPtr& msg);
    //void get_mode(const triangulation_msg::mode_msg::ConstPtr& msg);

    //ring bufferd vector push
    void push_vec(vector<float>& vec, float data);
    void push_vec(vector<uint32_t>& vec, uint32_t data);
};
#endif
