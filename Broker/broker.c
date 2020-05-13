/*
 * broker.c
 *
 *  Created on: 24 abr. 2020
 *      Author: utnso
 */

#include"broker.h"


//TODO: SACAR LA VARIABLE GLOBAL!
t_subscribers* subscribers;

int main(void) {

	char* ip;
	char* puerto;

	t_config* config;

	config = leer_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");

	subscribers = iniciarSubscribers();
	iniciar_servidor(ip, puerto);


	return 0;
}

t_config* leer_config(void)
{
	return config_create("broker.config");
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




