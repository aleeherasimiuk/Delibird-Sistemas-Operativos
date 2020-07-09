/*
 * gamecard.c
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#include "gameboy.h"
#include "utils.h"

t_log* logger = NULL;
t_config* config = NULL;
uint32_t process_id;

int main(int argc, char* argv[]) {
	char* logfile;

	config = leer_config();

	logfile = config_get_string_value(config, "LOG_FILE");

	logger = iniciar_logger(logfile);

	process_id = config_get_int_value(config, "PROCESS_ID");

	if(argc < 3){
		log_error(logger, "Cantidad incorrecta de parámetros");
		terminar_programa(CANT_CONNECT, logger, config);
		exit(1);
	}

	int success = enviar_mensaje(--argc, &argv[1]);

	return 0;
}

t_log* iniciar_logger(char* logfile) {
	return log_create(logfile, "GameBoy", true, LOG_LEVEL_DEBUG);
}

t_config* leer_config(void) {
	return config_create("gameboy.config");
}

void terminar_programa(int socket, t_log* logger, t_config* config) {
	if(socket != CANT_CONNECT){
		close(socket);
	}
	if(logger != NULL){
		log_destroy(logger);
	}
	if(config != NULL){
		config_destroy(config);
	}

	exit(0);
}

