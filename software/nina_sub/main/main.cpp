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
//#include "driver/spi_master.h"
#include "SPIbus.hpp"
#include "FpgaVidor.hpp"
#include "mode_ctl.hpp"
#include "msg.hpp"

//#include "esp_sntp.h"

static const char *TAG = "MQTTS_SAMPLE";

static uint32_t sys_time_debug = 0;

static EventGroupHandle_t wifi_event_group;
const static int CONNECTED_BIT = BIT0;
static bool xUserWaitflage_main_cpp = false;

//Config
#ifndef CONFIG_WIFI_SSID
#define CONFIG_WIFI_SSID "roboy"
#endif

#ifndef CONFIG_WIFI_PASSWORD
#define CONFIG_WIFI_PASSWORD "wiihackroboy"
#endif

static esp_mqtt_client_handle_t mqtt_client = NULL;

#define SPI_MODE  1//original 0
#define MISO_PIN  19
#define MOSI_PIN  23
#define SCLK_PIN  18
#define CS_PIN    5
#define SPI_CLOCK 1000000//SPI_MASTER_FREQ_16M   // 1 MHz



static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);

            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            esp_wifi_connect();
            xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
            break;
        default:
            break;
    }
    return ESP_OK;
}

static void wifi_init(void)
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    wifi_ap_config_t wifi_cfg = {CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD};
    wifi_config_t wifi_config = {wifi_cfg};

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_LOGI(TAG, "start the WIFI SSID:[%s] password:[%s]", CONFIG_WIFI_SSID, "******");
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "Waiting for wifi");
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            //msg_id = esp_mqtt_client_subscribe(client, "/topic/qos3", 0);
            //ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            //msg_id = esp_mqtt_client_publish(client, CONFIG_EMITTER_CHANNEL_KEY"/topic/", "data", 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            //printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            //printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ;
            break;
    }
    return ESP_OK;
}


//static esp_err_t foo(esp_mqtt_event_handle_t event){
  //printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
//}

template <typename user_class>
void search_topic_handl(user_class *c, string topic_, string data_){
  for(uint16_t i = 0; i < sizeof(c->topic_list_sub)/sizeof(c->topic_list_sub[0]); i++){
    if(topic_ == c->topic_list_sub[i]){
        //printf("\n....HEURIKA....\n");
        c->select_subf(i,data_);
    }
  }
    if(topic_== "/time/set_zero"){
      //sys_time_debug = 0;
      //cout << "\nSET TIME";
      c->set_time(0);
    }
}
static void custom_handl(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
  //printf("\n===HELLO I'm custom ==");
  esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
  fpga_mode *mode_ = (fpga_mode *)handler_args;

  //foo(event_data);
  //esp_mqtt_event_handle_t event = event_data;

  printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
  printf("DATA=%.*s\r\n", event->data_len, event->data);

  string s_topic;
  string s_data;

  for(uint8_t i = 0; i < event->topic_len; i++)
    s_topic += *event->topic++;
  for(uint8_t i = 0; i < event->data_len; i++)
    s_data += *event->data++;

  search_topic_handl(mode_,s_topic,s_data);

  //return ESP_OK;
}
static void mqtt_event_handler_(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
  printf("default handl");
}

static void mqtt_app_start(esp_mqtt_client_handle_t *client_)
{
  //const esp_mqtt_client_config_t mqtt_cfg = {mqtt_event_handler ,NULL ,"mqtt://192.168.1.1", "mqtt://192.168.1.1"};
  const esp_mqtt_client_config_t mqtt_cfg = {NULL ,NULL ,"mqtt://192.168.1.1", "mqtt://192.168.1.1"};


  //esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
  *client_ = esp_mqtt_client_init(&mqtt_cfg);
  //esp_mqtt_client_register_event(*client_, MQTT_EVENT_CONNECTED, mqtt_event_handler_, *client_);
  esp_mqtt_client_start(*client_);

}

/*
static void initialize_sntp(void)
{
    char strftime_buf[64];

    ESP_LOGI("NTP", "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    //sntp_set_time_sync_notification_cb(time_sync_notification_cb);
//#ifdef CONFIG_SNTP_TIME_SYNC_METHOD_SMOOTH
//    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
//#endif
    sntp_init();


    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 10;
    vTaskDelay(2000 / portTICK_PERIOD_MS);

  //  while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
//        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
//        vTaskDelay(2000 / portTICK_PERIOD_MS);
  //  }
    time(&now);
    localtime_r(&now, &timeinfo);

    setenv("TZ", "EST5EDT,M3.2.0/2,M11.1.0", 1);
    tzset();
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in New York is: %s", strftime_buf);

    //ESP_ERROR_CHECK( example_disconnect() );
}
*/



