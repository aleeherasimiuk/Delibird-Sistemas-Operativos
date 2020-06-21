/*
 * gamecard.c
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#include "conexionesGamecard.h"

uint32_t process_id;

void suscribirGameCardAlBroker(void){
		int conexiones[3];

		conexiones[0] = abrirUnaConexionGameCard(config);
		suscribirAUnaCola(conexiones[0], NEW_POKEMON, process_id);

		conexiones[1] = abrirUnaConexionGameCard(config);
		suscribirAUnaCola(conexiones[1], CATCH_POKEMON, process_id);

		conexiones[2] = abrirUnaConexionGameCard(config);
		suscribirAUnaCola(conexiones[2], GET_POKEMON, process_id);


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

int abrirUnaConexionGameCard(t_config* config) {
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");
	return conexion;
}

void *escucharAlSocket(void* socket) {
	int i = 1;
	log_debug(logger, "Escuchando en el socket: %d", *((int*)socket));
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(*((int*)socket));

		if(paquete != NULL){

			switch(paquete->type) {
				case NEW_POKEMON:
					//procesarNewPokemon(paquete);
					break;
				case CATCH_POKEMON:
					// procesarCatchPokemon(paquete); TODO
					//log_debug(logger, "Que Google Maps ni Google Maps!. Localized Pokemon PAPÁ");
					break;
				case GET_POKEMON:
					//procesarGetPokemon(paquete);
					//log_debug(logger, "Despues de procesar paquete");
					break;
				default:
					log_debug(logger, "No entiendo le mensaje, debe ser NEW_POKEMON, CATCH_POKEMON o GET_POKEMON");
					break;
			}
		}
	}
	// TODO DESTRUIR EL HILO?
	return NULL;
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

