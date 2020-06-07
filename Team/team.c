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
	printf("Hola!");
	iniciarPlanificador();
	printf("Hola2!");
	cargarEntrenadores(); // Tambien se define el objetivo global aca
	printf("Hola3!");
	suscribirseAlBroker(); // TODO Revisar el escucharAlBroker
	printf("Hola4!");
	enviarGetsAlBroker();
	// abrirSocketParaGameboy(); TODO
}

t_log* iniciar_logger(char* logfile)
{
	return log_create(logfile, "Team", true, LOG_LEVEL_INFO);
}

t_config* leer_config(void) {
	return config_create("team.config");
}
