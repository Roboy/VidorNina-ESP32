#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <mosquitto.h>
#include <unistd.h>
#include <cstdio>
#include <curses.h>

#include <vector>

#include "common.hpp"

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

#include <cstring>

#include "udp_data_rx.hpp"
#include "udp_data_tx.hpp"

#include <unistd.h>


//#include <thread>



using namespace std;

#define MAX_USERS 10

#define TIME_TOPIC "/triangulation/+/time_data/"

void sub_thread();
void set_burst_cycles(struct mosquitto *mosq);

void spezific_conver(struct mosquitto *mosq);
void start_conver(struct mosquitto *mosq,int id_input);
void  send_master_id(std::atomic<int>& id_tx, std::atomic<bool>& allow_tx);


uint64_t t_dat[30];
uint64_t tag_dat[30];
static uint8_t count_data = 0;
//std::vector<int> t_dat[30][2];

void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	int current_id = 0;
	int current_master_id = 0;
	int time_dat = 0;
	char *payload_data;

	std::stringstream ss_buffer;


	if(message->payloadlen){
		//printf("%s %s\n", message->topic, message->payload);
		for(int i=3; i<=30; i++)
			if(message->topic[i] == '/'){
				i++;
				if((uint8_t)message->topic[i] > 57 || (uint8_t)message->topic[i] < 48)
					break;
				else{
					//printf("\n%s %s", message->topic, message->payload);
					current_id = (int)message->topic[i] - 48;
					//cout << "\nCURRENT ID: " << +current_id;
					//printf("\ncurrent ID: %u", current_id);
					uint8_t* p = (uint8_t*)message->payload;
					//payload_data = &message->payload;
					//ss_buffer << message->payload;
					//std::string str(p);
					p++;
					current_master_id = (unsigned int)*p++ - 48;
					p++;
					tag_dat[current_id] = current_master_id;

					ss_buffer << p;
					ss_buffer >> time_dat;

					t_dat[current_id] = time_dat;
					tag_dat[current_id] = current_master_id;
					count_data ++;
					//printf("\ntime master %u: time %u \n%u\n", t_dat[current_id],t_dat[tag_dat[current_id]],t_dat[tag_dat[current_id]] - t_dat[current_id]);
					//if(current_master_id != current_id)
						//printf("\n%u",t_dat[tag_dat[current_id]] - t_dat[current_id]);
					//printf("\nTime DATA: %x [%d,%d]", t_dat[current_id], current_id,tag_dat[current_id] );
					//time_dat[current_id] = message->payload;

					if(count_data > 2){
						//printf("count data");
						for(uint8_t j=0; j < count_data; j++){
							int64_t dif = t_dat[tag_dat[j]] - t_dat[j];
							//printf("\nm:%d,c:%d,time %u: master time %u .... %d", tag_dat[current_id],current_id,t_dat[current_id],t_dat[tag_dat[current_id]],t_dat[tag_dat[current_id]] - t_dat[current_id]);
							printf("\ni: %ld", dif);
						}
						printf("\ndiv 2: %ld", t_dat[2] - t_dat[1]);
						count_data = 0;


					}
					break;
				}

				break;
			}

	}else{
		printf("%s (null)\n", message->topic);
	}




	fflush(stdout);
}

void my_connect_callback(struct mosquitto *mosq, void *userdata, int result)
{
	int i;
	std::stringstream ss_buffer;


	if(!result){
		/* Subscribe to broker information topics on successful connect. */
		//mosquitto_subscribe(mosq, NULL, "$SYS/#", 2);
		/*for(uint8_t i = 0; i < MAX_USERS; i++){
			ss_buffer << "/triangulation/" << i << "/#";
			string s = ss_buffer.str();
			const char *data_buffer = s.c_str();
			mosquitto_subscribe(mosq, NULL, data_buffer, 2);
			ss_buffer.str("");
		}*/
		;//mosquitto_subscribe(mosq, NULL, "#", 0);

	}else{
		fprintf(stderr, "Connect failed\n");
	}
}

void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
	int i;

	//printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
	//for(i=1; i<qos_count; i++){
	//	printf(", %d", granted_qos[i]);
	//}
	printf("END_SUB\n");
}

void my_log_callback(struct mosquitto *mosq, void *userdata, int level, const char *str)
{
	/* Pring all log messages regardless of level. */
	;//printf("%s\n", str);
}

