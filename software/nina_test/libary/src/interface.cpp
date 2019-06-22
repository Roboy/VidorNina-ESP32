/* =========================================================================
SPIbus library is placed under the MIT License
Copyright 2017 Natanael Josue Rabello. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
 ========================================================================= */

 #include "interface.hpp"
 #include <stdio.h>
 #include <stdint.h>


 ros_interface::ros_interface(esp_mqtt_client_handle_t *mqtt_client_){
   mqttclient = mqtt_client_;
   topic_list_pub = &topic_buff_pub[0];

 }

 void ros_interface::push_pub(std::string topic, std::string data){
   int msg_id = 0;
   const char *topic_ = topic.c_str();
   const char *pub_data = data.c_str();
   //std::cout << "\nDATA: " << data;

   //esp_mqtt_client_stop(mqtt_client);
   //esp_mqtt_client_start(mqtt_client);

   //msg_id = esp_mqtt_client_publish(mqtt_client, topic_, pub_data, 0, 0, 1);
   msg_id = esp_mqtt_client_publish(*mqttclient, topic_, pub_data, 0, 0, 1);

   if(msg_id==0){
     printf("\nMSG COULDN'T BE PUBLISHED");
   }

 }

/*
 void ros_interface::push_pub_multi(std::string *topic, std::string *data,uint32_t size){
   int msg_id = 0;

   for(uint32_t i = 0; i < size; i++)
     const char *topic_ = *topic.c_str();
     const char *pub_data = *data.c_str();

     msg_id = esp_mqtt_client_publish(*mqttclient, topic_, pub_data, 0, 0, 1);
     topic++;
     data++;
     if(msg_id==0){
       printf("\nMSG COULDN'T BE PUBLISHED");
     }
  }

}*/

void ros_interface::creat_topics(string *ret_data, string base_topic, const char* names_[], uint32_t size_){

  uint32_t name_cnt = 0;

  //string *list_;
  //string list_buffer_[1000];

  //list_ = &list_buffer_[0];

  name_cnt = size_/8;
  //cout << name_cnt << "\n";

  for(uint32_t i = 0; i < name_cnt; i++){
    std::stringstream ss_;
    if(*names_[i] == '#'){
        i++;
        for(uint32_t j = 0; j < 30; j++){
            ss_ << base_topic <<names_[i]<<"/"<< j;
            //cout << ss_.str() << "\n";
            *ret_data++ = ss_.str();
            ss_.str("");
        }
    }else{
        ss_ << base_topic << names_[i];
        //cout << ss_.str() << "\n";;
        *ret_data++ = ss_.str();
    }

  }

}
