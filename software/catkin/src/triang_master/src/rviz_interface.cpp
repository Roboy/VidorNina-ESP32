#include "rviz_interface.hpp"

#define NUM_MASTERS 2
#define CORRECTION_FACTOR (700000*2)



void rviz_loop(std::atomic<bool>& program_is_running, std::vector<std::string> &rx_slave , std::vector<std::string> &rx_master, std::atomic<bool> & udp_waitForData_Flag, std::atomic<bool> & allow_tx){


  int argc = 0;
  char **argv = NULL;
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle nh;
  ros::Rate r(1000000);
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Publisher marker_pub_array = nh.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 1);

  visualization_msgs::Marker marker;
  visualization_msgs::MarkerArray mark_array;
  //ros::Publisher marker_array_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 1);


  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE_LIST;

  uint32_t nods_num = 5;

  std::stringstream ss_;
  std::string s_;
  //visualization_msgs::MarkerArray markerArray;


  //for (uint32_t i = 0; i < nods_num; i++) {


    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.id = 0;
    marker.header.frame_id = "/my_frame";
    //marker.header.stamp = ros::Time::now();

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

    ros::Duration lifetime_;

    marker.lifetime = lifetime_.fromSec(2);
    /*for (uint32_t i = 0; i < nods_num; i++) {
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

    }*/

  //uint8_t id_ = 0;
