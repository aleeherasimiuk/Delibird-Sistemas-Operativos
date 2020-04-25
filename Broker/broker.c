/*
 * broker.c
 *
 *  Created on: 24 abr. 2020
 *      Author: utnso
 */

#include"broker.h"

int main(void) {

	char* ip;
	char* puerto;

	t_config* config;

	config = leer_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	printf("Server corriendo");
	iniciar_servidor(ip, puerto);

	return 0;
}

t_config* leer_config(void)
{
	return config_create("broker.config");
}

void terminar_programa(t_config* config) {
	config_destroy(config);
}