int main(int argc, char *argv[])
{
	int i;
	char *host = "192.168.1.1";
	int port = 1883;
	int keepalive = 60;
	bool clean_session = true;
	struct mosquitto *mosq = NULL;
	struct mosquitto *mosq2 = NULL;
	char input_key = 0;

	mosquitto_lib_init();
	mosq = mosquitto_new(NULL, clean_session, NULL);
	if(!mosq){
		fprintf(stderr, "Error: Out of memory.\n");
		return 1;
	}


	/*
	transmit.push_pub("/topic/qos3", ss.str());
	transmit.push_pub("/triangulation/master/masterlist/", ss.str());
	transmit.push_pub("/triangulation/master/start_burst/", ss.str());
	transmit.push_pub("/triangulation/master/start_continiouse/", ss.str());
	transmit.push_pub("/triangulation/master/start_ptp_sync/", ss.str());
	transmit.push_pub("/triangulation/master/burst_cycles/", ss.str());
	*/

	//mosquitto_subscribe(mosq, NULL, "#", 2);


	mosquitto_log_callback_set(mosq, my_log_callback);
	mosquitto_connect_callback_set(mosq, my_connect_callback);
	mosquitto_message_callback_set(mosq, my_message_callback);
	mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);


	if(mosquitto_connect(mosq, host, port, keepalive)){
		fprintf(stderr, "Unable to connect.\n");
		return 1;
	}

	std::stringstream ss_buffer;
	int id_buffer = 0;
	ss_buffer << 0;
	for (uint8_t i=1; i < 20; i++){
		id_buffer++;
		if(id_buffer > 10)
			id_buffer=0;

		ss_buffer << "," << id_buffer;
	}
	ss_buffer << ";";
	string s_masterlist_data = ss_buffer.str();  //PS.: max list size 20
	const char *masterlist_data = s_masterlist_data.c_str();
	cout << "\n\n===============START==================\n" << s_masterlist_data <<  "\n";
	cout << "all members connected?(enter)\n";
	cin >> input_key;

	atomic<bool> running { true } ;
	atomic<bool> allow_tx { true };
	atomic<int> id_tx { 0 };

	static struct sockaddr_in addr1;
	static struct sockaddr_in addr2;
	static int fd1;
	static int fd2;

	//static allocation
	static string rx_master_buffer[1000];
	static string rx_slaves_buffer[1000];

	atomic<string> *rx_master;
	std::vector<std::string> v { "a", "b", "c" };
	//rx_master = &rx_master_buffer[0];
	atomic<string> *rx_slaves;
	//rx_slaves = &rx_slaves_buffer[0];

	udp_conv_rx udp;
	(void)udp.udp_init(41823,addr1,fd1);
	std::thread update_thread( udp.loop, std::ref(v), std::ref(running), std::ref(addr1),std::ref(fd1));
	udp_conv_rx udp2;
	(void)udp2.udp_init(40000,addr2,fd2);
	std::thread update_thread_rx2( udp2.loop, std::ref(v), std::ref(running), std::ref(addr2),std::ref(fd2));

	udp_conv_tx udp_tx;
	(void)udp_tx.udp_init();
	std::thread update_thread2( udp_tx.loop, std::ref(running), std::ref(allow_tx), std::ref(id_tx)) ;

	rviz_interface rviz();
	std::thread update_rviz(rviz.loop, std::ref(running));



	//for(uint8_t i = 0; i < 2; i++){

	//mosquitto_loop_forever(mosq, -1, 1);

	//mosquitto_subscribe(mosq2,NULL,"triangulation/+/time_data/", 0);
	//mosquitto_subscribe(mosq,NULL,"triangulation/1/time_data/", 0);

	mosquitto_subscribe(mosq, NULL, TIME_TOPIC, 0);

	mosquitto_loop_start(mosq);

	//for(uint32_t i = 0; i<2; i++){
	mosquitto_publish(mosq,NULL,"/triangulation/master/masterlist/",s_masterlist_data.size(),masterlist_data,1,false);
	mosquitto_publish(mosq,NULL,"/triangulation/master/start_burst/",1,FALSE_S,2,false);
	mosquitto_publish(mosq,NULL,"/triangulation/master/start_continiouse/",1,FALSE_S,2,false);
	mosquitto_publish(mosq,NULL,"/triangulation/master/start_ptp_sync/",1,FALSE_S,2,false);
	mosquitto_publish(mosq,NULL,"/triangulation/master/burst_cycles/",1,"4",2,false);
	mosquitto_publish(mosq,NULL,"/time/set_zero",1,"0",1,false);
	mosquitto_publish(mosq,NULL,"/triangulation/master/start_conv/",1,"0",1,false);


		//mosquitto_loop_start(mosq2);
		//thread t1(sub_thread);
		//mosquitto_loop_forever(mosq2,1000,1);
		//mosquitto_sub -h 192.168.1.1 -p 1883 -t


	//}
	//}





	bool t_burst = false;
	bool t_ptp = false;
	bool t_continiouse = false;
	bool t_conversation = false;

	mosquitto_publish(mosq,NULL,"/triangulation/master/burst_cycles/",3,"50",1,false);

	cout << "\n 1: burst cycle amount";
	cout << "\n 2: start burst data";
	cout << "\n 3: start ptp time sync";
	cout << "\n 4: continouse burst";
	cout << "\n 5: simple zero time";
	cout << "\n 6: burst from ID0";


  while(input_key!=27){
		//const char *num_cycl = "4";
    //menu.options_menu(menu.select());
    //input_key = getch();


    cin >> input_key;
    //cout << input_key;
    switch (input_key){
      case '1':
				set_burst_cycles(mosq);
        break;
      case '2':
        //activate burst
        cout<<"\nactivate burst mode";
        //masterctl.start_burst_mode();
				mosquitto_publish(mosq,NULL,"/triangulation/master/start_burst/",sbool_size,TRUE_S,1,false);
        break;
      case '3':
        //start ptp sync
        cout<<"\nstart ptp sync";
        //masterctl.time_sync_tgl(true);
				mosquitto_publish(mosq,NULL,"/triangulation/master/start_ptp_sync/",sbool_size,TRUE_S,2,false);
				//cin >> input_key;
        break;
      case '4':
          //start ptp sync
          cout<<"\nstart continouse mode";
					t_continiouse = !t_continiouse;
					if(t_continiouse){
						cout << " TRUE";
						mosquitto_publish(mosq,NULL,"/triangulation/master/start_continiouse/",sbool_size,TRUE_S,1,false);
					}
					else{
						cout << " FALSE";
						mosquitto_publish(mosq,NULL,"/triangulation/master/start_continiouse/",sbool_size,FALSE_S,1,false);
					}


          //masterctl.tgl_continiouse_mode();
          break;
			case '5':
					mosquitto_publish(mosq,NULL,"/time/set_zero",1,"0",0,false);
				break;
			case '6':
					//start_conver(mosq,0);
					id_tx = 0;
					allow_tx = true;
				break;
			case '7':
						send_master_id(std::ref(id_tx), std::ref(allow_tx));
						//spezific_conver(mosq);
					break;
      default:
				;
        break;
    }
		//mosquitto_loop(mosq, -1, 1);
	}


	//mosquitto_loop_forever(mosq, -1, 1);



	//for(uint8_t i = 0; i < MAX_USERS; i++){
		//mosquitto_subscribe(mosq, NULL, "/triangulation/master/masterlist/", 2);
	//}



	mosquitto_loop_stop(mosq,true);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	running = false ;
	update_thread.join() ;
	update_thread2.join();

	return 0;
}
void  send_master_id(std::atomic<int>& id_tx, std::atomic<bool>& allow_tx){
	cout<<"\nstart conversation..[enter ID]";
	int id_input = 0;
	cin >> id_input;
	cout << id_input;

	for(uint8_t i = 0; i < 1000; i++){
		id_tx = id_input;
		allow_tx = true;
		while(allow_tx);
		usleep(500000);
	}

}


