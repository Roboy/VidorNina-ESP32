#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sys/socket.h"
#include "sys/time.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <stdio.h>
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static int64_t t0 = 0, t1 = 0;

static char tag[] = "servo1";
static int id = 0;
static int displacement_offset = 0;

struct{
    int32_t motor;
    int32_t pos;
    int32_t vel;
    int32_t dis;
    int32_t pwm;
}status_frame;

struct{
    int32_t motor;
    int32_t setpoint;
}command_frame;

struct{
    int32_t motor;
    int32_t mode;
    int32_t Kp;
    int32_t Ki;
    int32_t Kd;
}control_frame;

static xQueueHandle gpio_evt_queue = NULL;

#define HOST_IP_ADDR "192.168.255.255"
#define PORT 8000

#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

static esp_adc_cal_characteristics_t *adc_chars;
static const adc1_channel_t channel = ADC1_CHANNEL_3;
static const adc_atten_t atten = ADC_ATTEN_DB_0;
static const adc_unit_t unit = ADC_UNIT_1;
/* The examples use WiFi configuration that you can set via 'make menuconfig'.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_SSID      "roboy"
#define EXAMPLE_ESP_WIFI_PASS      "wiihackroboy"
#define EXAMPLE_ESP_MAXIMUM_RETRY  10

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about one event
 * - are we connected to the AP with an IP? */
const int WIFI_CONNECTED_BIT = BIT0;

static const char *TAG = "wifi station";

static int s_retry_num = 0;

static void check_efuse()
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

void displacement_task(void *ignore){
    status_frame.dis = 0;
    //Check if Two Point or Vref are burned into eFuse
    check_efuse();

    //Configure ADC
    if (unit == ADC_UNIT_1) {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(channel, atten);
    } else {
        adc2_config_channel_atten((adc2_channel_t)channel, atten);
    }

    //Characterize ADC
    adc_chars = (esp_adc_cal_characteristics_t*)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);

    vTaskDelay(1000/portTICK_PERIOD_MS);

    uint32_t adc_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_reading /= NO_OF_SAMPLES;
    displacement_offset = adc_reading;

    //Continuously sample ADC1
    while (1) {
        uint32_t adc_reading = 0;
        //Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++) {
            adc_reading += adc1_get_raw((adc1_channel_t)channel);
        }
        adc_reading /= NO_OF_SAMPLES;
        if ( ((int)adc_reading-displacement_offset) < 0 ) {
            displacement_offset = adc_reading;
//            printf("%d\n",displacement_offset);
        }
        status_frame.dis = adc_reading-displacement_offset;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static void command_task(void *pvParameters)
{
    char rx_buffer[128];
    int addr_family;
    int ip_protocol;

    command_frame.setpoint = 0;

    while (1) {

        struct sockaddr_in local_addr;
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }

        local_addr.sin_family = AF_INET;
        local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        local_addr.sin_port = htons(8001);
        if (bind(sock, (struct sockaddr *) &local_addr, sizeof local_addr) < 0) {
            ESP_LOGE(TAG, "bind port error");
            break;
        }
        //set timer for recv_socket
        static int timeout = 10;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));
        while (1) {
            struct sockaddr_in source_addr; // Large enough for both IPv4 or IPv6
            socklen_t socklen = sizeof(source_addr);
            int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);
            // Error occurred during receiving
            if (len == 10) {
                int m;
                memcpy(&m,&rx_buffer[4],4);
                if(m==command_frame.motor){
                    memcpy(&command_frame.setpoint,rx_buffer,4);
                }
                ESP_LOGI(TAG,"Received command_frame for motor %d with setpoint %d", m, command_frame.setpoint);
            }else if(len == 20){
                int m,kp,ki,kd,mode;
                memcpy(&m,&rx_buffer[16],4);
                if(m==command_frame.motor) {
                    memcpy(&mode, &rx_buffer[12], 4);
                    memcpy(&kp, &rx_buffer[8], 4);
                    memcpy(&ki, &rx_buffer[4], 4);
                    memcpy(&kd, &rx_buffer[0], 4);
                    if(mode==0){
                        command_frame.setpoint = status_frame.pos;
                    }else if(mode == 1){
                        command_frame.setpoint = 0;
                    }else if(mode ==2){
                        command_frame.setpoint = 0;
                    }
                    control_frame.mode = mode;
                    control_frame.Kp = kp;
                    control_frame.Ki = ki;
                    control_frame.Kd = kd;
                    ESP_LOGI(TAG, "Received control_frame for motor %d mode %d kp %d ki %d kd %d", m, mode, kp, ki, kd);
//                if(m==command_frame.motor){
//                    memcpy(&command_frame.setpoint,rx_buffer,4);
//                }
                }
            }
        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}

