#ifndef _RVIZ_INTERFACE_HPP_
#define _RVIZ_INTERFACE_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/Point.h>


class rviz_interface{
public:
  rviz_interface();
  //int udp_init();
  static void loop(std::atomic<bool>& program_is_running);


    ros::NodeHandlePtr  nh;
    ros::Subscriber     client_sub[MAX_CLIENTS + 1];
    ros::Publisher      marker_pub;

    visualization_msgs::Marker marker;

};



#endif
