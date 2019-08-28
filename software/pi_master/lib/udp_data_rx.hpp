#ifndef _UDP_DATA_SEND_HPP_
#define _UDP_DATA_SEND_HPP_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cstdio>
#include <curses.h>

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
  int udp_init();
  static void loop(std::atomic<bool>& program_is_running);

private:
  const char* multi_ip = "239.0.255.250";
  const int multicast_port = 41823;



};

#endif
