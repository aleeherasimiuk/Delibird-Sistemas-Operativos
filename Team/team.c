#include "team.h"

t_log* logger = NULL;
t_config* config = NULL;

int main() {
	char* logfile;

	config = leer_config();

	logfile = config_get_string_value(config, "LOG_FILE");

	logger = iniciar_logger(logfile);

	inicializar_team();
	return 1;
}


/*
 * Iniciarlizar el proceso team y que quede corriendo
 */

void inicializar_team(void) {
	iniciarPlanificador();
	cargarEntrenadores(); // Tambien se define el objetivo global aca
	abrirSocketParaGameboy();
	suscribirseAlBroker(); // TODO Revisar el escucharAlBroker
	//enviarGetsAlBroker();
}

t_log* iniciar_logger(char* logfile)
{
	return log_create(logfile, "Team", true, LOG_LEVEL_DEBUG);
}

t_config* leer_config(void) {
	return config_create("team.config");
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
	exit(1);
}
