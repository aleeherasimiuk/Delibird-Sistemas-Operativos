/*
 * broker.c
 *
 *  Created on: 24 abr. 2020
 *      Author: utnso
 */

#include"broker.h"


t_config* config = NULL;
t_log* logger = NULL;
t_log* logger_extra = NULL;

int main(void) {

	char* ip;
	char* puerto;
	char* logfile;
	char* log_extra;

	config = leer_config();

	if(config == NULL){
		printf("El archivo de configuración es inválido");
		exit(0);
	}

	ip        = config_get_string_value(config, "IP");
	puerto    = config_get_string_value(config, "PUERTO");
	logfile   = config_get_string_value(config, "LOG_FILE");
	log_extra = config_get_string_value(config, "LOG_EXTRA");
	/*Test Valgrind*/
//	ip      = "127.0.0.1";
//	puerto  = "5003";
//	logfile = "/home/utnso/log_broker.txt";

	logger = iniciar_logger(logfile, "BROKER");
	logger_extra = iniciar_logger(log_extra, "SERVER - EXTRALOG");

	if(logger == NULL || logger_extra == NULL){
		printf("El archivo de log es inválido.");
	}

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

t_log* iniciar_logger(char* logfile, char* name){
	return log_create(logfile, name, true, LOG_LEVEL_INFO);
}



void iniciarSignals(){
	signal(SIGUSR1, dump_cache);
	signal(SIGINT, terminar_programa);
}

void terminar_programa(int signal){

	close(server_socket);

	if(config != NULL)
		config_destroy(config);

	if(logger != NULL)
		log_destroy(logger);
//
//	//destruir_colas();
	destruir_mensajes();
	exit(0);

}