static void status_task(void *pvParameters)
{
    char addr_str[128];
    int addr_family;
    int ip_protocol;
    status_frame.vel = 0;

    int64_t t0_vel = 0, t1_vel = 0;
    t0_vel = esp_timer_get_time();
    int pos_prev = 0;

    id = (gpio_get_level(18)<<4|gpio_get_level(5)<<3|gpio_get_level(17)<<2|gpio_get_level(16)<<1|gpio_get_level(4));
    printf("my id is %d %d %d %d %d-> %d\n", gpio_get_level(18),gpio_get_level(5),gpio_get_level(17),gpio_get_level(16),gpio_get_level(4),id);
    status_frame.motor = id;
    command_frame.motor = id;

    while (1) {

        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
        inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }

        while (1) {
            t1_vel = esp_timer_get_time();
            int err = sendto(sock, (char*)&status_frame, sizeof(status_frame), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
            if (err < 0) {
//                ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                break;
            }
            ESP_LOGD(TAG, "Message sent");
            vTaskDelay(200 / portTICK_PERIOD_MS);
            float dt = (t1_vel-t0_vel)/1000000.0f; // in s
            float vel = (dt>0?(status_frame.pos-pos_prev)/dt:0);
//            status_frame.vel = vel;

//            ESP_LOGI("vel", "%f %f",vel, dt);
            pos_prev = status_frame.pos;
            t0_vel = t1_vel;
        }

        if (sock != -1) {
//            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}

static void event_handler(void* arg, esp_event_base_t event_base,
                          int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta()
{
    s_wifi_event_group = xEventGroupCreate();

    tcpip_adapter_init();

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));

    wifi_config_t wifi_config = {
            .sta = {
                    .ssid = EXAMPLE_ESP_WIFI_SSID,
                    .password = EXAMPLE_ESP_WIFI_PASS
            },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
}

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
    if(gpio_get_level(gpio_num)==0)
        t0 = esp_timer_get_time();
    else
        t1 = esp_timer_get_time();
}

void servo_task(void *ignore) {
    int zeroSpeed       = 2450;
    int duty            = 2000 ;

    ledc_timer_config_t timer_conf;
    timer_conf.bit_num    = LEDC_TIMER_15_BIT;
    timer_conf.freq_hz    = 50;
    timer_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
    timer_conf.timer_num  = LEDC_TIMER_0;
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t ledc_conf;
    ledc_conf.channel    = LEDC_CHANNEL_0;
    ledc_conf.duty       = duty;
    ledc_conf.gpio_num   = 19;
    ledc_conf.intr_type  = LEDC_INTR_DISABLE;
    ledc_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_conf.timer_sel  = LEDC_TIMER_0;
    ledc_channel_config(&ledc_conf);

    vTaskDelay(1000/portTICK_PERIOD_MS);

    control_frame.mode = 2;
    control_frame.Kp = 1;
    control_frame.Ki = 0;
    control_frame.Kd = 0;

    status_frame.vel = 0;
    int error_prev = 0;
    while(1) {
        int error, output;             // Control system variables
        switch(control_frame.mode){
            case 0:
                error = status_frame.pos-command_frame.setpoint;         // Calculate error
                break;
            case 1:
                error = status_frame.vel-command_frame.setpoint;         // Calculate error
                break;
            case 2:
                if(command_frame.setpoint>=0)
                    error = status_frame.dis - command_frame.setpoint;         // Calculate error
                else
                    error = 0;
                break;
            default:
                error = 0;
        }

        output = error * control_frame.Kp + (error-error_prev)*control_frame.Kd;                 // Calculate proportional
        if(output > 1000)
            output = 1000;            // Clamp output
        if(output < -1000)
            output = -1000;
        status_frame.vel = output;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, zeroSpeed+output);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
        status_frame.pwm = output;
        vTaskDelay(pdMS_TO_TICKS(10));
        error_prev = error;
    } // End loop forever

    vTaskDelete(NULL);
}

void feedback360_task()                            // Cog keeps angle variable updated
{
    int unitsFC = 360;                          // Units in a full circle
    int dutyScale = 1000;                       // Scale duty cycle to 1/1000ths
    int dcMin = 29;                             // Minimum duty cycle
    int dcMax = 971;                            // Maximum duty cycle
    int q2min = unitsFC/4;                      // For checking if in 1st quadrant
    int q3max = q2min * 3;                      // For checking if in 4th quadrant
    int turns = 0;                              // For tracking turns
    // dc is duty cycle, theta is 0 to 359 angle, thetaP is theta from previous
    // loop repetition, tHigh and tLow are the high and low signal times for
    // duty cycle calculations.
    int dc, theta, thetaP, tHigh = 1200, tLow = 0;

    // Calcualte initial duty cycle and angle.
    dc = (dutyScale * tHigh) / (tHigh + tLow);
    theta = (unitsFC - 1) - ((dc - dcMin) * unitsFC) / (dcMax - dcMin + 1);
    thetaP = theta;

    int io_num = 21;

    int pos = 0, pos_offset = 0;
    bool first = true;

    while(1)                                    // Main loop for this cog
    {
        int tHigh = 0, tLow = 0, tCycle = 0;
        while(1)                                  // Keep checking
        {
            if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
                if(gpio_get_level(io_num)==0){
                    tLow = abs(t1-t0);
                }else{
                    tHigh = abs(t0-t1);
                }
                if(tHigh!=0 && tLow!=0){
                    tCycle = tHigh + tLow;
                    if((tCycle > 1000) && (tCycle < 1200)) {  // If cycle time valid
                        break;                                // break from loop
                    }
                }
            }                            // break from loop
        }
        dc = (dutyScale * tHigh) / tCycle;        // Calculate duty cycle

        // This gives a theta increasing int the
        // counterclockwise direction.
        theta = (unitsFC - 1) -                   // Calculate angle
                ((dc - dcMin) * unitsFC)
                / (dcMax - dcMin + 1);

        if(theta < 0)                             // Keep theta valid
            theta = 0;
        else if(theta > (unitsFC - 1))
            theta = unitsFC - 1;

        // If transition from quadrant 4 to
        // quadrant 1, increase turns count.
        if((theta < q2min) && (thetaP > q3max))
            turns++;
            // If transition from quadrant 1 to
            // quadrant 4, decrease turns count.
        else if((thetaP < q2min) && (theta > q3max))
            turns --;

        // Construct the angle measurement from the turns count and
        // current theta value.
        if(turns >= 0)
            pos = (turns * unitsFC) + theta;
        else if(turns <  0)
            pos = ((turns + 1) * unitsFC) - (unitsFC - theta);

        if(first){
            first = false;
            pos_offset = pos;
            status_frame.pos = 0;
        }else{
            status_frame.pos = pos-pos_offset;
        }

        ESP_LOGD("timer", "angle = %d", status_frame.pos);

        thetaP = theta;                           // Theta previous for next rep
    }
}

