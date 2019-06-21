/* =========================================================================
The MIT License (MIT)

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

 #include <stdio.h>
 #include <stdint.h>
 #include <stddef.h>
 #include <alloca.h>
 #include <string>
 #include <cstring>

 #include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

 #include "esp_system.h"
 //#include "esp_wifi.h"
 #include "esp_log.h"
 #include "esp_err.h"

 #include "lwip/sockets.h"
 #include "lwip/dns.h"
 #include "lwip/netdb.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "config.hpp"

#include "SPIbus.hpp"
#include "ninaWifi.hpp"
//#include "mqtt.hpp"
//#include "mqtt_client.h"
#include "mqtt_client.h"
//#include "PubSubClient.h"

#include "nvs_flash.h"

#include "interface.hpp"
#include "FpgaVidor.hpp"


using namespace std;


#define SPI_MODE  1//original 0
#define MISO_PIN  19
#define MOSI_PIN  23
#define SCLK_PIN  18
#define CS_PIN    5
#define SPI_CLOCK SPI_MASTER_FREQ_16M   // 1 MHz


//static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event);
static void mqtt_app_start(void);
static void get_string(char *line, size_t size);

string foo_msg[ARRAY_SIZE] = "/topic/foo";


static const char *TAG = "PUBLISH_TEST";

static EventGroupHandle_t mqtt_event_group;
const static int CONNECTED_BIT = BIT0;

static esp_mqtt_client_handle_t mqtt_client = NULL;

static char *expected_data = NULL;
static char *actual_data = NULL;
static size_t expected_size = 0;
static size_t expected_published = 0;
static size_t actual_published = 0;
static int qos_test = 0;

void push_pub(string topic, string data){
  int msg_id = 0;
  //const char *topic_ = topic.c_str();
  //const char *pub_data = data.c_str();

  //esp_mqtt_client_stop(mqtt_client);
  //esp_mqtt_client_start(mqtt_client);

  //msg_id = esp_mqtt_client_publish(mqtt_client, topic_, pub_data, 0, 0, 1);
  msg_id = esp_mqtt_client_publish(mqtt_client, "/topic/qos3", "foo data", 0, 0, 1);

  if(msg_id==0){
    printf("\nMSG COULDN'T BE PUBLISHED");
  }

}

extern "C" void app_main() {
    printf("--START-- \n");
    fflush(stdout);

    uint32_t in_time, trave_time;
    double distance;
    string msg_sub_[10];

    SPI_t &mySPI = vspi;  // vspi and hspi are the default objects

    ESP_ERROR_CHECK( mySPI.begin(MOSI_PIN, MISO_PIN, SCLK_PIN,8));
    ESP_ERROR_CHECK( mySPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &mySPI.device_fpga));

    hardware_interface hw (&mySPI);

    ESP_ERROR_CHECK(nvs_flash_init());
    WIFI wifi;

    mqtt_app_start();

    hw.allow_input_trigger();
    printf("\nID: %d", hw.getID());

    hw.stop_US_out();
    hw.piezo_set_burst_cycles(3);
    hw.piezo_burst_out();

    //init time should be given via ntp ...
    //ptp.time_data.sys_time = 100;
    //printf("set rtc to ini\n\n");
    //hw.set_time(ptp.time_data.sys_time);

    printf("\n\n=====================================");
    printf("\n\n  start loopy");
    printf("\n\n=====================================");

    char foo;

    //uint32_t i;

    char line[256];
    char pattern[32];
    char transport[32];
    int repeat = 0;

    for(uint16_t j=0; j<10; j++){
      hw.piezo_burst_out();
      //hw.start_US_out();
      printf("\ntime : %d", hw.US_start_time);//hw.read_trigger_time());
      push_pub("/topic/qos3", "foo data");
    }

    while(1){
      //msg_sub_[0]="/topic/foo";
      //msg_id = esp_mqtt_client_subscribe(client, "/topic/foo", 0);
      //printf("\ntime : %d", hw.US_start_time); //!!!!!!!!!!!!!!!!!!!!!!!!! never start that befor piezo burst out
      hw.piezo_burst_out();
      //hw.start_US_out();
      printf("\ntime : %d", hw.US_start_time);//hw.read_trigger_time());

      /*
      modef.start_conversation(); //only does something if master changes

      if(modef.burst_enable)
        modef.conversation();

      //ros tells the master to ptp sync
      if(modef.sync_enable){
        cout << "\nsync was enabled\n";
        usleep(100000);
        modef.sync_enable = false;
        ptp.update_time(modef.id == MASTER);  //TODO MASTER zu current master
        cout << "\nCurrentSysTime: " << ptp.time_data.sys_time;
        cout << "\nCurrentClkCycleCntTime: " << ptp.time_data.cycle_cnt;
        cout << "\nCurrentSyncDivTime: " << ptp.time_data.sync_time_div;
      }

      */

      //get_string(line, sizeof(line));
      //msg_id = esp_mqtt_client_publish(mqtt_client, "/topic/qos3", "buhai", 0, 1, 0);

      //esp_mqtt_client_stop(mqtt_client);
      //esp_mqtt_client_start(mqtt_client);

      //push_pub("/topic/qos3", "buhai");

      //hw.read_trigger_time());

      //sscanf(line, "%s %s %d %d %d", transport, pattern, &repeat, &expected_published, &qos_test);
      /*pattern = ;
      repeat = 1;
      expected_published = 1;
      qos_test = 0;

      ESP_LOGI(TAG, "PATTERN:%s REPEATED:%d PUBLISHED:%d\n", pattern, repeat, expected_published);
      int pattern_size = strlen(pattern);
       free(expected_data);
       free(actual_data);
       actual_published = 0;
       expected_size = pattern_size * repeat;
       expected_data = (char*)malloc(expected_size);
       actual_data = (char*)malloc(expected_size);
       for (int i = 0; i < repeat; i++) {
           memcpy(expected_data + i * pattern_size, pattern, pattern_size);
       }*/
       //printf("EXPECTED STRING %.*s, SIZE:%d\n", expected_size, expected_data, expected_size);
       //esp_mqtt_client_stop(mqtt_client);

       //esp_mqtt_client_set_uri(mqtt_client, CONFIG_EXAMPLE_BROKER_TCP_URI);

       //xEventGroupClearBits(mqtt_event_group, CONNECTED_BIT);
       //esp_mqtt_client_start(mqtt_client);
       /*ESP_LOGI(TAG, "Note free memory: %d bytes", esp_get_free_heap_size());
       //xEventGroupWaitBits(mqtt_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);

      for (int i = 0; i < expected_published; i++) {
           int msg_id = esp_mqtt_client_publish(mqtt_client, "/test/pub", expected_data, expected_size, qos_test, 0);
           ESP_LOGI(TAG, "[%d] Publishing...", msg_id);
       }*/
       /*
      for(uint32_t j = 0; j<10000;j++){
          uint8_t delay_cnt=0;
          delay_cnt++;
      }
      printf("\n========================\n");
      esp_mqtt_client_handle_t client = event->client;
      int msg_id;
      msg_id = esp_mqtt_client_publish(client, "/topic/qos3", "fuu data", 0, 1, 0);
      ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);
      */

  }

    mySPI.removeDevice(mySPI.device_fpga);
    mySPI.close();
    vTaskDelay(portMAX_DELAY);
}

