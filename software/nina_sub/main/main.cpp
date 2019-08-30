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
#include "lwip/err.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

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



#define CONFIG_EXAMPLE_IPV4
#define CONFIG_EXAMPLE_IPV4_ONLY
#undef CONFIG_EXAMPLE_IPV6

#define CONFIG_EXAMPLE_PORT 41823//1900//41823

#define CONFIG_EXAMPLE_LOOPBACK false

#define CONFIG_EXAMPLE_MULTICAST_TTL 20 //range from 1 to 255

#define CONFIG_EXAMPLE_MULTICAST_IPV4_ADDR "239.0.255.250"// "232.10.11.12"
#define MULTICAST_IPV4_RX "239.0.255.250"
#define CONFIG_EXAMPLE_MULTICAST_IPV6_ADDR "FF02::FC"

#define CONFIG_EXAMPLE_LISTEN_DEFAULT_IF false



#define EXAMPLE_WIFI_SSID CONFIG_WIFI_SSID
#define EXAMPLE_WIFI_PASS CONFIG_WIFI_PASSWORD

#define UDP_PORT CONFIG_EXAMPLE_PORT
#define UDP_PORT_RX 40001

#define MULTICAST_LOOPBACK CONFIG_EXAMPLE_LOOPBACK

#define MULTICAST_TTL CONFIG_EXAMPLE_MULTICAST_TTL

#define MULTICAST_IPV4_ADDR CONFIG_EXAMPLE_MULTICAST_IPV4_ADDR
#define MULTICAST_IPV6_ADDR CONFIG_EXAMPLE_MULTICAST_IPV6_ADDR

#define LISTEN_DEFAULT_IF CONFIG_EXAMPLE_LISTEN_DEFAULT_IF

#define USE_DEFAULT_IF true

/* FreeRTOS event group to signal when we are connected & ready to make a request */
//static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   we use two - one for IPv4 "got ip", and
   one for IPv6 "got ip". */
const int IPV4_GOTIP_BIT = BIT0;
const int IPV6_GOTIP_BIT = BIT1;

static const char *TAG_M = "multicast";
#ifdef CONFIG_EXAMPLE_IPV4
static const char *V4TAG = "mcast-ipv4";
#endif
#ifdef CONFIG_EXAMPLE_IPV6
static const char *V6TAG = "mcast-ipv6";
#endif

#ifdef CONFIG_EXAMPLE_IPV4
/* Add a socket, either IPV4-only or IPV6 dual mode, to the IPV4
   multicast group */
static int socket_add_ipv4_multicast_group(int sock, bool assign_source_if)
{
    struct ip_mreq imreq = { 0 };
    struct in_addr iaddr = { 0 };
    int err = 0;
    // Configure source interface
#if USE_DEFAULT_IF
    imreq.imr_interface.s_addr = IPADDR_ANY;
#else
    tcpip_adapter_ip_info_t ip_info = { 0 };
    err = tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
    if (err != ESP_OK) {
        ESP_LOGE(V4TAG, "Failed to get IP address info. Error 0x%x", err);
        return err;
    }
    inet_addr_from_ipaddr(&iaddr, &ip_info.ip);
#endif
    // Configure multicast address to listen to
    err = inet_aton(MULTICAST_IPV4_ADDR, &imreq.imr_multiaddr.s_addr);
    if (err != 1) {
        ESP_LOGE(V4TAG, "Configured IPV4 multicast address '%s' is invalid.", MULTICAST_IPV4_ADDR);
        return err;
    }
    ESP_LOGI(TAG_M, "Configured IPV4 Multicast address %s", inet_ntoa(imreq.imr_multiaddr.s_addr));
    if (!IP_MULTICAST(ntohl(imreq.imr_multiaddr.s_addr))) {
        ESP_LOGW(V4TAG, "Configured IPV4 multicast address '%s' is not a valid multicast address. This will probably not work.", MULTICAST_IPV4_ADDR);
    }

    if (assign_source_if) {
        // Assign the IPv4 multicast source interface, via its IP
        // (only necessary if this socket is IPV4 only)
        err = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, &iaddr,
                         sizeof(struct in_addr));
        if (err < 0) {
            ESP_LOGE(V4TAG, "Failed to set IP_MULTICAST_IF. Error %d", errno);
            return err;
        }
    }

    err = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                         &imreq, sizeof(struct ip_mreq));
    if (err < 0) {
        ESP_LOGE(V4TAG, "Failed to set IP_ADD_MEMBERSHIP. Error %d", errno);
        return err;
    }

 //err:
    return err;
}
#endif /* CONFIG_EXAMPLE_IPV4 */

