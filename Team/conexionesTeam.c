/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "conexionesTeam.h"


//////////////////////////////////////////////
//				SUSCRIPCIONES				//
//////////////////////////////////////////////

void suscribirseAlBroker(void) {
	/* char* ip = config_get_string_value(config,"IP_BROKER");
	char* puerto = config_get_string_value(config, "PUERTO_BROKER"); */
	// Abro conexion
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");

	// Creo el mensaje de subscripcion
	t_subscribe* subscripcion = malloc(sizeof(t_subscribe));
	subscripcion->module = TEAM;

	uint32_t subscripcion_size;
	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);

	uint32_t paquete_size;
	void* paquete_serializado = crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, &paquete_size);

	send(conexion, paquete_serializado, paquete_size, 0);

	pthread_t thread;
	pthread_create(&thread, NULL, escucharAlBroker, &conexion); // Hilo para escuchar al broker
	pthread_detach(thread);

	free(subscripcion);
	return;
}

void *escucharAlBroker(void* socket) {
	int i = 1;
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(*((int*)socket));

		switch(paquete->type) {
			case APPEARED_POKEMON:
				// procesarAppeared(paquete); TODO
			case LOCALIZED_POKEMON:
				// procesarLocalized(paquete); TODO
			case CAUGHT_POKEMON:
				// procesarCaught(paquete); TODO
			default:
				printf("Codigo no valido: %d \n", paquete->type);
				i = 0;
		}
	}
	// TODO DESTRUIR EL HILO?
	return NULL;
}


//////////////////////////////////////////////
//					GET						//
//////////////////////////////////////////////

void enviarGetPokemon(t_pokemon* pokemon) {
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");

	uint32_t get_pokemon_size;
	void* serialized_get_pokemon = serializarPokemon(pokemon, &get_pokemon_size);

	uint32_t paquete_size;
	void* paquete_serializado = crear_paquete(GET_POKEMON, serialized_get_pokemon, get_pokemon_size, &paquete_size);

	int status = send(conexion, paquete_serializado, paquete_size, 0); // TODO ver si tengo que esperar a que envie todo el mensaje para recien cerrar la conexion

	liberar_conexion(conexion);

	free(paquete_serializado);
	return;
}