/*

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    uint32_t num_cnt = 2;



    //foo_msg.c_str(),""};
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI("MQTT", "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos3", 0);
            ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);

            //msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            //ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);

            //msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            //ESP_LOGI("MQTT", "sent unsubscribe successful, msg_id=%d", msg_id);

            //msg_id = esp_mqtt_client_subscribe(client, glob_sub[0], 2);
            //ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);


            break;
        case MQTT_EVENT_DISCONNECTED:
            ;//ESP_LOGI("MQTT", "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI("MQTT", "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos3", "datapub1", 0, 0, 0);
            //msg_id = esp_mqtt_client_publish(client, "/topic/fuckoff", "data", 0, 2, 0);
            ESP_LOGI("MQTT", "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ;//ESP_LOGI("MQTT", "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ;//ESP_LOGI("MQTT", "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI("MQTT", "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI("MQTT", "MQTT_EVENT_ERROR");
            break;
    }
    return ESP_OK;
}



static void mqtt_app_start()
{
    const esp_mqtt_client_config_t mqtt_cfg = {mqtt_event_handler, "mqtt://192.168.1.1", "mqtt://192.168.1.1"};



    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

}
*/




static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    static int msg_id = 0;
    static int actual_len = 0;
    // your_context_t *context = event->context;
    switch (event->event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        //xEventGroupSetBits(mqtt_event_group, CONNECTED_BIT);
        msg_id = esp_mqtt_client_subscribe(client, "/topic/qos3", qos_test);
        ESP_LOGI(TAG, "/topic/qos3 sent subscribe successful, msg_id=%d", msg_id);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        printf("ID=%d, total_len=%d, data_len=%d, current_data_offset=%d\n", event->msg_id, event->total_data_len, event->data_len, event->current_data_offset);
        /*if (event->topic) {
            actual_len = event->data_len;
            msg_id = event->msg_id;
        } else {
            actual_len += event->data_len;
            // check consisency with msg_id across multiple data events for single msg
            if (msg_id != event->msg_id) {
                ESP_LOGI(TAG, "Wrong msg_id in chunked message %d != %d", msg_id, event->msg_id);
                abort();
            }
        }
        memcpy(actual_data + event->current_data_offset, event->data, event->data_len);
        if (actual_len == event->total_data_len) {
            if (0 == memcmp(actual_data, expected_data, expected_size)) {
                printf("OK!");
                memset(actual_data, 0, expected_size);
                actual_published ++;
                if (actual_published == expected_published) {
                    printf("Correct pattern received exactly x times\n");
                    ESP_LOGI(TAG, "Test finished correctly!");
                }
            } else {
                printf("FAILED!");
                abort();
            }
        }*/
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
    return ESP_OK;
}



static void mqtt_app_start(void)
{
  const esp_mqtt_client_config_t mqtt_cfg = {mqtt_event_handler, "mqtt://192.168.1.1", "mqtt://192.168.1.1"};

  //esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_start(mqtt_client);
}

static void get_string(char *line, size_t size)
{

    int count = 0;
    while (count < size) {
        int c = fgetc(stdin);
        if (c == '\n') {
            line[count] = '\0';
            break;
        } else if (c > 0 && c < 127) {
            line[count] = c;
            ++count;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
