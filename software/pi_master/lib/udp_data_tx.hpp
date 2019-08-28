#ifndef _UDP_DATA_TX_HPP_
#define _UDP_DATA_TX_HPP_

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
#include <unistd.h>

#include <atomic>
#include <thread>
#include <chrono>


class udp_conv_tx{
public:
  udp_conv_tx();
  int udp_init();
  static void loop(std::atomic<bool>& program_is_running, std::atomic<bool>& allow_tx, std::atomic<int>& id_tx);

private:
  const char* multi_ip = "239.0.255.250";
  const int multicast_port = 40001;



};

#endif
