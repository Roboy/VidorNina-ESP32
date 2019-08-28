#include "udp_data_rx.hpp"


static int fd;
static struct sockaddr_in addr;
static struct ip_mreq mreq;

udp_conv_rx::udp_conv_rx(){

}

int udp_conv_rx::udp_init(){
  //https://gist.github.com/hostilefork/f7cae3dc33e7416f2dd25a402857b6c6
  fd = socket(AF_INET, SOCK_DGRAM, 0);


  if (fd < 0) {
      printf("\nsocket");
      return 1;
  }

  u_int yes = 1;
  if (
      setsockopt(
          fd, SOL_SOCKET, SO_REUSEADDR, (char*) &yes, sizeof(yes)
      ) < 0
  ){
     printf("\nReusing ADDR failed");
     return 1;
  }

      // set up destination address
  //

  //memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY); // differs from sender
  addr.sin_port = htons(multicast_port);

  // bind to receive address
  //
  if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
      printf("\nbind");
      return 1;
  }

  // use setsockopt() to request that the kernel join a multicast multi_ip
  //

  mreq.imr_multiaddr.s_addr = inet_addr(multi_ip);
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);
  if (
      setsockopt(
          fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)
      ) < 0
  ){
      printf("\nsetsockopt");
      return 1;
  }
}

void udp_conv_rx::loop(std::atomic<bool>& program_is_running){
  while( program_is_running ) {
      char msgbuf[MSGBUFSIZE];
      socklen_t addrlen = sizeof(addr);
      int nbytes = recvfrom(
          fd,
          msgbuf,
          MSGBUFSIZE,
          0,
          (struct sockaddr *) &addr,
          &addrlen
      );
      if (nbytes < 0) {
          printf("\nrecvfrom");
          return;
      }
      msgbuf[nbytes] = '\0';
      //puts(msgbuf);
      printf("\n=DATA=:%s", msgbuf);

  }
}
