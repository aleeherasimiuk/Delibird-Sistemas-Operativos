#include "team.h"

int main() {

	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	//Loggear "soy un log"

	log_info(logger, "soy un log");

	config = leer_config();

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger, "Lei la ip %s y el puerto %s", ip, puerto);

	conexion = crear_conexion(ip, puerto);

	t_localized_pokemon pokemones = recibir_mensaje(conexion);




}