#ifdef CONFIG_EXAMPLE_IPV4_ONLY
static int create_multicast_ipv4_socket_rx(){
  struct sockaddr_in saddr = { 0 };
  int sock = -1;
  int err = 0;

  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  if (sock < 0) {
      ESP_LOGE(V4TAG, "Failed to create socket. Error %d", errno);
      return -1;
  }

  // Bind the socket to any address
  saddr.sin_family = PF_INET;
  saddr.sin_port = htons(UDP_PORT_RX);
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  err = bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
  if (err < 0) {
      ESP_LOGE(V4TAG, "Failed to bind socket. Error %d", errno);
      return err;
  }


  // Assign multicast TTL (set separately from normal interface TTL)
  uint8_t ttl = MULTICAST_TTL;
  setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(uint8_t));
  if (err < 0) {
      ESP_LOGE(V4TAG, "Failed to set IP_MULTICAST_TTL. Error %d", errno);
      return err;
  }


  // this is also a listening socket, so add it to the multicast
  // group for listening...
  err = socket_add_ipv4_multicast_group(sock, true);
  if (err < 0) {
      return err;
  }

  // All set, socket is configured for sending and receiving
  return sock;

//err:
  close(sock);
  return -1;
}
static int create_multicast_ipv4_socket()
{
    struct sockaddr_in saddr = { 0 };
    int sock = -1;
    int err = 0;

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(V4TAG, "Failed to create socket. Error %d", errno);
        return -1;
    }

    // Bind the socket to any address
    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(UDP_PORT);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(sock, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
    if (err < 0) {
        ESP_LOGE(V4TAG, "Failed to bind socket. Error %d", errno);
        return err;
    }


    // Assign multicast TTL (set separately from normal interface TTL)
    uint8_t ttl = MULTICAST_TTL;
    setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(uint8_t));
    if (err < 0) {
        ESP_LOGE(V4TAG, "Failed to set IP_MULTICAST_TTL. Error %d", errno);
        return err;
    }


    // this is also a listening socket, so add it to the multicast
    // group for listening...
    err = socket_add_ipv4_multicast_group(sock, true);
    if (err < 0) {
        return err;
    }

    // All set, socket is configured for sending and receiving
    return sock;

//err:
    close(sock);
    return -1;
}
#endif /* CONFIG_EXAMPLE_IPV4_ONLY */

