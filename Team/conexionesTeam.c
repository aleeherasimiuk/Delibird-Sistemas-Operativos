/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "conexionesTeam.h"
uint32_t process_id;


//////////////////////////////////////////////
//				SUSCRIPCIONES				//
//////////////////////////////////////////////

void suscribirseAlBroker(void) {
	// Abro conexion
	t_escucha_socket escuchar_appeared = { 0, APPEARED_POKEMON };
	t_escucha_socket escuchar_localized = { 0, LOCALIZED_POKEMON };
	t_escucha_socket escuchar_caught = { 0, CAUGHT_POKEMON };

	escuchar_appeared.socket = abrirUnaConexion(config);
	suscribirAUnaCola(escuchar_appeared.socket, escuchar_appeared.cola);

	escuchar_localized.socket = abrirUnaConexion(config);
	suscribirAUnaCola(escuchar_localized.socket, escuchar_localized.cola);

	escuchar_caught.socket = abrirUnaConexion(config);
	suscribirAUnaCola(escuchar_caught.socket, escuchar_caught.cola);


	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, escucharAlSocket, &escuchar_appeared);
	pthread_create(&thread2, NULL, escucharAlSocket, &escuchar_localized);
	pthread_create(&thread3, NULL, escucharAlSocket, &escuchar_caught);

	esperarAQueFinalicenLosEntrenadores();
	log_debug(logger, "Ya finalizaron todos los entrenadores");

	return;
}


int abrirUnaConexion(t_config* config) {
	int tiempo_reconexion = config_get_int_value(config, "TIEMPO_RECONEXION");
	int conexion;
	int hubo_reconexion = 0;

	while (1) {
		// Reconexion
		conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");
		if(conexion == CANT_CONNECT){
			log_debug(logger, "No me pude conectar, espero para reintentar");
			hubo_reconexion = 1;
			log_info(logger, "REINTENTO DE COMUNICACIÓN CON EL BROKER");
			sleep(tiempo_reconexion);
		} else {
			log_debug(logger, "Conexión Abierta");
			if (hubo_reconexion)
				log_info(logger, "SE CONECTA AL BROKER EN EL SOCKET: %d", conexion);
			break;
		}
	}
	return conexion;
}

void suscribirAUnaCola(int conexion, message_type cola){

	// Creo el mensaje de subscripcion
	t_subscribe* subscripcion = subscribe(cola, process_id);

	uint32_t subscripcion_size;
	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);

	uint32_t paquete_size;
	void* paquete_serializado = crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, &paquete_size);

	send(conexion, paquete_serializado, paquete_size, 0);

	free(subscripcion);
	free(serialized_subscribe);
	free(paquete_serializado);

	log_debug(logger, "Me suscribí a %d", cola);
}


void *escucharAlSocket(void* data) {
	t_escucha_socket* escucha_socket = (t_escucha_socket*) data;
	int socket = escucha_socket->socket;
	message_type cola = escucha_socket->cola;
	pthread_t thread;

	int i = 1;
	while(i) {
		log_debug(logger, "Escuchando en el socket: %d", socket);
		t_paquete* paquete = recibirPaquete(socket);


		if(paquete != NULL){
			enviarACK(paquete -> id);

			//void* ptrStream = paquete->buffer->stream; // lo guardo porque mientras se desserializa se mueve el puntero del stream

			switch(paquete->type) {
				case APPEARED_POKEMON:
					pthread_create(&thread, NULL, procesarAppeared, (void*) paquete);
					pthread_detach(thread);
					break;
				case LOCALIZED_POKEMON:
					pthread_create(&thread, NULL, procesarLocalized, (void*) paquete);
					pthread_detach(thread);
					break;
				case CAUGHT_POKEMON:
					pthread_create(&thread, NULL, procesarCaughtPokemon, (void*) paquete);
					pthread_detach(thread);
					break;
				default:
					log_debug(logger, "What is this SHIT?.");
					liberar_paquete(paquete);
					break;
			}

			//free(ptrStream);
			//free(paquete->buffer);
			//free(paquete);
		} else {
			// Políticas de reconexión
			close(socket);

			// Intento abrir la conexion de nuevo
			socket = abrirUnaConexion(config);
			// Y me vuelvo a suscribir
			suscribirAUnaCola(socket, cola);
		}
	}
	return NULL;
}

