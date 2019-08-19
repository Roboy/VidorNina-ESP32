#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <mosquitto.h>

//#include <thread>


using namespace std;

#define MAX_USERS 10

void sub_thread();
void start_conver(struct mosquitto *mosq);

void my_message_callback(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
	if(message->payloadlen){
		printf("%s %s\n", message->topic, message->payload);
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
		cout << "\nsub to all";
		mosquitto_subscribe(mosq, NULL, "#", 0);

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

	int in_;

	mosquitto_lib_init();
	mosq = mosquitto_new(NULL, clean_session, NULL);
	if(!mosq){
		fprintf(stderr, "Error: Out of memory.\n");
		return 1;
	}


	mosquitto_log_callback_set(mosq, my_log_callback);
	mosquitto_connect_callback_set(mosq, my_connect_callback);
	mosquitto_message_callback_set(mosq, my_message_callback);
	mosquitto_subscribe_callback_set(mosq, my_subscribe_callback);


	if(mosquitto_connect_async(mosq, host, port, keepalive)){
		fprintf(stderr, "Unable to connect.\n");
		return 1;
	}

	mosquitto_subscribe(mosq,NULL,"#", 0);

	cout << "\nasdfasdf";
	cin >> in_;

	mosquitto_loop_start(mosq);


	cout << "\nasdfasdf";
	cin >> in_;

	mosquitto_loop_stop(mosq,true);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return 0;
}
