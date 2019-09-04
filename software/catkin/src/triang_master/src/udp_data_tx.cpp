#include "udp_data_tx.hpp"

#include <cstring>

static int fd_tx;
static struct sockaddr_in addr_tx;
static struct ip_mreq mreq_tx;

udp_conv_tx::udp_conv_tx(){

}

int udp_conv_tx::udp_init(){
  //https://gist.github.com/hostilefork/f7cae3dc33e7416f2dd25a402857b6c6

    //char* multi_ip = "239.0.255.250"; // e.g. 239.255.255.250 for SSDP
    //int port_udp = 41823; // 0 if error, which is an invalid port

    // !!! If test requires, make these configurable via args
    //



    // create what looks like an ordinary UDP socket
    //
    fd_tx = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_tx < 0) {
        perror("socket");
        return 1;
    }

    // set up destination address
    //
    //struct sockaddr_in addr_tx;
    memset(&addr_tx, 0, sizeof(addr_tx));
    addr_tx.sin_family = AF_INET;
    addr_tx.sin_addr.s_addr = inet_addr(multi_ip);
    addr_tx.sin_port = htons(multicast_port);

      // now just sendto() our destination!
    //

    return 0;
}

void udp_conv_tx::loop(std::atomic<bool>& program_is_running,std::atomic<bool>& allow_tx, std::atomic<int>& id_tx){
  while( program_is_running ) {
    const int delay_secs = 1;
    std::stringstream ss;
    ss << std::to_string(id_tx) << "/" << std::to_string(id_tx+1) << "/" << std::to_string(id_tx+2);

    std::string s = ss.str();//std::to_string(id_tx);
    const char *message = s.c_str(); //id_tx
    char ch = 0;

    //while(!allow_tx);
    if(allow_tx){
      //std::cout << "\nout " << (bool)allow_tx;
      int nbytes = sendto(
          fd_tx,
          message,
          std::strlen(message),
          0,
          (struct sockaddr*) &addr_tx,
          sizeof(addr_tx)
      );

      if (nbytes < 0) {
          perror("sendto");
          return;
      }

      allow_tx = false;
    }
    //sleep(delay_secs); // Unix sleep is seconds

  }


    //sleep(delay_secs); // Unix sleep is seconds


}