void app_main()
{
    gpio_config_t dip_config;
    dip_config.intr_type = GPIO_PIN_INTR_DISABLE; 	//Enable interrupt on both rising and falling edges
    dip_config.mode = GPIO_MODE_INPUT;        	//Set as Input
    dip_config.pin_bit_mask = (1ULL<<18|1ULL<<17|1ULL<<16|1ULL<<5|1ULL<<4); //Bitmask
    dip_config.pull_up_en = GPIO_PULLUP_DISABLE; 	//Disable pullup
    dip_config.pull_down_en = GPIO_PULLDOWN_ENABLE; //Enable pulldown
    gpio_config(&dip_config);

    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_ANYEDGE;
    //set as output mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = (1ULL<<21);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    //create a queue to handle gpio event from isr
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    //install gpio isr service
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(21, gpio_isr_handler, (void*) 21);
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    nvs_flash_init();
    wifi_init_sta();
    xTaskCreate(&displacement_task,"displacement_task",2048,NULL,1,NULL);
    printf("displacement_task started\n");
    xTaskCreate(&feedback360_task,"feedback360_task",2048,NULL,4,NULL);
    printf("feedback360_task started\n");
    xTaskCreate(&status_task,"status_task",2048,NULL,5,NULL);
    printf("status_task started\n");
    xTaskCreate(&command_task,"command_task",2048,NULL,3,NULL);
    printf("command_task started\n");
    xTaskCreate(&servo_task,"servo_task",2048,NULL,1,NULL);
    printf("servo_task started\n");
}