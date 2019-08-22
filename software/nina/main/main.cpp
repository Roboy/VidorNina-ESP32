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
 #include <string.h>

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
#include "nvs_flash.h"

#include "interface.hpp"
#include "interface0.hpp"


#define SPI_MODE  1//original 0
#define MISO_PIN  19
#define MOSI_PIN  23
#define SCLK_PIN  18
#define CS_PIN    5
#define SPI_CLOCK SPI_MASTER_FREQ_16M   // 1 MHz

extern "C" void app_main() {
    printf("--START-- \n");
    fflush(stdout);

    //nvs_flash_init();
    //wifi_init();
    WIFI wifi;
    //MQTT mqtt;

    //mqtt_app_start();


    SPI_t &mySPI = vspi;  // vspi and hspi are the default objects

    spi_device_handle_t device;
    ESP_ERROR_CHECK( mySPI.begin(MOSI_PIN, MISO_PIN, SCLK_PIN,8));
    //ESP_ERROR_CHECK( mySPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &device));
    ESP_ERROR_CHECK( mySPI.addDevice(SPI_MODE, SPI_CLOCK, CS_PIN, &mySPI.device_fpga));

    mySPI.fpga_write(0x0, 0, 16);
    mySPI.fpga_write(0x0, 1, 0);
    mySPI.fpga_write(0x0, 2, 14);

    mySPI.fpga_write(0x40000, 0, 17);
    mySPI.fpga_write(0x40000, 1, 0);
    mySPI.fpga_write(0x40000, 2, 13);



    while(1){

    uint8_t ret_read;
    uint32_t i;
    for(i = 0; i < 20; i++){
      printf("\n%d: data: %d",i, mySPI.fpga_read(0x0, i)); //i
      printf("\n%d: data: %d",i, mySPI.fpga_read(0x40000, i)); //i
    }

  }
    mySPI.removeDevice(mySPI.device_fpga);
    mySPI.close();
    vTaskDelay(portMAX_DELAY);
}
