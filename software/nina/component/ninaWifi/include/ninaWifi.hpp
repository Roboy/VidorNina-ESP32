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

#ifndef _NINAWIFI_HPP_
#define _NINAWIFI_HPP_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "esp_system.h"
#include "esp_wifi.h"
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

#include "nvs_flash.h"

#include "mqtt_client.h"



//Config
#ifndef CONFIG_WIFI_SSID
#define CONFIG_WIFI_SSID "roboy"
#endif

#ifndef CONFIG_WIFI_PASSWORD
#define CONFIG_WIFI_PASSWORD "wiihackroboy"
#endif


// Forward declaration
class WIFI;

/*static EventGroupHandle_t wifi_event_group;
static const int CONNECTED_BIT = BIT0;
static void wifi_init(void);
static esp_err_t wifi_event_handler(void *ctx, system_event_t *event);
*/
static esp_err_t wifi_event_handler(void *ctx, system_event_t *event);
//static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event);
//static void mqtt_app_start(void);

typedef
class WIFI {
  public:
    explicit WIFI();
    ~WIFI();

    EventGroupHandle_t wifi_event_group;

    const char *TAG = "WIFI";
    const int CONNECTED_BIT = BIT0;

    //esp_err_t wifi_event_handler(void *ctx, system_event_t *event);
    void wifi_init(void);


//  private:

};


 #endif  // end of include guard: _SPIBUS_HPP_
