#include "team.h"

t_log* logger = NULL;
t_config* config = NULL;

int main() {
	char* ip;
	char* puerto;
	char* logfile;

	config = leer_config();

	ip = config_get_string_value(config,"IP_BROKER");
	puerto = config_get_string_value(config, "PUERTO_BROKER");
	logfile = config_get_string_value(config, "LOG_FILE");

	logger = iniciar_logger(logfile);


	log_info(logger, "Lei la ip %s y el puerto %s", ip, puerto);


	inicializar_team();

	return 1;
}


/*
 * Iniciarlizar el proceso team y que quede corriendo
 */

void inicializar_team(void) {
	cargarEntrenadores();
	// definirObjetivoGlobal(); TODO
	// suscribirseAlBroker(); TODO
	// enviarGetsAlBroker(); TODO
	// abrirSocketParaGameboy(); TODO
}

t_log* iniciar_logger(char* logfile)
{
	return log_create(logfile, "Team", true, LOG_LEVEL_INFO);
}

t_config* leer_config(void) {
	return config_create("team.config");
}