//  for(const visualization_msgs::Marker &marker_ : markerArray.markers){
    //marker_.id = id_;
    //id_++;

  //  printf("\ndata: %g", marker_.pose.position.x);
  //}
  //std::vector<std::string> ;

  data_pars p(&marker);

  while(allow_tx != true);
  while(rx_master.size() < NUM_MASTERS );//|| rx_slave.size() < 1);
  usleep(10000);
  rx_master.clear();
  rx_slave.clear();

  uint8_t marker_pub_cnt = 0;

  while (ros::ok() && program_is_running)
  {


    int wait_cnt_udp = 0;
    if(allow_tx == false){
      //if(wait_cnt_udp = ;
      //rx_master.clear();
      //rx_slave.clear();
      //std::cout << "\nALLOW TX .. [ROS] " << allow_tx;
      uint8_t marker_cnt = 0;
      udp_waitForData_Flag = true;
    	while(udp_waitForData_Flag){
    		//std::cout << "\nRX SIZE2: " << rx_master.size();

        //std::cout << "\nMASTER SIZE: " << rx_master.size();
        //std::cout << "\nSLAVE SIZE: " << rx_slave.size();
        //std::cout << "\n1MASTER SIZE: " << rx_master.size();
        //std::cout << "\n1SLAVE SIZE: " << rx_slave.size();
        if(rx_master.size() >= NUM_MASTERS){ //&& rx_slave.size() >= 3){

          usleep(100);

          //std::cout << "\n2MASTER SIZE: " << rx_master.size();
          //std::cout << "\n2SLAVE SIZE: " << rx_slave.size();



        /*  for(uint8_t j = 0; j < rx_master.size(); j++){
            printf("\nMASTER[DATA]: %s", rx_master[j].c_str());
          }
          for(uint8_t j = 0; j < rx_slave.size(); j++){
            printf("\nSLAVE[DATA]: %s", rx_slave[j].c_str());
          }*/

          marker.id ++;
          ss_.str("");
          ss_ << "basic_shapes" << (int)marker.id;
          //marker.ns = ss_.str();
          //std::cout <<"\nMARKER NS: " << marker.ns ;

          //mark_array.markers.clear();
          marker.points.clear();
          p.parse(rx_master, rx_slave);
          p.calc_kartes();

          //


          //marker.header.stamp = ros::Time::now();
          marker_pub.publish(marker);

          //mark_array.markers.push_back(marker);
          //mark_array.markers.insert(mark_array.markers.begin(),marker);

          marker_pub_array.publish(mark_array);
          //marker_cnt++;
/*
          if(marker_cnt > 10){
            //marker.action = visualization_msgs::Marker::DELETE;
            cout << "\n size of marker: " << (int) mark_array.markers.size() << " .. " << (int) mark_array.markers.size()
            //mark_array.markers.pop_back();
            marker_cnt = 9;
          }*/
          //marker_pub.publish(marker);

          //if(marker.id > 100){
        //    marker.id = 0;;
        //  }

          //rx_master.clear();
          //rx_slave.clear();

          //rx_master.pop_back();
          //rx_master.pop_back();
          //rx_slave.pop_back();
          //rx_slave.pop_back();
          //rx_slave.pop_back();

          //if(rx_master.size() != 0){
          //  rx_master.clear();
          //  rx_slave.clear();
          //}

          //p.sort_data();



          //std::cout << "\nRDY to send";
    			udp_waitForData_Flag = false;
          wait_cnt_udp = 0;

          rx_master.clear();
          rx_slave.clear();


    			break;

        }
        //udp_waitForData_Flag = true;
        //usleep(20000);








        //if(udp_waitForData_Flag = false;)
          wait_cnt_udp++;
          if(wait_cnt_udp > 429496720){
            wait_cnt_udp = 0;
            printf("not every base could be reached");
            rx_master.clear();
            rx_slave.clear();
            udp_waitForData_Flag = false;
            break;
          }
    	}
    }



    //std::cout << "\nROS...M" << (int)rx_master.size();
    //std::cout << "\nROS...S" << (int)rx_slave.size();


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

    /*marker_pub.publish(marker);
    marker_pub_cnt ++;
    if(marker_pub_cnt > 30){
      marker.points.clear();
      marker.colors.clear();
      marker_pub_cnt = 0;
    }*/

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

data_pars::data_pars(visualization_msgs::Marker *marker_){
  marker = marker_;

}
void data_pars::send_datapoints(int id_, int des_id_, double dist_){
  dist_ = dist[id_][des_id_];
  dist_ = dist_ * 10;

  //marker->points.clear();
  geometry_msgs::Point obj;
  std_msgs::ColorRGBA c;

  obj.x = 0.0;
  obj.y = 0.0;
  obj.z = 0.0;

  c.g = 0;
  c.b = 0.5;
  c.a = 1;

  c.r = 0;


  marker->points.push_back(obj);
  marker->colors.push_back(c);


  for(uint8_t i = 0; i < 2; i++){


    switch (id_) {
      case 0:
        if(des_id_ != 2){
          obj.x = dist_;
          obj.y = 0.0;
          obj.z = 0.0;
          c.r = 1;
        }else{
          obj.x = 0.0;
          obj.y = 0.0;
          obj.z = dist_;
          c.r = 1;
        }
        break;
      case 1:
          obj.x = 0.0;
          obj.y = dist_;
          obj.z = 0.0;
          c.r = 0.5;
        break;
      default:
        break;
      }


    //marker->points.pop_back();
    marker->points.push_back(obj);
    marker->colors.push_back(c);
    //marker->header.stamp = ros::Time::now();
  }


}

double data_pars::calc_distance (uint32_t t1, uint32_t t2){
  uint32_t buffer = 0;
  int64_t div_buff = t2 - t1;
  uint32_t div_time = std::abs(div_buff);


  buffer = SOUND_SPEED * div_time;
  return(DISTANCE_FACTOR * buffer);
}


void data_pars::calc_kartes(){
  //unsigned int data_match[20][MAX_ARRAY_SIZE];
  //unsigned int data_master[20];

  const double scale = 10.0;

  std_msgs::ColorRGBA c;

  double calc_buffer[10];
  for(uint8_t i = 0; i < 3; i++){
    switch (i) {
      case 0:
          point.x = 0.0;
          point.y = 0.0;
          point.z = 0.0;
          c.r = 0;
        break;
      case 1:
          c.r = 0.5;
          point.x = abs(dist[0][1]) * scale;
          point.y = 0.0;
          point.z = 0.0;
        break;
      case 2:
          c.r = 1;
          calc_buffer[0] = 2 * dist[0][2] * dist[0][1];
          calc_buffer[4] = dist[0][2]*dist[0][2];
          calc_buffer[5] = dist[0][1]*dist[0][1];
          calc_buffer[1] = 2 * (calc_buffer[4]  +  -(dist[1][2]*dist[1][2]));
          calc_buffer[2] = calc_buffer[1] /  calc_buffer[0];
          point.x = dist[0][2] * calc_buffer[2];
          point.x = abs(point.x);

          calc_buffer[3] = dist[0][2]*dist[0][2] - (point.x*point.x);
          calc_buffer[3] = abs(calc_buffer[3]);
          point.y = sqrt(calc_buffer[3]);
          point.x = point.x * scale;
          point.y = point.y * scale;
          point.z = 0.0;

          //printf("\nPOS: %g/%g/%g ... %g/%g", point.x, point.y, point.z, calc_buffer[2] , calc_buffer[3] );
        break;
      default:
          point.x = 1.0;
          point.y = 1.0;
          point.z = 1.0;
        break;

    }

    c.g = 0;
    c.b = 0.5;
    c.a = 1;

    //marker->points.clear();
    //marker->colors.clear();

    marker->points.push_back(point);
    marker->colors.push_back(c);
  }


}
void data_pars::sort_data(){

  int d;

  for(uint8_t i = 0; i < NUM_MASTERS; i++){
    for(uint8_t j = 0; j < num_slave_data; j++){
      if((data_match[i][j] != 1337 || data_match[i][j] != 1338) && ( i != j)){
        if( data_match[i][j] == 0){
          dist[i][j] = 0.0;
          d = 0;
        }else{
          d = data_master[i] - data_match[i][j];
          dist[i][j] = dist[i][j] = calc_distance(data_master[i], data_match[i][j]);
        }

      }else{
        d = 0;
        dist[i][j] = 0.0;
      }
      //printf("\nDIST[%d%d]: %g {FROM:[M] %u - [S] %u}\n", i, j, dist[i][j], data_master[i], data_match[i][j]);
      printf("\nDIST[%u - %u]: %d", data_master[i], data_match[i][j], d);
    }
  }


  calc_kartes();

}



void data_pars::parse(std::vector<std::string> input, std::vector<std::string> input_slave){
  static std::string set_data_slave[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE]; //[MASTER ID][SLAVE ID]
  static std::string single_data_slave[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
  static std::string single_data_master[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];

  unsigned int dis_ticks[MAX_ARRAY_SIZE];
  unsigned int calc_buffer;

  double dis[MAX_ARRAY_SIZE];

  uint8_t dest_id;
  uint8_t send_id;
  double dis_buffer;



  uint8_t set_cnt = 0;
  int size_buffer = input.size();
  num_slave_data = size_buffer;
  int slave_len = 0;

  uint8_t foo_cnt[20];
  for(uint8_t i = 0; i < sizeof(foo_cnt); i++){
    foo_cnt[i] = 0;
  }

  for(uint8_t i = 0; i < size_buffer; i++){
    slave_len = parse_string(input.back(), &single_data_master[i][0], ESCKEY_NEW_DATA);
    //std::cout << "\nbuffer size: " << (int)input.size();
    //std::cout << "\nRAW DATA: " << input.back();
    input.pop_back();
    //std::cout << "\nRAW DATA: " << input.back();
    if(single_data_master[i][0] == "=" && single_data_master[i][2] != "420" ){
      if(single_data_master[i][2] == "1"){
        send_id = std::atoi(single_data_master[i][1].c_str());
        uint8_t array_cnt = std::atoi(single_data_master[i][1].c_str());
        dis_ticks[array_cnt] = (unsigned int) std::atoi(single_data_master[i][3].c_str()) - CORRECTION_FACTOR;
        //std::cout << "\nDistDATACLK: " <<  (unsigned int) dis_ticks[array_cnt];
        calc_buffer = SOUND_SPEED * dis_ticks[array_cnt] ;
        dis[array_cnt] = (double)calc_buffer * FPGA_CLK_T;
        dis[array_cnt] = dis[array_cnt] / 2;
        dis_buffer = dis[array_cnt];

        //if(dis[array_cnt] < 10.0){
          //printf("\nID: %d", array_cnt);
        //  send_datapoints(array_cnt, dis[array_cnt]);
        //}


      }
      else{
        dest_id = std::atoi(single_data_master[i][1].c_str());
      }
    }else{
      ;//break;
    }
  }

  //double calc_buffer[10];
  printf("\nDISTANCE: %g", dis_buffer);
  if(dis_buffer < 10.0){
    dist[send_id][dest_id] = dis_buffer;
    //send_datapoints(send_id, dest_id, dis_buffer);
  }


  //usleep(10000);;






  /*static std::string set_data_slave[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE]; //[MASTER ID][SLAVE ID]
  static std::string single_data_slave[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
  static std::string single_data_master[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];


  //std::cout << "\nSTART PARSE :" << (int) input_slave.size() << "..." << input_slave.back();

  uint8_t set_cnt = 0;
  int size_buffer = input_slave.size();
  num_slave_data = size_buffer;
  int slave_len = 0;

  uint8_t foo_cnt[20];
  for(uint8_t i = 0; i < sizeof(foo_cnt); i++){
    foo_cnt[i] = 0;
  }
  for(uint8_t i = 0; i < size_buffer; i++){

    slave_len = parse_string(input_slave.back(), &set_data_slave[i][0], ESCKEY_NEW_DATASET);
    input_slave.pop_back();

    for(uint8_t j = 0; j < slave_len; j++){

      int len = parse_string(set_data_slave[i][j], &single_data_slave[set_cnt][0], ESCKEY_NEW_DATA);//ESCKEY_NEW_DATA
      if(std::atoi(single_data_slave[set_cnt][0].c_str()) < 0){
        single_data_slave[set_cnt][0] = "0";
      }
      data_match[foo_cnt[std::atoi(single_data_slave[set_cnt][1].c_str())]][std::atoi(single_data_slave[set_cnt][1].c_str())] = std::atoi(single_data_slave[set_cnt][2].c_str());


      //std::cout << "\n[DATA_S: " << (int)foo_cnt[std::atoi(single_data_slave[set_cnt][1].c_str())] << " + SLAVEID: " << single_data_slave[set_cnt][1]  << "] " << single_data_slave[set_cnt][2];
      foo_cnt[std::atoi(single_data_slave[set_cnt][1].c_str())]++;
      set_cnt++;
    }
    //std::cout << "\nlen " << len;
    //for(uint8_t i = 0; i < len; i ++){
    //  std::cout << "\n[DATA: " << (int) i << "] " << set_data_slave[set_cnt][i];
    //}

    //std::cout << "\n";
    set_cnt++;
  }


  //for(uint8_t j = 0; j <= set_cnt; j++){
  //  int len = parse_string(set_data_slave[j][0], &single_data_slave[j][0], ESCKEY_NEW_DATA);//ESCKEY_NEW_DATA
  //}


  //std::cout <<"master data:" << input.size();
  size_buffer = input.size();
  for(uint8_t j = 0; j < size_buffer; j++){
    int len = parse_string(input.back(), &single_data_master[j][0], ESCKEY_NEW_DATA);//ESCKEY_NEW_DATA
    input.pop_back();


    data_master[std::atoi(single_data_master[j][0].c_str())] = std::atoi(single_data_master[j][1].c_str());
    if(j > 0 && std::atoi(single_data_master[j][0].c_str()) == (std::atoi(single_data_master[j][0].c_str())-1)){
      std::cout << "\n!!!! ERROR TWO TIMES SAME MASTER";
    }

    //std::cout << "\n[DATA_M: " << single_data_master[j][0] << "] " << single_data_master[j][1];

  }

*/
}

int data_pars::parse_string(std::string inData, std::string *outdata, char identifier){
  int size = 0;
  const char *c = inData.c_str();
  char char_buffer[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
  std::string outdata_buffer[MAX_ARRAY_SIZE];
  uint8_t i=0;
  uint8_t j=0;

  //uint8_t j = 0;
  //std::cout << "\nINSTRING " << inData;

  for(i=0; i < 200; i++){
    if(*c == identifier){
      char_buffer[size][i-j] = '\0';
      outdata[size] = char_buffer[size];
      size ++;
      c++;
      j = i;
    }else if(*c == '='){
      char_buffer[size][i-j] = '=';
      outdata[size] = char_buffer[size];
      size ++;
      c++;
      j = i;
    }
    if(*c == NULL){
      break;
    }
    char_buffer[size][i-j] = *c++;
  }

  char_buffer[size][i-j] = '\0';
  outdata[size] = char_buffer[size];

  //outdata = &outdata_buffer[0];
  size++;
  return size;
}