static void mcast_gather_data(void *pvParameters){

  //static int err = 0;

  hardware_interface *hw = (hardware_interface *)pvParameters;

  while (1) {
      /*int sock;

      sock = create_multicast_ipv4_socket();
      if (sock < 0) {
          ESP_LOGE(TAG, "Failed to create IPv4 multicast socket");
      }

      if (sock < 0) {
          // Nothing to do!
          vTaskDelay(5 / portTICK_PERIOD_MS);
          continue;
      }

  //#ifdef CONFIG_EXAMPLE_IPV4
      // set destination multicast addresses for sending from these sockets
      struct sockaddr_in sdestv4 = {NULL,PF_INET,htons(UDP_PORT_RX)};
      // We know this inet_aton will pass because we did it above already
      inet_aton(MULTICAST_IPV4_RX, &sdestv4.sin_addr.s_addr);
  //#endif


      // Loop waiting for UDP received, and sending UDP packets if we don't
      // see any.
      int err = 1;*/

      uint32_t bits = 0;
      bits |= IPV4_GOTIP_BIT;


      ESP_LOGI(TAG_M, "Waiting for AP connection...");
      xEventGroupWaitBits(wifi_event_group, bits, false, true, portMAX_DELAY);
      ESP_LOGI(TAG_M, "Connected to AP");

      int sock;
      sock = create_multicast_ipv4_socket_rx();
      //ESP_LOGE(V4TAG, "+++SOCK CREATED++");
      if (sock < 0) {
          ESP_LOGE(V4TAG, "Failed to create IPv4 multicast socket");
      }
      if (sock < 0) {
          // Nothing to do!
          //vTaskDelay(5 / portTICK_PERIOD_MS);
          continue;
      }

      struct sockaddr_in sdestv4 = {NULL,PF_INET,htons(UDP_PORT_RX)};

      inet_aton(MULTICAST_IPV4_RX, &sdestv4.sin_addr.s_addr);

      //ESP_LOGE(V4TAG, "+++STARTED LOOP++");
      int err = 1;
      while (err > 0) {
          struct timeval tv = {
              .tv_sec = 2,
              .tv_usec = 0,
          };
          fd_set rfds;
          FD_ZERO(&rfds);
          FD_SET(sock, &rfds);

          //int s = select(sock + 1, &rfds, NULL, NULL, &tv);
          int s = lwip_select(sock + 1, &rfds, NULL, NULL, &tv);
          //ESP_LOGE(V4TAG, "+++S: %d ++",s);
          if (s < 0) {
              ESP_LOGE(V4TAG, "Select failed: errno %d", errno);
              err = -1;
              break;
          }
          else if (s > 0) {
              printf("\ns > 0");
              if (FD_ISSET(sock, &rfds)) {
                  // Incoming datagram received
                  char recvbuf[48];
                  char raddr_name[32] = { 0 };

                  struct sockaddr_in6 raddr; // Large enough for both IPv4 or IPv6
                  socklen_t socklen = sizeof(raddr);
                  int len = recvfrom(sock, recvbuf, sizeof(recvbuf)-1, 0,
                                     (struct sockaddr *)&raddr, &socklen);
                  if (len < 0) {
                      ESP_LOGE(V4TAG, "multicast recvfrom failed: errno %d", errno);
                      err = -1;
                      break;
                  }

                  // Get the sender's address as a string
                  if (raddr.sin6_family == PF_INET) {
                      inet_ntoa_r(((struct sockaddr_in *)&raddr)->sin_addr.s_addr,
                                  raddr_name, sizeof(raddr_name)-1);
                  }
                  ESP_LOGI(V4TAG, "received %d bytes from %s:", len, raddr_name);

                  recvbuf[len] = 0; // Null-terminate whatever we received and treat like a string...
                  ESP_LOGI(V4TAG, "%s", recvbuf);

                  hw->piezo_burst_out();
                  //send_time_frame(hw->US_start_time);


                  static int send_count;
                  const char sendfmt[] = "Multicast #%d sent by ESP32\n";
                  char sendbuf[48];
                  char addrbuf[32] = { 0 };
                  len = snprintf(sendbuf, sizeof(sendbuf), sendfmt, send_count++);
                  if (len > sizeof(sendbuf)) {
                      ESP_LOGE(TAG, "Overflowed multicast sendfmt buffer!!");
                      send_count = 0;
                      err = -1;
                      break;
                  }

                  struct addrinfo hints = {AI_PASSIVE,NULL,SOCK_DGRAM};
                  struct addrinfo *res;

                  hints.ai_family = AF_INET; // For an IPv4 socket

                  int err = getaddrinfo(MULTICAST_IPV4_RX,//CONFIG_EXAMPLE_MULTICAST_IPV4_ADDR,
                                        NULL,
                                        &hints,
                                        &res);
                  if (err < 0) {
                      ESP_LOGE(TAG, "getaddrinfo() failed for IPV4 destination address. error: %d", err);
                      break;
                  }
                  if (res == 0) {
                      ESP_LOGE(TAG, "getaddrinfo() did not return any addresses");
                      break;
                  }
                  ((struct sockaddr_in *)res->ai_addr)->sin_port = htons(40000);
                  inet_ntoa_r(((struct sockaddr_in *)res->ai_addr)->sin_addr, addrbuf, sizeof(addrbuf)-1);
                  ESP_LOGI(TAG, "Sending to IPV4 multicast address %s:%d...",  addrbuf, 40000);
                  err = sendto(sock, sendbuf, len, 0, res->ai_addr, res->ai_addrlen);
                  freeaddrinfo(res);
                  if (err < 0) {
                      ESP_LOGE(TAG, "IPV4 sendto failed. errno: %d", errno);
                      break;
                  }
              }

          }
          else { // s == 0
            // Timeout passed with no incoming data, so send something!
            //std::cout<<"\nUDP no packet received ... sending";


        }
      }

      ESP_LOGE(V4TAG, "Shutting down socket and restarting...");
      shutdown(sock, 0);
      close(sock);
    }

  }


