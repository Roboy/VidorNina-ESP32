#ifndef _RVIZ_INTERFACE_HPP_
#define _RVIZ_INTERFACE_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstring>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point.h>

#include "custom_type.hpp"

#include <atomic>

#define ESCKEY_NEW_DATASET '+'
#define ESCKEY_NEW_DATA '/'

#define MAX_ARRAY_SIZE 100

void rviz_loop(std::atomic<bool>& program_is_running, std::vector<std::string> &rx_master, std::vector<std::string> &rx_slave, std::atomic<bool> & udp_waitForData_Flag, std::atomic<bool> & allow_tx);

class data_pars{
public:
  data_pars();

  unsigned int time_stamp[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

  void parse(std::vector<std::string> input, std::vector<std::string> input_slave);

private:
  std::string data_buffer[MAX_ARRAY_SIZE];
  std::string dataSet_buffer[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
  int parse_string(std::string inData, std::string *outdata, char identifier); //returns size
};





#endif
