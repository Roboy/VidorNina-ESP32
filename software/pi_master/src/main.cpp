#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <mosquitto.h>

#include "common.hpp"

using namespace std;

#define MAX_USERS 10

void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	if(message->payloadlen){
		;//printf("%s %s\n", message->topic, message->payload);
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
		mosquitto_subscribe(mosq, NULL, "/triangulation/#", 2);

	}else{
		fprintf(stderr, "Connect failed\n");
	}
}

void my_subscribe_callback(struct mosquitto *mosq, void *userdata, int mid, int qos_count, const int *granted_qos)
{
	int i;

	printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
	for(i=1; i<qos_count; i++){
		printf(", %d", granted_qos[i]);
	}
	printf("\n");
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

	//mosquitto_subscribe(mosq, NULL, "/triangulation/master/masterlist/", 2);


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
	cout << "all members connected?\n";
	//for(uint8_t i = 0; i < 2; i++){

	//mosquitto_loop_forever(mosq, -1, 1);

	mosquitto_loop_start(	mosq);

	for(uint32_t i = 0; i<2; i++){
		mosquitto_publish(mosq,NULL,"/triangulation/master/masterlist/",s_masterlist_data.size(),masterlist_data,1,false);
		mosquitto_publish(mosq,NULL,"/triangulation/master/start_burst/",1,FALSE_S,0,false);
		mosquitto_publish(mosq,NULL,"/triangulation/master/start_continiouse/",1,FALSE_S,1,false);
		mosquitto_publish(mosq,NULL,"/triangulation/master/start_ptp_sync/",1,FALSE_S,0,false);
		mosquitto_publish(mosq,NULL,"/triangulation/master/burst_cycles/",1,"4",1,false);
		mosquitto_publish(mosq,NULL,"/time/set_zero",1,"0",1,false);
	}
	//}




	char input_key = 0;
	bool t_burst = false;
	bool t_ptp = false;
	bool t_continiouse = false;
	string amount_burst_cycles = "4";

  while(input_key!=27){
		//const char *num_cycl = "4";
    //menu.options_menu(menu.select());
    //input_key = getch();
		cout << "\n 1: burst cycle amount";
	  cout << "\n 2: start burst data";
	  cout << "\n 3: start ptp time sync";
	  cout << "\n 4: continouse burst";
		cout << "\n 5: simple zero time";

    cin >> input_key;
    cout << input_key;
    switch (input_key){
      case '1':
				//cout <<"\nAmount of Cycles: ";
				//cin >> amount_burst_cycles;
				//const char *num_cycl = amount_burst_cycles.c_str();
				mosquitto_publish(mosq,NULL,"/triangulation/master/burst_cycles/",1,"4",1,false);
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
					mosquitto_publish(mosq,NULL,"/time/set_zero",1,"0",1,false);
				break;
      default:
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
	return 0;
}
