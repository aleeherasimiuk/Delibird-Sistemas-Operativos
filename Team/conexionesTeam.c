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
	// Abro conexion
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");
	log_info(logger, "Conexión Abierta");

	uint32_t process_id = 25; // TODO: TRAER DEL CONFIG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	suscribirAUnaCola(conexion, APPEARED_POKEMON, process_id);
	suscribirAUnaCola(conexion, LOCALIZED_POKEMON, process_id);
	suscribirAUnaCola(conexion, CAUGHT_POKEMON, process_id);




	pthread_t thread;
	pthread_create(&thread, NULL, escucharAlSocket, &conexion); // Hilo para escuchar al broker
	//pthread_detach(thread);
	pthread_join(thread, NULL);


	return;
}

void suscribirAUnaCola(int conexion, message_type cola, uint32_t process_id){
	// Creo el mensaje de subscripcion
	t_subscribe* subscripcion = malloc(sizeof(t_subscribe));
	subscripcion -> queue_to_subscribe = cola;
	subscripcion -> process_id = process_id;

	uint32_t subscripcion_size;
	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);

	uint32_t paquete_size;
	void* paquete_serializado = crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, &paquete_size);

	send(conexion, paquete_serializado, paquete_size, 0);
	free(subscripcion);
	log_info(logger, "Me suscribí a %d", cola);
}


void *escucharAlSocket(void* socket) {
	int i = 1;
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(*((int*)socket));

		switch(paquete->type) {
			case APPEARED_POKEMON:
				// procesarAppeared(paquete); TODO
				log_info(logger, "Llegó un APPEARED_POKEMON");
				break;
			case LOCALIZED_POKEMON:
				// procesarLocalized(paquete); TODO
				log_info(logger, "Llegó un LOCALIZED_POKEMON");
				break;
			case CAUGHT_POKEMON:
				log_info(logger, "Llegó un CAUGHT_POKEMON");
				break;
			default:
				//printf("Codigo no valido: %d \n", paquete->type);
				//i = 0;
				break;
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

	int status = send(conexion, paquete_serializado, paquete_size, 0);

	// TODO ESperar el ID del mensaje

	liberar_conexion(conexion);

	free(paquete_serializado);
	return;
}


