#include "team.h"

t_log* logger = NULL;
t_log* logger_extra = NULL;
t_config* config = NULL;

int log_cpus_totales = 0;
int log_cambios_contexto = 0;
int log_deadlocks_producidos = 0;

char* logfile;

int main() {


	config = leer_config();

	logfile = config_get_string_value(config, "LOG_FILE");
	process_id = config_get_int_value(config, "PROCESS_ID");

	logger = iniciar_logger_obligatorio(logfile, false);

	inicializar_team();

	log_debug(logger, "El team finaliza satisfactoriamente");
	terminar_programa(logger, config);
	return 1;
}


/*
 * Iniciarlizar el proceso team y que quede corriendo
 */

void inicializar_team(void) {
	iniciarPlanificador();
	inciarListasMensajes();
	inicializarDeadlock();
	cargarEntrenadores(); // Tambien se define el objetivo global aca
	enviarGetsAlBroker();
	escucharAlGameboy();
	suscribirseAlBroker();	// Tiene que estar a lo ultimo ya que tiene los wait ara que los entrenadores finalicen
}

t_log* iniciar_logger_obligatorio(char* logfile, int in_console)
{
	return log_create(logfile, "Team", in_console, LOG_LEVEL_INFO);
}

t_config* leer_config(void) {
	return config_create("team.config");
}

void terminar_programa(t_log* logger, t_config* config) {
	if(logger != NULL){
		log_destroy(logger);
	}
	logger = iniciar_logger_obligatorio(logfile, true);
	log_info(logger, "EL TEAM CUMPLE SU OBJETIVO");
	log_info(logger, "CICLOS DE CPU TOTALES: %d", log_cpus_totales);
	log_info(logger, "CAMBIOS DE CONTEXTO REALIZADOS: %d", log_cambios_contexto);
	for (int i = 0; i < list_size(entrenadores_exit->lista); i++) {
		t_tcb* tcb = list_get(entrenadores_exit->lista, i);
		log_info(logger, "CICLOS DE CPU DEL ENTRENADOR %d: %d", tcb->entrenador->id_entrenador, tcb->log_cpus_ejecutados);
	}
	log_info(logger, "DEADLOCKS PRODUCIDOS: %d", log_deadlocks_producidos);

	if(logger != NULL){
		log_destroy(logger);
	}

	if(config != NULL){
		config_destroy(config);
	}
}