static void mcast_example_task(void *pvParameters){
    hardware_interface *hw = (hardware_interface *)pvParameters;
    //static struct addrinfo res_;
    //static struct sockaddr ai_addr_;

/*    struct addrinfo {
    int               ai_flags;
    int               ai_family;
    int               ai_socktype;
    int               ai_protocol;
    socklen_t         ai_addrlen;
    struct sockaddr  *ai_addr;
    char             *ai_canonname;
    struct addrinfo  *ai_next;
};
*/


    static int err = 0;

    while (1) {
        /* Wait for all the IPs we care about to be set
        */
        uint32_t bits = 0;
        bits |= IPV4_GOTIP_BIT;


        ESP_LOGI(TAG_M, "Waiting for AP connection...");
        xEventGroupWaitBits(wifi_event_group, bits, false, true, portMAX_DELAY);
        ESP_LOGI(TAG_M, "Connected to AP");

        int sock;

        sock = create_multicast_ipv4_socket();
        if (sock < 0) {
            ESP_LOGE(TAG_M, "Failed to create IPv4 multicast socket");
        }

        if (sock < 0) {
            // Nothing to do!
            vTaskDelay(5 / portTICK_PERIOD_MS);
            continue;
        }

        // set destination multicast addresses for sending from these sockets
        /*
        struct sockaddr_in {
          u8_t            sin_len;
          sa_family_t     sin_family;
          in_port_t       sin_port;
          struct in_addr  sin_addr;
        #define SIN_ZERO_LEN 8
          char            sin_zero[SIN_ZERO_LEN];
        };


        */
        struct sockaddr_in sdestv4 = {NULL,PF_INET,htons(UDP_PORT)};
        //    .sin_family = PF_INET,
        //    .sin_port = htons(UDP_PORT),
        //};
        // We know this inet_aton will pass because we did it above already
        inet_aton(MULTICAST_IPV4_ADDR, &sdestv4.sin_addr.s_addr);


        // Loop waiting for UDP received, and sending UDP packets if we don't
        // see any.
        //int err = 1;
        struct timeval tv = {
            .tv_sec = 2,
            .tv_usec = 0,
        };
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(sock, &rfds);

        int s = lwip_select(sock + 1, &rfds, NULL, NULL, &tv);
        if (s < 0) {
            ESP_LOGE(TAG_M, "Select failed: errno %d", errno);
            err = -1;
            break;
        }

        struct addrinfo hints = {AI_PASSIVE,NULL,SOCK_DGRAM};
        struct addrinfo *res; //= &res_;
        hints.ai_family = AF_INET; // For an IPv4 socket


        err = getaddrinfo(CONFIG_EXAMPLE_MULTICAST_IPV4_ADDR,
                              NULL,
                              &hints,
                              &res);
        if (err < 0) {
            ESP_LOGE(TAG_M, "getaddrinfo() failed for IPV4 destination address. error: %d", err);
            break;
        }


        while (err >= 0) {
          //int err  = 0;
            /*
            else if (s > 0) {
                if (FD_ISSET(sock, &rfds)) {
                    // Incoming datagram received
                    char recvbuf[48];
                    char raddr_name[32] = { 0 };

                    struct sockaddr_in6 raddr; // Large enough for both IPv4 or IPv6
                    socklen_t socklen = sizeof(raddr);
                    int len = recvfrom(sock, recvbuf, sizeof(recvbuf)-1, 0,
                                       (struct sockaddr *)&raddr, &socklen);
                    if (len < 0) {
                        ESP_LOGE(TAG_M, "multicast recvfrom failed: errno %d", errno);
                        err = -1;
                        break;
                    }

                    // Get the sender's address as a string
#ifdef CONFIG_EXAMPLE_IPV4
                    if (raddr.sin6_family == PF_INET) {
                        inet_ntoa_r(((struct sockaddr_in *)&raddr)->sin_addr.s_addr,
                                    raddr_name, sizeof(raddr_name)-1);
                    }
#endif
                    ESP_LOGI(TAG_M, "received %d bytes from %s:", len, raddr_name);

                    recvbuf[len] = 0; // Null-terminate whatever we received and treat like a string...
                    ESP_LOGI(TAG_M, "%s", recvbuf);
                }
            }*/
            // s == 0
                // Timeout passed with no incoming data, so send something!
                //vTaskDelay(500 / portTICK_PERIOD_MS);

                /*
                struct addrinfo {
                    int               ai_flags;
                    int               ai_family;
                    int               ai_socktype;
                    int               ai_protocol;
                    socklen_t         ai_addrlen;
                    struct sockaddr  *ai_addr;
                    char             *ai_canonname;
                    struct addrinfo  *ai_next;
                };
                */


                  //    .ai_flags = AI_PASSIVE,
                  //    .ai_socktype = SOCK_DGRAM,
                  //};

                  //(*res).ai_addr = &ai_addr_;
                static int send_count;
                const char sendfmt[] = "%u/%u\n";
                char sendbuf[48];
                char addrbuf[32] = { 0 };
                int len = 0;

                hw->allow_input_trigger();
                for(int time_out_cnt = 0; time_out_cnt < 4294967295; time_out_cnt++){
                //  cout << "\n" << +(int)hw.rdy_to_read() << " : " << +(int)time_out_cnt << " : " <<  (int)hw.read_trigger_time();
                  if(!hw->rdy_to_read()){
                    len = snprintf(sendbuf, sizeof(sendbuf), sendfmt,hw->device_id, hw->read_trigger_time());
                    //cout << "\nready to read " << time_out_cnt;
                    //modef.send_time_frame(hw.read_trigger_time());
                    break;
                  }
                }




              if (len > sizeof(sendbuf)) {
                  ESP_LOGE(TAG_M, "Overflowed multicast sendfmt buffer!!");
                  send_count = 0;
                  err = -1;
                  break;
              }



              ((struct sockaddr_in *)res->ai_addr)->sin_port = htons(UDP_PORT);
              inet_ntoa_r(((struct sockaddr_in *)res->ai_addr)->sin_addr, addrbuf, sizeof(addrbuf)-1);
              //ESP_LOGI(TAG_M, "Sending to IPV4 multicast address %s...",  addrbuf);
              //printf("\nSending to IPV4 multicast address %s...",  addrbuf);
              //printf("\nsin: %d ....%d...%d", (int)((struct sockaddr_in *)res->ai_addr)->sin_addr, (int)res->ai_addrlen);
              //printf("\nsock: %d ....%d...%d", (int)&res, (int)&res->ai_addr, (int)res->ai_addr->sa_data);
              //printf("\naddr: %d ....%d ", (int)&addrbuf, (int)&sendbuf);

              err = sendto(sock, sendbuf, len, 0, res->ai_addr, res->ai_addrlen);
              if (err < 0) {
                  ESP_LOGE(TAG_M, "IPV4 sendto failed. errno: %d", errno);
                  break;
              }
            }



        ESP_LOGE(TAG_M, "Shutting down socket and restarting...");
        shutdown(sock, 0);
        close(sock);
    }

}



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
    ESP_LOGI(TAG_M, "start the WIFI SSID:[%s] password:[%s]", CONFIG_WIFI_SSID, "******");
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG_M, "Waiting for wifi");
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG_M, "MQTT_EVENT_CONNECTED");
            //msg_id = esp_mqtt_client_subscribe(client, "/topic/qos3", 0);
            //ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG_M, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG_M, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            //msg_id = esp_mqtt_client_publish(client, CONFIG_EMITTER_CHANNEL_KEY"/topic/", "data", 0, 0, 0);
            //ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG_M, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG_M, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG_M, "MQTT_EVENT_DATA");
            //printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            //printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG_M, "MQTT_EVENT_ERROR");
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

