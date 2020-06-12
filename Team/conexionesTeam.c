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
	int conexiones[3];
	uint32_t process_id = 25; // TODO: TRAER DEL CONFIG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	conexiones[0] = abrirUnaConexion(config);
	suscribirAUnaCola(conexiones[0], APPEARED_POKEMON, process_id);

	conexiones[1] = abrirUnaConexion(config);
	suscribirAUnaCola(conexiones[1], LOCALIZED_POKEMON, process_id);

	conexiones[2] = abrirUnaConexion(config);
	suscribirAUnaCola(conexiones[2], CAUGHT_POKEMON, process_id);


	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, escucharAlSocket, &conexiones[0]);
	pthread_create(&thread2, NULL, escucharAlSocket, &conexiones[1]);
	pthread_create(&thread3, NULL, escucharAlSocket, &conexiones[2]);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

//	for(int i = 0; i < 3; i++){
//		pthread_t thread;
//		log_debug(logger, "Escuchando en %d", conexiones[i]);
//		pthread_create(&thread, NULL, escucharAlSocket, &conexiones[i]); // Hilo para escuchar al broker
//		//pthread_detach(thread);
//		pthread_join(thread, NULL);
//	}


	return;
}

int abrirUnaConexion(t_config* config) {
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");
	if(conexion == CANT_CONNECT){
		log_debug(logger, "No pude conectar :(");
		terminar_programa(conexion, logger, config);
	} else {
		log_debug(logger, "Conexión Abierta");
	}
	return conexion;
}

void suscribirAUnaCola(int conexion, message_type cola, uint32_t process_id){

	// Creo el mensaje de subscripcion
	t_subscribe* subscripcion = subscribe(cola, process_id);

	uint32_t subscripcion_size;
	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);

	uint32_t paquete_size;
	void* paquete_serializado = crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, &paquete_size);

	//TODO: Handlear error
	send(conexion, paquete_serializado, paquete_size, 0);
	free(subscripcion);
	log_debug(logger, "Me suscribí a %d", cola);
}


void *escucharAlSocket(void* socket) {
	int i = 1;
	log_debug(logger, "Escuchando en el socket: %d", *((int*)socket));
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(*((int*)socket));

		if(paquete != NULL){

			switch(paquete->type) {
				case APPEARED_POKEMON:
					// procesarAppeared(paquete); TODO
					log_debug(logger, "Wow! Apareció un Pokemon!");
					break;
				case LOCALIZED_POKEMON:
					// procesarLocalized(paquete); TODO
					log_debug(logger, "Que Google Maps ni Google Maps!. Localized Pokemon PAPÁ");
					break;
				case CAUGHT_POKEMON:
					procesarCaughtPokemon(paquete);

					break;
				default:
					log_debug(logger, "What is this SHIT?.");
					break;
			}
		}
	}
	// TODO DESTRUIR EL HILO?
	return NULL;
}

void procesarCaughtPokemon(t_paquete* paquete){
	t_caught_pokemon* cau_pok = deserializarCaughtPokemon(paquete -> buffer);

	if(*cau_pok == YES){
		log_debug(logger, "Yey! Atrapé un Pokemon!");
	} else if(*cau_pok == NO){
		log_debug(logger, "Ufa! No pude atraparlo :(");
	} else {
		log_debug(logger, "No entiendo man %d o %d o %d", *cau_pok, cau_pok, &cau_pok);
	}
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


