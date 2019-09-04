#ifndef _UDP_DATA_SEND_HPP_
#define _UDP_DATA_SEND_HPP_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <curses.h>

#include <vector>

#include <chrono>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include <atomic>
#include <thread>
#include <chrono>

#define MSGBUFSIZE 256


class udp_conv_rx{
public:
  udp_conv_rx();
  int udp_init(int udp_port, struct sockaddr_in &addr, int &fd);
  static void loop(std::vector<std::string> rx_data, std::atomic<bool>& program_is_running, struct sockaddr_in &addr, int &fd);

private:
  const char* multi_ip = "239.0.255.250";
  struct ip_mreq mreq;


};

#endif
