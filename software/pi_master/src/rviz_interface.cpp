#include "rviz_interface.hpp"


rviz_interface::rviz_interface(){
  if (!ros::isInitialized()) {
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "basic_shapes");
  }
  nh = ros::NodeHandlePtr(new ros::NodeHandle);


  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

}

void rviz_interface::loop(std::atomic<bool>& program_is_running){
  //ros::Publisher marker_array_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 1);


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE_LIST;

  uint32_t nods_num = 5;


  //visualization_msgs::MarkerArray markerArray;


  //for (uint32_t i = 0; i < nods_num; i++) {


    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.id = 0;
    marker.header.frame_id = "/my_frame";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker_array_pub.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    /*marker.pose.position.x = (float)i*1.0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    */

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
    for (uint32_t i = 0; i < nods_num; i++) {
      geometry_msgs::Point point;

      point.x = (float)i*1.0;
      point.y = 0.0;
      point.z = 0.0;

      std_msgs::ColorRGBA c;
      c.r = (float)i/10.0;
      c.g = 0;
      c.b = 0;
      c.a = 1;

      marker.points.push_back(point);
      marker.colors.push_back(c);
      //if(i < (nods_num-1))
      //  markerArray.markers.push_back(marker);

        //marker_array_pub.publish(markerArray);

        //r.sleep();

    }

  //uint8_t id_ = 0;
//  for(const visualization_msgs::Marker &marker_ : markerArray.markers){
    //marker_.id = id_;
    //id_++;

  //  printf("\ndata: %g", marker_.pose.position.x);
  //}

  while (ros::ok() && program_is_running)
  {



    // Publish the marker
  /*  while (marker_array_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }*/

    //marker_array_pub.publish(markerArray);
    marker_pub.publish(marker);

    /*// Cycle between different shapes
    switch (shape)
    {
    case visualization_msgs::Marker::CUBE:
      shape = visualization_msgs::Marker::SPHERE;
      break;
    case visualization_msgs::Marker::SPHERE:
      shape = visualization_msgs::Marker::ARROW;
      break;
    case visualization_msgs::Marker::ARROW:
      shape = visualization_msgs::Marker::CYLINDER;
      break;
    case visualization_msgs::Marker::CYLINDER:
      shape = visualization_msgs::Marker::CUBE;
      break;
    }*/

    r.sleep();
  }
}