static void mqtt_app_start(esp_mqtt_client_handle_t *client_, int id)
{
  std::stringstream ss_buffer_;
  ss_buffer_ << "sausi_esp" << +(int)id;
  string s = ss_buffer_.str();
  const char *c_id = s.c_str();
  //const esp_mqtt_client_config_t mqtt_cfg = {mqtt_event_handler ,NULL ,"mqtt://192.168.1.1", "mqtt://192.168.1.1"};
  const esp_mqtt_client_config_t mqtt_cfg = {NULL ,NULL ,"mqtt://192.168.1.1", "mqtt://192.168.1.1", 1883, c_id};

  //const char *p = mqtt_cfg.client_id;
  //ESP_LOGI(TAG, "MQTT!!!!!! ID: %s ", p);


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

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    xTaskCreate(&mcast_example_task, "mcast_task", 4096, &hw, 6, NULL);
    xTaskCreate(&mcast_gather_data, "mcast_rx", 4096, &hw, 5, NULL);



    mqtt_app_start(&mqtt_client, hw.getID());
    esp_mqtt_client_register_event(mqtt_client, MQTT_EVENT_DATA, custom_handl, &modef);


    //transmit.push_pub("/init", "0");
    (void)esp_mqtt_client_publish(mqtt_client, "/init", "1", 0, 1, 0);
    for(uint8_t i=0; i < 1000; i++){
      if(esp_mqtt_client_subscribe(mqtt_client, "/init", 1) > 0)
        break;
    }
    (void)esp_mqtt_client_unsubscribe(mqtt_client, "/init");
    (void)esp_mqtt_client_subscribe(mqtt_client, "/time/set_zero", 0) ;

    //hw.allow_input_trigger();
    hw.device_id = hw.getID();
    printf("\nID: %d", hw.device_id);

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
        //hw.piezo_set_burst_cycles(30);
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
        /*hw.allow_input_trigger();
        for(int time_out_cnt = 0; time_out_cnt <= 3000; time_out_cnt++){
        //  cout << "\n" << +(int)hw.rdy_to_read() << " : " << +(int)time_out_cnt << " : " <<  (int)hw.read_trigger_time();
          if(!hw.rdy_to_read()){
            ;
            //cout << "\nready to read " << time_out_cnt;
            //modef.send_time_frame(hw.read_trigger_time());
            break;
          }
        }*/

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

        //std::stringstream ss;
        //ss << i*5;

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
          //modef.id = hw.getID();
          i=0;
        }
    }

    /*for(uint32_t j=0; j <10; j++){

    }*/

   mySPI.removeDevice(mySPI.device_fpga);
   mySPI.close();
   vTaskDelay(portMAX_DELAY);
}