// devuelve el ID del mensaje enviado, 0 => error
uint32_t esperarID (int socket) {
	t_paquete* paquete = recibirPaquete(socket);
	uint32_t id = 0;

	if (paquete != NULL) {
		switch(paquete->type) {
			case ID:
				id = procesarID(paquete);
				break;
			default:
				log_error(logger, "No se recibio un ID como corresponde");
		}
		liberar_paquete(paquete);
	}
	return id;
}

uint32_t procesarID(t_paquete* paquete) {
	t_id* id = paquete -> buffer -> stream;
	log_debug(logger, "Recibí el ID: %d", *id);
	return *id;
}


void escucharAlGameboy(){
	pthread_t thread;
	pthread_create(&thread, NULL ,abrirSocketParaGameboy, NULL);
	pthread_detach(thread);
}

void* abrirSocketParaGameboy(){

	char* ip = config_get_string_value(config, "IP");
	char* puerto = config_get_string_value(config, "PUERTO");
	log_debug(logger, "Estoy escuchando al gameboy en %s:%s", ip, puerto);
	crear_servidor(ip, puerto, serve_client);

	return NULL;
}

void serve_client(int* socket){
	message_type type = recibirCodigoDeOperacion(*socket);

	if(type != -1) {
		log_debug(logger, "Procesando solicitud");
		process_request(type, *socket);
	}else {
		log_debug(logger, "No puedo procesar la solicitud");
	}
}

void process_request(message_type type, int socket){

	t_paquete* paquete = recibirPaqueteSi(socket, type);

	switch(type){

		case APPEARED_POKEMON:
			procesarAppeared(paquete);
			break;

		case CAUGHT_POKEMON:
			procesarCaughtPokemon(paquete);
			break;

		default:
			log_error(logger, "Código de operación inválido");
	}

}

void enviarACK(uint32_t id){

	int conexion = abrirUnaConexion(config);

	log_debug(logger,"Enviaré un ACK por el id: %d",id);
	t_ack* _ack = ack(process_id, id);

	uint32_t bytes_ack;
	void* serialized_ack = serializarACK(_ack, &bytes_ack);

	uint32_t bytes;
	void* a_enviar = crear_paquete(ACK, serialized_ack, bytes_ack, &bytes);

	int status = send(conexion, a_enviar, bytes, 0);
	log_debug(logger, "Envié un ACK al ID: %d, con status: %d", id, status);

	free(_ack);
	free(serialized_ack);
	free(a_enviar);

	close(conexion);

}


//////////////////////////////////////////////
//					GET						//
//////////////////////////////////////////////

void* enviarGetPokemon(void* data) {
	t_pokemon* pokemon = (t_pokemon*) data;
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");

	if(conexion == CANT_CONNECT) {

		log_info(logger, "ERROR DE COMUNICACIÓN AL BROKER: se ejecuta comportamiento default de GET_POKEMON %s => no existen locaciones", pokemon->name);
		// Comportamiento default: no existen locaciones de ese pokemon
		addGetEnviado(0);

		t_localized_pokemon* dummy_localized = localized_pokemon(pokemon, 0, NULL);

		uint32_t bytes;
		void* serialized_localized_pokemon = serializarLocalizedPokemon(dummy_localized, &bytes);

		t_paquete* dummy_paquete = crearPaquete();
		dummy_paquete->type = LOCALIZED_POKEMON;
		dummy_paquete->buffer = malloc(sizeof(t_buffer));
		dummy_paquete->buffer->stream_size = bytes;
		dummy_paquete->buffer->stream = serialized_localized_pokemon;

		procesarLocalized(dummy_paquete);

		free(dummy_localized);

		//free(serialized_localized_pokemon);
		//free(dummy_paquete->buffer);
		//free(dummy_paquete);

	} else {
		uint32_t get_pokemon_size;
		void* serialized_get_pokemon = serializarPokemon(pokemon, &get_pokemon_size);

		uint32_t paquete_size;
		void* paquete_serializado = crear_paquete(GET_POKEMON, serialized_get_pokemon, get_pokemon_size, &paquete_size);

		send(conexion, paquete_serializado, paquete_size, 0);

		uint32_t id = esperarID(conexion);
		addGetEnviado(id);

		liberar_conexion(conexion);

		free(paquete_serializado);
		free(serialized_get_pokemon);
	}

	return NULL;
}