//static void wifi_init(void)
//static int wait_for_user_input = 0;
extern "C" void app_main() {
    printf("--START-- \n");
    fflush(stdout);


    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);


    SPI_t &mySPI = vspi;  // vspi and hspi are the default objects


    printf("\nbegin SPI");
    ESP_ERROR_CHECK( mySPI.begin(MOSI_PIN, MISO_PIN, SCLK_PIN,8));
    ESP_ERROR_CHECK( mySPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &mySPI.device_fpga));

    //struct msg_mqtt msg_mqtt;
    msg_gen transmit (&mqtt_client);
    hardware_interface hw (&mySPI,&transmit);
    fpga_mode modef(&hw,&transmit,&mqtt_client);

    uint8_t buffer[6];

    printf("\n\n=====================================");
    printf("\n\n  start loopy");
    printf("\n\n=====================================");

    nvs_flash_init();
    wifi_init();
    mqtt_app_start(&mqtt_client);
    esp_mqtt_client_register_event(mqtt_client, MQTT_EVENT_DATA, custom_handl, &modef);


    //transmit.push_pub("/init", "0");
    (void)esp_mqtt_client_publish(mqtt_client, "/init", "1", 0, 0, 1);
    for(uint8_t i=0; i < 1000; i++){
      if(esp_mqtt_client_subscribe(mqtt_client, "/init", 0) > 0)
        break;
    }
    (void)esp_mqtt_client_unsubscribe(mqtt_client, "/init");
    (void)esp_mqtt_client_subscribe(mqtt_client, "/time/set_zero", 1) ;

    hw.allow_input_trigger();
    printf("\nID: %d", hw.getID());

    hw.stop_US_out();
    //hw.piezo_set_burst_cycles(3);
    //hw.piezo_burst_out();



    modef.transmission_init(&mqtt_client);

    (void)esp_mqtt_client_subscribe(mqtt_client, "/triangulation/testno", 0);


    //cout <<"\n Start NTP SYNC\n";
    //sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    //while (sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
    //initialize_sntp();

    int i = 0;
    int wait_for_user_input = 0;

    //int8_t cRxedChar, cInputIndex = 0;
    //Peripheral_Descriptor_t xConsole;

    std::stringstream ss_buffer_;
    unsigned int t_;
    int time_out_cnt = 0;


    while (1) {
        hw.piezo_set_burst_cycles(30);
        //cout << "\nALLOW Input trigger";
        /*
        hw.allow_input_trigger();
        //hw.allow_input_trigger();
        //while(hw.rdy_to_read());
        //t_ = 0;
        for(time_out_cnt = 0; time_out_cnt <= 4294967294; time_out_cnt++){
          if(!hw.rdy_to_read()){
            //time_dat = hw->read_trigger_time();
            t_ = hw.read_trigger_time();
            //cout << "\nTIME:" <<  +time_dat ; //<< " clk count : " << hw->read_trigger_time2();
            break;
          }
          //cout << "\nCNT:" <<  +time_out_cnt;
        }*/
        //for(time_out_cnt=0; time_out_cnt <= 4294967294; time_out_cnt++){
        //  if(hw->rdy_to_read())
        //    break;
        //}
        //cout << "\n time_out_cnt " << time_out_cnt;


        /*
        ss_buffer_ <<"[0]" << +(int)t_;
        transmit.push_pub("/triangulation/1/time_data/",ss_buffer_.str());
        ss_buffer_.str("");

        */


        //cout << "\nFPGA TIME: " << hw.read_time();
        //cout << "\nID: " <<  hw.getID();

        //modef.start_conversation();
        //modef.conversation();

        //hw.piezo_burst_out();
        //vTaskDelay(10000 / portTICK_PERIOD_MS);

      //hw.start_US_out();
        //printf("\ntime : %d", hw.US_start_time);//hw.read_trigger_time());

        //TODO ... do it via ros
        //for(int time_out_cnt = 0; time_out_cnt <= 4294967294; time_out_cnt++){
        //hw.allow_input_trigger();
        //for(int time_out_cnt = 0; time_out_cnt <= 3000; time_out_cnt++){
        //  cout << "\n" << +(int)hw.rdy_to_read() << " : " << +(int)time_out_cnt << " : " <<  (int)hw.read_trigger_time();
          /*if(!hw.rdy_to_read()){
            cout << "\nready to read " << time_out_cnt;
            break;
          }*/
        //}

        /*hw.allow_input_trigger();
        //while(hw.rdy_to_read());
        for(int time_out_cnt = 0; time_out_cnt <= 50000; time_out_cnt++){
          if(!hw.rdy_to_read()){
            cout << "\ncnt: " << (int)time_out_cnt << " time: " << +(unsigned int)hw.read_trigger_time();
            break;
          }
        }*/

        //cout << "\nIN:" << +(int)hw.rdy_to_read() << " : " << +(int)time_out_cnt << " : " <<  (int)hw.read_trigger_time();

      //  for(int time_out_cnt = 0; time_out_cnt <= 1000; time_out_cnt++){

      //    cout << "\nIN:" << +(int)hw.rdy_to_read() << " : " << +(int)time_out_cnt << " : " <<  (int)hw.read_trigger_time();
          /*if(!hw.rdy_to_read()){
            cout << "\nready to read " << time_out_cnt;
            break;
          }*/
        //}

        //cout << "\nBREAK";
        //cout <<"\ntrigger time: " <<  hw.read_trigger_time();

        //.............
        //vTaskDelay(500 / portTICK_PERIOD_MS);


        //ESP_ERROR_CHECK(mySPI.readBytes(mySPI.device_fpga, 0x3B, 6, buffer));


        //hw.start_US_out();

        //printf("\nread time %d", hw.read_time());
        //printf("\ntrigger time %d",hw.read_trigger_time());

        //xUserWaitflage_main_cpp =



        /*
        xUserWaitflage_main_cpp = true;
        while(xUserWaitflage_main_cpp){
          FreeRTOS_read( xConsole, &cRxedChar, sizeof( cRxedChar ) );

          scanf("\nScann data %d", &wait_for_user_input);
          vTaskDelay(1000 / portTICK_PERIOD_MS);
          //cin >> wait_for_user_input;
          cout << "wait for user input: " << wait_for_user_input << "\n";
          if(wait_for_user_input == 1)
            xUserWaitflage_main_cpp = false;
        }
        */
        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        //hw.piezo_set_burst_cycles(3);

        /*time_t now;
        struct tm timeinfo;
        time(&now);
        char strftime_buf[64];

        localtime_r(&now, &timeinfo);
        strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
        ESP_LOGI(TAG, "The current date/time in New York is: %s", strftime_buf);*/

        /*printf("\nUS_out");
        hw.start_US_out();
        //cin >> wait_for_user_input;
        vTaskDelay(500 / portTICK_PERIOD_MS);

        hw.stop_US_out();
        vTaskDelay(500 / portTICK_PERIOD_MS);
        */

        std::stringstream ss;
        ss << i*5;

        //push_pub("/topic/qos3", ss.str(), mqtt_client);

        //transmit.push_pub("/topic/qos3", ss.str());
        //transmit.push_pub("/triangulation/master/masterlist/", ss.str());
        //transmit.push_pub("/triangulation/master/start_burst/", ss.str());
        //transmit.push_pub("/triangulation/master/start_continiouse/", ss.str());
        //transmit.push_pub("/triangulation/master/start_ptp_sync/", ss.str());
        //transmit.push_pub("/triangulation/master/burst_cycles/", ss.str());
        //transmit.push_pub("/triangulation/test", ss.str());


        //int msg_id = 0;

        //msg_id = esp_mqtt_client_publish(mqtt_client, "/topic/qos3", "foo data", 0, 0, 1);

        //if(msg_id==0){
        //  printf("\nMSG COULDN'T BE PUBLISHED");
        //}


        //msg_id = esp_mqtt_client_subscribe(mqtt_client, "/triangulation/0ID/ctl/", 0);

        //if(msg_id==0){
        //  printf("\n[ERROR] NOT SUBED");
        //}

        //vTaskDelay(1000 / portTICK_PERIOD_MS);
        i++;
        if(i >= 10000){
          modef.id = hw.getID();
          i=0;
        }
    }

    /*for(uint32_t j=0; j <10; j++){

    }*/

   mySPI.removeDevice(mySPI.device_fpga);
   mySPI.close();
   vTaskDelay(portMAX_DELAY);
}