void set_burst_cycles(struct mosquitto *mosq){

	int amount_burst_cycles = 20;


	cout <<"\nAmount of Cycles: ";
	cin >> amount_burst_cycles;
	string foo = std::to_string(amount_burst_cycles);
	const char *num_cycl = foo.c_str();

	mosquitto_publish(mosq,NULL,"/triangulation/master/burst_cycles/",2,num_cycl,2,false);

}

void spezific_conver(struct mosquitto *mosq){
	cout<<"\nstart conversation..[enter ID]";
	int id_input = 0;
	cin >> id_input;
	cout << (int)id_input;

	//id_tx = id_input;
	//allow_tx = true;
	//start_conver(mosq,id_input);
}
void start_conver(struct mosquitto *mosq,int id_input){

	std::stringstream ss_buffer;

	ss_buffer.str("");
	ss_buffer << id_input;
	string id_temp_string = ss_buffer.str();
	const char *id_temp_char = id_temp_string.c_str();

	/*uint8_t low_cnt = 0;
	for(uint32_t i = 0; i< 100; i++){
		mosquitto_publish(mosq,NULL,"/triangulation/master/start_conv/",id_temp_string.size(),id_temp_char,2,false);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		low_cnt++;
		if(low_cnt > 5){
			mosquitto_publish(mosq,NULL,"/time/set_zero",1,"0",2,false);
			low_cnt = 0;
		}

	}*/
	mosquitto_publish(mosq,NULL,"/triangulation/master/start_conv/",id_temp_string.size(),id_temp_char,1,false);



	//mosquitto_publish(mosq,NULL,"/triangulation/master/start_conv/",1,"0",1,false);



}

void sub_thread(){
	cout <<"foo";
}
