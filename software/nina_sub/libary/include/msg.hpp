#ifndef _MSG_HPP_
#define _MSG_HPP_

//#include <ros/ros.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdio.h>

#include <sstream>
#include <iostream>
#include <vector>

#include "mqtt_client.h"

using namespace std;


#define MAX_VEC_SIZE 10
#define MAX_POINTER_SIZE 128

#define MAX_LIST_SIZE 10

//template <typename T_, typename C>
//void foo_(string *topic_, T_ *t, uint32_t vec_size,C *c);
//template <typename T,typename C_>
//void pub_multi(string *topic_, T *t, uint32_t vec_size,C_ *c);

class msg_gen{
  public:
    template <typename type_cust> void pub_multi(string *topic_,type_cust *t, uint32_t vec_size);

    msg_gen(esp_mqtt_client_handle_t *mqtt_client_);

    void push_pub(std::string topic, std::string data);

    //void pub_multi(string *topic_, T *t, uint32_t vec_size);
    void creat_topics(string *ret_data,string base_topic, const char* names_[], uint32_t size_);


    //string topic_buff_pub[MAX_POINTER_SIZE];
    //string *topic_list_pub;
    //string topic_buff_sub[MAX_POINTER_SIZE];
    //string *topic_list_sub;

  private:
    esp_mqtt_client_handle_t *mqttclient;

};

  struct mqtt_out{
    bool allow_input;
    float trigger_time[MAX_LIST_SIZE];
    uint8_t master_identifier[MAX_LIST_SIZE];
  };
  struct mqtt_in{
    std::vector<uint8_t> masterlist;
    bool     start_burst;
    bool     start_continiouse;
    bool     start_ptp_sync;
    uint32_t burst_cycles;
    bool allow_input;
  };

struct msg_mqtt{
  struct master_list{
    uint32_t start_ptp_sync;
    uint32_t start_burst;
    uint32_t start_continiouse_mode;
    uint32_t burst_cycles;
    uint32_t master_id_list[MAX_VEC_SIZE];
    const char* names[6] = {
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
    float trigger_time[MAX_VEC_SIZE];
    const char* names[4] = {
      "master_id",
      "enable_slave_input",
      "#",
      "trigger_time"
    };
  }system_ctl;

  struct {
    uint32_t id;
    float trigger_time[MAX_VEC_SIZE];
    uint32_t master_identifier[MAX_VEC_SIZE];
    const char* names[5] = {
      "id",
      "#",
      "trigger_time",
      "#",
      "master_identifier"
    };
  }time_msg;

  struct time_sync_msg{
    uint32_t id;
    float sync_time_div[MAX_VEC_SIZE];
    uint32_t cycle_cnt[MAX_VEC_SIZE];
    float sys_time[MAX_VEC_SIZE];
    const char* names[7] = {
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


template <typename type_cust>
void msg_gen::pub_multi(string *topic_,type_cust *t, uint32_t vec_size){
  if(vec_size == 0){
    vec_size = 1;
  }
  uint32_t name_cnt = 0;
  uint32_t num_arry_cnt = 0;

  name_cnt = sizeof(t->names)/sizeof(t->names[0]);
  cout << name_cnt << "\n";

  for(uint32_t i = 0; i < name_cnt; i++){
      if(*t->names[i] == '#'){
          num_arry_cnt++;
      }
  }

 //cout << "\n VEC SIZE: " << vec_size;
 //cout << "\n num_arry_cnt SIZE: " << num_arry_cnt;

 std::stringstream ss_;

 for (uint32_t *p = (uint32_t*)t;reinterpret_cast<uintptr_t>(p) < reinterpret_cast<uintptr_t>(t->names);p++){

      //const char *topic_ = *topic[data_cnt].c_str();
      //const char *pub_data = *data.c_str();

      if(reinterpret_cast<uintptr_t>(p)+(MAX_VEC_SIZE)*(4*num_arry_cnt)+4 < reinterpret_cast<uintptr_t>(t->names)){
          //cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
          //cout << "\nTOPIC: "<< *topic_++;
          //cout << "\nDATA : "<< *p;
          ss_ << *p;
          push_pub(*topic_++, ss_.str());
          //cout << ss_.str()
          ss_.str("");

      }else{
          for(uint32_t i = 0; i < vec_size; i++){
              //cout << "\nADDR: " << reinterpret_cast<uintptr_t>(p) << "--" << reinterpret_cast<uintptr_t>(t->names);
              //cout << "\nvecTOPIC: "<< *topic_++;
              //cout << "\nvecDATA : "<< *p++;
              ss_ << *p++;
              push_pub(*topic_++, ss_.str());
              ss_.str("");

          }
          cout << "\n----\n";
          for(uint32_t i = 0; i < (MAX_VEC_SIZE-vec_size); i++){
              topic_++;
              p++;
          }
      }
  }
}

/*

*/

#endif