//////////////////////////////////////////////
//				LOCALIZED					//
//////////////////////////////////////////////

void* procesarLocalized(void* data) {
	t_paquete* paquete = (t_paquete*) data;
	void* ptrStream = paquete->buffer->stream; // lo guardo porque mientras se desserializa se mueve el puntero del stream

	t_localized_pokemon* pok = deserializarLocalizedPokemon(paquete -> buffer);
	t_pokemon* pokemon_aux = NULL;

	log_debug(logger, "Se localizaron %d Pokemon: %s!", pok->cant_coords, pok -> pokemon -> name);
	// LOGUEO
	char* log_msg = string_from_format("LLEGA UN MESAJE: ID: %d ID_CORR: %d DATA: LOCALIZED_POKEMON %s %d ", paquete->id, paquete->correlative_id, pok->pokemon->name, pok->cant_coords);

	for (int i = 0; i < pok->cant_coords; i++) {
		string_append_with_format(&log_msg, "%d %d ", pok->coords_array[i]->posX, pok->coords_array[i]->posY);
	}
	log_info(logger, log_msg);
	free(log_msg);

	// FIN LOGUEO


	if (getEnviadoConID(paquete->correlative_id, NULL)) {
		if (pokemonNecesario(pok->pokemon)) {
			log_debug(logger, "El pokemon es necesario");

			for (int i = 0; i < pok->cant_coords; i++) {
				pokemon_aux = malloc(sizeof(t_pokemon));
				// Lo copio porque sino cuando se libere el pokemon en algun lado, va a liberar a todos
				memcpy(pokemon_aux, pok->pokemon, sizeof(t_pokemon));
				pokemon_aux->name_size = pok->pokemon->name_size;
				memcpy(pokemon_aux->name, pok->pokemon->name, pokemon_aux->name_size);

				agregarPokemonAlMapa(pokemon_aux, pok->coords_array[i]);
			}

			addPokemonRecibido(pok->pokemon->name);
		} else {
			log_debug(logger, "No necesito un %s ahora mismo", pok->pokemon->name);
			for (int i = 0; i < pok->cant_coords; i++) {
				free(pok->coords_array[i]);
			}
		}
		eliminarGetEnviado(paquete->correlative_id);
	}

	free(pok->pokemon);

	if (pok->coords_array != NULL)
		free(pok->coords_array);

	free(pok);

	if (pokemon_aux != NULL)
		free(pokemon_aux);

	free(ptrStream);
	free(paquete->buffer);
	free(paquete);

	return NULL;
}


//////////////////////////////////////////////
//				APPEARED					//
//////////////////////////////////////////////

void* procesarAppeared(void* data) {
	t_paquete* paquete = (t_paquete*) data;
	void* ptrStream = paquete->buffer->stream; // lo guardo porque mientras se desserializa se mueve el puntero del stream

	t_appeared_pokemon* pok = deserializarAppearedPokemon(paquete -> buffer);

	log_debug(logger, "Wow! Apareció un Pokemon: %s!", pok -> pokemon -> name);
	log_info(logger, "LLEGA UN MESAJE: ID: %d ID_CORR: %d DATA: APPEARED_POKEMON %s %d %d", paquete->id, paquete->correlative_id, pok->pokemon->name, pok->coords->posX, pok->coords->posY);

	if (pokemonNecesario(pok->pokemon)) {
		log_debug(logger, "El pokemon es necesario");
		agregarPokemonAlMapa(pok->pokemon, pok->coords);
		addPokemonRecibido(pok->pokemon->name);
	} else {
		log_debug(logger, "No necesito un %s ahora mismo", pok->pokemon->name);
		free(pok->pokemon->name);
		free(pok->pokemon);
		free(pok->coords);
	}
	free(pok);
	free(ptrStream);
	free(paquete->buffer);
	free(paquete);

	return NULL;
}

//////////////////////////////////////////////
//					CATCH					//
//////////////////////////////////////////////

