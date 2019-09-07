#ifndef _RVIZ_INTERFACE_HPP_
#define _RVIZ_INTERFACE_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstring>


#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point.h>

#include "custom_type.hpp"

#include <atomic>

#include <cmath>


#define ESCKEY_NEW_DATASET '+'
#define ESCKEY_NEW_DATA '/'

#define MAX_ARRAY_SIZE 100


#define FPGA_CLK_FRQ      50000000
#define FPGA_CLK_T        (double)( 1. / FPGA_CLK_FRQ)

#define SOUND_SPEED       340 //m/s
#define DISTANCE_FACTOR   FPGA_CLK_T

void rviz_loop(std::atomic<bool>& program_is_running, std::vector<std::string> &rx_master, std::vector<std::string> &rx_slave, std::atomic<bool> & udp_waitForData_Flag, std::atomic<bool> & allow_tx);

class data_pars{
public:
  data_pars(visualization_msgs::Marker *marker_);

  unsigned int time_stamp[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

  void parse(std::vector<std::string> input, std::vector<std::string> input_slave);
  double calc_distance (uint32_t t1, uint32_t t2);
  void calc_kartes();
  void sort_data();
  void send_datapoints(int id_, int des_id_, double dist_);


  visualization_msgs::Marker *marker;
  geometry_msgs::Point point;

private:
  std::string data_buffer[MAX_ARRAY_SIZE];
  std::string dataSet_buffer[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

  unsigned int data_match[20][MAX_ARRAY_SIZE];
  unsigned int data_master[20];


  uint8_t num_slave_data = 0;

  double dist[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

  int parse_string(std::string inData, std::string *outdata, char identifier); //returns size
};





#endif
