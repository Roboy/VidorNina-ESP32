#ifndef _INTERFACE_HPP_
#define _INTERFACE_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

class ros_interface{
public:
  ros_interface(esp_mqtt_client_handle_t *mqtt_client_);
  void push_pub(std::string topic, std::string data);
  //void push_pub_multi(std::string *topic, std::string *data,uint32_t size);


  string topic_buff_pub[4000];
  string *topic_list_pub;

  void creat_topics(string *ret_data,string base_topic, const char* names_[], uint32_t size_);


private:
  esp_mqtt_client_handle_t *mqttclient;

};

#endif
