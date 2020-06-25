/*
 * broker.c
 *
 *  Created on: 24 abr. 2020
 *      Author: utnso
 */

#include"broker.h"


t_config* config = NULL;
t_log* logger = NULL;

int main(void) {

	char* ip;
	char* puerto;
	char* logfile;

	config = leer_config();

//	ip      = config_get_string_value(config, "IP");
//	puerto  = config_get_string_value(config, "PUERTO");
//	logfile = config_get_string_value(config, "LOG_FILE");

	/*Test Valgrind*/
	ip      = "127.0.0.1";
	puerto  = "5003";
	logfile = "/home/utnso/log_broker.txt";

	logger = iniciar_logger(logfile);
	iniciarSignals();
	iniciarMemoria();
	iniciarSubscribers();
	iniciarMensajes();
	iniciarVectorDeSockets();
	iniciarVectorDeSemaforos();
	iniciarColas();
	iniciar_servidor(ip, puerto);


	return 0;
}

t_config* leer_config(void){
	return config_create("broker.config");
}

t_log* iniciar_logger(char* logfile){
	return log_create(logfile, "Broker", true, LOG_LEVEL_DEBUG);
}

void iniciarSignals(){
	signal(SIGUSR1, dump_cache);
}


/*void terminar_programa(t_config* config, t_subscribers* subscribers) {
	config_destroy(config);
	list_destroy(subscribers -> new_pokemon);
	list_destroy(subscribers -> get_pokemon);
	list_destroy(subscribers -> catch_pokemon);
	list_destroy(subscribers -> caught_pokemon);
	list_destroy(subscribers -> appeared_pokemon);
	list_destroy(subscribers -> localized_pokemon);
	free(subscribers);
}

this is basically useless, but we have it here anyway just in case!
*/