void enviarCatchPokemon(t_pokemon_en_mapa* pokemon_en_mapa, t_tcb* tcb) {

	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");

	if(conexion == CANT_CONNECT) {
		log_info(logger, "ERROR DE COMUNICACIÓN AL BROKER: se ejecuta comportamiento default de CATCH_POKEMON %s => se atrapa el pokemon", pokemon_en_mapa->pokemon->name);

		// Comportamiento default: se atrapa el pokemon
		addCatchEnviado(0, tcb);
		uint32_t* caught = malloc(sizeof(uint32_t));
		*caught = YES;
		t_caught_pokemon* dummy_caught = caught_pokemon(caught);

		uint32_t bytes;
		void* serialized_caught_pokemon = serializarCaughtPokemon(dummy_caught, &bytes);

		t_paquete* dummy_paquete = crearPaquete();
		dummy_paquete->type = CAUGHT_POKEMON;
		dummy_paquete->buffer = malloc(sizeof(t_buffer));
		dummy_paquete->buffer->stream_size = bytes;
		dummy_paquete->buffer->stream = serialized_caught_pokemon;

		procesarCaughtPokemon(dummy_paquete);

		//free(serialized_caught_pokemon);
		//free(dummy_paquete->buffer);
		//free(dummy_paquete);

	} else {
		// Un t_pokemon_en_mapa tiene la misma estructura que un t_catch_pokemon
		uint32_t catch_pokemon_size;
		void* serialized_catch_pokemon = serializarCatchPokemon((t_catch_pokemon*) pokemon_en_mapa, &catch_pokemon_size);

		uint32_t paquete_size;
		void* paquete_serializado = crear_paquete(CATCH_POKEMON, serialized_catch_pokemon, catch_pokemon_size, &paquete_size);

		send(conexion, paquete_serializado, paquete_size, 0);

		uint32_t id = esperarID(conexion);
		addCatchEnviado(id, tcb);

		liberar_conexion(conexion);

		free(serialized_catch_pokemon);
		free(paquete_serializado);
	}
	return;
}

//////////////////////////////////////////////
//					CAUGHT					//
//////////////////////////////////////////////

void* procesarCaughtPokemon(void* data) {
	t_paquete* paquete = (t_paquete*) data;
	void* ptrStream = paquete->buffer->stream; // lo guardo porque mientras se desserializa se mueve el puntero del stream



	t_caught_pokemon* cau_pok = deserializarCaughtPokemon(paquete -> buffer);

	log_info(logger, "LLEGA UN MESAJE: ID: %d ID_CORR: %d DATA: CAUGHT_POKEMON %d", paquete->id, paquete->correlative_id, *cau_pok);

	t_tcb* tcb = traerTcbDelCatchConID(paquete->correlative_id);

	if (tcb == NULL) {	// Si ese id no corresponde a un catch enviado por este team, ignorar
		log_debug(logger, "Este proceso no envió un catch con id %d", paquete->correlative_id);
		liberar_paquete(paquete);
		return NULL;
	}

	if(*cau_pok == YES){
		log_debug(logger, "Yey! Atrapé un Pokemon!");
		// Cargo en el entrenador
		cargarPokemonEnListaDeInventario(tcb->entrenador->pokes_actuales, tcb->entrenador->objetivo->pokemon->name);
	} else if(*cau_pok == NO){
		log_debug(logger, "Ufa! No pude atraparlo :(");
		
		pthread_mutex_lock(&mutex_actuales_global);
		sacarPokemonEnListaDeInventario(actuales_global, tcb->entrenador->objetivo->pokemon->name);
		pthread_mutex_unlock(&mutex_actuales_global);
		buscarPokemonAuxiliarYPasarAlMapa(tcb->entrenador->objetivo->pokemon->name);
	} else {
		log_debug(logger, "No entiendo man %d o %d o %d", *cau_pok, cau_pok, &cau_pok);
	}

	// libero el objetivo
	//free(tcb->entrenador->objetivo->pokemon->name); // El nombre está
	free(tcb->entrenador->objetivo->pokemon);
	free(tcb->entrenador->objetivo->posicion);
	free(tcb->entrenador->objetivo);
	tcb->entrenador->objetivo = NULL;

	eliminarCatchEnviado(paquete->correlative_id);

	// como lo cambio de lista despues de liberar al auxiliar, si hay otro entrenador, va a ir a buscarlo el otro.
	cambiarColaSegunCapacidad(tcb);

	free(ptrStream);
	free(paquete->buffer);
	free(paquete);


	return NULL;
}
