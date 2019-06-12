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

 #include "ninaWifi.hpp"

 WIFI::WIFI() {
   nvs_flash_init();
   wifi_init();

 }

 WIFI::~WIFI() {
     ;
 }

static bool wifi_waitflag;

static esp_err_t wifi_event_handler(void *ctx, system_event_t *event){
//esp_err_t WIFI::wifi_event_handler(void *ctx, system_event_t *event){
     switch (event->event_id) {
         case SYSTEM_EVENT_STA_START:
             esp_wifi_connect();
             break;
         case SYSTEM_EVENT_STA_GOT_IP:
              wifi_waitflag = 0;
            // xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);

             break;
         case SYSTEM_EVENT_STA_DISCONNECTED:
             esp_wifi_connect();
             //xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
             break;
         default:
             break;
     }
     return ESP_OK;
 }


//static void wifi_init(void){
void WIFI::wifi_init(void){
    tcpip_adapter_init();
    /*wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_init(wifi_event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    wifi_ap_config_t wifi_cfg = {CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD};
    wifi_config_t wifi_config = {wifi_cfg};

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_LOGI("WIFI", "wlan init cfg %d", cfg.mgmt_sbuf_num);

    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    //wifi_sta_config_t sta_ = {CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD};
    //wifi_config_t wifi_config = {sta_};
    //wifi_config_t wifi_config = {{CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD}};

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_LOGI("WIFI", "start the WIFI SSID:[%s] password:[%s]", CONFIG_WIFI_SSID, "******");
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI("WIFI", "Waiting for wifi");
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);*/

    wifi_waitflag = 1;
    esp_event_loop_init(wifi_event_handler, NULL);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    wifi_ap_config_t wifi_cfg = {CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD};
    wifi_config_t wifi_config = {wifi_cfg};

    esp_wifi_init(&cfg);

    esp_wifi_set_storage(WIFI_STORAGE_RAM);
    //wifi_sta_config_t sta_ = {CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD};
    //wifi_config_t wifi_config = {sta_};
    //wifi_config_t wifi_config = {{CONFIG_WIFI_SSID,CONFIG_WIFI_PASSWORD}};

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config);
    ESP_LOGI("WIFI", "start the WIFI SSID:[%s] password:[%s]", CONFIG_WIFI_SSID, "******");
    esp_wifi_start();
    ESP_LOGI("WIFI", "Waiting for wifi");
    while(wifi_waitflag);
}
