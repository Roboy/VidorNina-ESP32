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
 #include <string>

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

#include "SPIbus.hpp"
#include "ninaWifi.hpp"
//#include "mqtt.hpp"
#include "mqtt_client.h"

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


static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event);
static void mqtt_app_start(void);

string foo_msg = "/topic/foo";

extern "C" void app_main() {
    printf("--START-- \n");
    fflush(stdout);

    uint32_t in_time, trave_time;
    double distance;
    string msg_sub_[10];

    //nvs_flash_init();
    //wifi_init();
    WIFI wifi;
    //MQTT mqtt;

    SPI_t &mySPI = vspi;  // vspi and hspi are the default objects

    spi_device_handle_t device;
    ESP_ERROR_CHECK( mySPI.begin(MOSI_PIN, MISO_PIN, SCLK_PIN,8));
    //ESP_ERROR_CHECK( mySPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &device));
    ESP_ERROR_CHECK( mySPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &mySPI.device_fpga));

    hardware_interface hw (&mySPI);
    //fpga_mode modef(&hw);
    //time_sync ptp(&hw);
    //msg_sub_[0] = "/topic/foo";

    //foo_msg = "/topic/foo";
    mqtt_app_start();

    hw.allow_input_trigger();
    printf("\nID: %d", hw.getID());

    hw.stop_US_out();
    hw.piezo_set_burst_cycles(3);

    //init time should be given via ntp ...
    //ptp.time_data.sys_time = 100;
    //printf("set rtc to ini\n\n");
    //hw.set_time(ptp.time_data.sys_time);

    printf("\n\n=====================================");
    printf("\n\n  start loopy");
    printf("\n\n=====================================");

    char foo;

    uint32_t i;

    while(1){
      //msg_sub_[0]="/topic/foo";
      //msg_id = esp_mqtt_client_subscribe(client, "/topic/foo", 0);
      printf("\ntime : %d", hw.US_start_time);

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

      for(uint32_t j = 0; j<1000;j++)
          ;


  }

    mySPI.removeDevice(mySPI.device_fpga);
    mySPI.close();
    vTaskDelay(portMAX_DELAY);
}




static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    const char *msg_sub_ = "/topic/foo";//foo_msg.c_str(),""};
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI("MQTT", "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
            ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            ESP_LOGI("MQTT", "sent unsubscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, msg_sub_, 2);
            ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);
            /*for(uint8_t i=0; i<10;i++){
              if(msg_sub_[i] != ""){
                msg_id = esp_mqtt_client_subscribe(client, msg_sub_[i], 1);
                ESP_LOGI("MQTT", "sent subscribe successful, msg_id=%d", msg_id);
              }
            }*/
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI("MQTT", "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI("MQTT", "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            ESP_LOGI("MQTT", "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI("MQTT", "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI("MQTT", "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
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



static void mqtt_app_start(string msg_sub[])
{
    const esp_mqtt_client_config_t mqtt_cfg = {mqtt_event_handler, "mqtt://192.168.1.1", "mqtt://192.168.1.1"};



    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

}
