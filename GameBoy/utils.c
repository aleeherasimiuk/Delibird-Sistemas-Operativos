/*
 * utils.c
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#include "utils.h"



int enviar_mensaje(int argc, char* argv[]){


	if(!handleProcessPokemon(argc, argv)){
		log_debug(logger, "TEST");
		wrong_parameters();
	}


	char* proceso = argv[0];
	int conexion;
	uint32_t paquete_size;
	void* paquete = preparar_mensaje(proceso, --argc, &argv[1], &paquete_size);

	char* ip, *puerto;
	char* pr = compare_string(proceso, "SUSCRIPTOR")? "BROKER" : proceso;

	ip = concat_string_config(pr, IP);
	puerto = concat_string_config(pr, PUERTO);

	// Abro conexión con el proceso en cuestión
	conexion = abrirUnaConexion(ip, puerto);

	log_info(logger, "Se ha establecido una conexión con: %s", pr);


	//int status = send(conexion, paquete, paquete_size, 0);
	int status = send_msg(conexion, paquete, paquete_size);
	log_debug(logger, "Envié un mensaje con status: %d", status);

	if(compare_string(proceso, "SUSCRIPTOR"))
		escuchar_broker(conexion, (convert_to_int(argv[2])), argv[1]);

	if(compare_string(proceso, "BROKER"))
		esperarID(conexion);

	if(compare_string(proceso, "TEAM") || compare_string(proceso, "GAMECARD"))
		esperarACK(conexion);


	free(paquete);


	terminar_programa(conexion, logger, config);
	return 0;

}

void* prepararNewPokemon(char* process, uint32_t argc, char* argv[], uint32_t* paquete_size){
	if(!handleNewPokemon(process, argc - 1, &argv[1]))
		wrong_parameters();

	t_pokemon* pokemon = crearPokemon(argv[1]);
	uint32_t posX = convert_to_int(argv[2]);
	uint32_t posY = convert_to_int(argv[3]);
	uint32_t cant = convert_to_int(argv[4]);
	t_new_pokemon* _new_pokemon = new_pokemon(pokemon, posX, posY, cant);

	uint32_t message_bytes;
	void* serialized_message = serializarNewPokemon(_new_pokemon, &message_bytes);

	if(compare_string(process, "BROKER"))
		return crear_paquete(NEW_POKEMON, serialized_message, message_bytes, paquete_size);


	uint32_t id = convert_to_int(argv[5]);
	return crear_paquete_con_id(NEW_POKEMON, serialized_message, message_bytes, id, paquete_size);
}

void* prepararAppearedPokemon(char* process, uint32_t argc, char* argv[], uint32_t* paquete_size){
	if(!handleAppearedPokemon(process, argc - 1, &argv[1]))
		wrong_parameters();

	t_pokemon* pokemon = crearPokemon(argv[1]);
	uint32_t posX = convert_to_int(argv[2]);
	uint32_t posY = convert_to_int(argv[3]);
	t_appeared_pokemon* _appeared_pokemon = appeared_pokemon(pokemon, posX, posY);

	uint32_t message_bytes;
	void* serialized_message = serializarAppearedPokemon(_appeared_pokemon, &message_bytes);

	if(compare_string(process, "TEAM"))
		return crear_paquete(APPEARED_POKEMON, serialized_message, message_bytes, paquete_size);

	uint32_t id_correlativo = convert_to_int(argv[4]);
	return crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_message, message_bytes, id_correlativo, paquete_size);

}

void* prepararCatchPokemon(char* process, uint32_t argc, char* argv[], uint32_t* paquete_size){

	int st = handleCatchPokemon(process, --argc, &argv[1]);
	if(st == WRONG_PARAMETERS)
		wrong_parameters();

	t_pokemon* pokemon = crearPokemon(argv[1]);
	uint32_t posX = convert_to_int(argv[2]);
	uint32_t posY = convert_to_int(argv[3]);
	t_catch_pokemon* _catch_pokemon = catch_pokemon(pokemon, posX, posY);

	uint32_t message_bytes;
	void* serialized_message = serializarCatchPokemon(_catch_pokemon, &message_bytes);

	if(compare_string(process, "BROKER"))
		return crear_paquete(CATCH_POKEMON, serialized_message, message_bytes, paquete_size);

	uint32_t id = convert_to_int(argv[4]);
	return crear_paquete_con_id(CATCH_POKEMON, serialized_message, message_bytes, id, paquete_size);


}
void* prepararCaughtPokemon(char* process, uint32_t argc, char* argv[], uint32_t* paquete_size){
	int st = handleCaughtPokemon(process, --argc, &argv[1]);
	if(st == WRONG_PARAMETERS)
		wrong_parameters();

	uint32_t id_correlativo = convert_to_int(argv[1]);
	uint32_t* caught = malloc(sizeof(uint32_t));
	char* ok = argv[2];

	*caught = compare_string(ok, "YES") || compare_string(ok, "OK");


	t_caught_pokemon* _caught_pokemon = caught_pokemon(caught);


	uint32_t bytes;
	void* serialized_message = serializarCaughtPokemon(_caught_pokemon, &bytes);
	return crear_paquete_con_id_correlativo(CAUGHT_POKEMON, serialized_message, bytes, id_correlativo, paquete_size);
}

void* prepararGetPokemon(char* process, uint32_t argc, char* argv[], uint32_t* paquete_size){

	int st = handleGetPokemon(process, --argc, &argv[1]);
	if(st == WRONG_PARAMETERS)
		wrong_parameters();

	t_pokemon* pokemon = crearPokemon(argv[1]);
	log_debug(logger, "%d", strlen(argv[1]));
	t_get_pokemon* _get_pokemon = get_pokemon(pokemon);
	int size;
	void* serialized_message = serializarPokemon(_get_pokemon, &size);

	if(compare_string(process, "BROKER"))
		return crear_paquete(GET_POKEMON, serialized_message, size, paquete_size);

	uint32_t id = convert_to_int(argv[2]);
	return crear_paquete_con_id(GET_POKEMON, serialized_message, size, id, paquete_size);
}

void* prepararSuscriptor(char* process, uint32_t argc, char* argv[], uint32_t* paquete_size){
	if(!handleSuscriptor(argc, &argv[0]))
		wrong_parameters();

	message_type queue = string_to_queue(argv[0]);

	t_subscribe* subscripcion = subscribe(queue, process_id);

	uint32_t subscripcion_size;
	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);
	free(subscripcion);
	return crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, paquete_size);
}


void* preparar_mensaje(char* process, int argc, char* argv[], uint32_t* paquete_size){
	char* mensaje = argv[0];

	if(compare_string(process, "SUSCRIPTOR"))
		return prepararSuscriptor(process, argc, argv, paquete_size);

	if(compare_string(mensaje, "NEW_POKEMON"))
		return prepararNewPokemon(process, argc, argv, paquete_size);


	if(compare_string(mensaje, "APPEARED_POKEMON"))
		return prepararAppearedPokemon(process, argc, argv, paquete_size);

	if(compare_string(mensaje, "CATCH_POKEMON"))
		return prepararCatchPokemon(process, argc, argv, paquete_size);


	if(compare_string(mensaje, "CAUGHT_POKEMON"))
		return prepararCaughtPokemon(process, argc, argv, paquete_size);


	if(compare_string(mensaje, "GET_POKEMON"))
		return prepararGetPokemon(process, argc, argv, paquete_size);


	return NULL;

}

void esperarID(uint32_t conexion){

	while(1){
		t_paquete* paquete = recibirPaquete(conexion);

		if(paquete == NULL)
			break;

		if(paquete -> type == ID){
			t_id* id = (paquete -> buffer -> stream);
			log_info(logger, "ID del mensaje enviado: #%d", *id);
			break;

		}

	}
}

void esperarACK(uint32_t conexion){

	while(1){
		t_paquete* paquete = recibirPaquete(conexion);

		if(paquete == NULL)
			break;

		if(paquete -> type == ACK){
			t_ack* ack = deserializarACK(paquete -> buffer);
			log_info(logger, "El proceso #%d, recibió el mensaje #%d", ack -> process_id, ack -> id);
			free(paquete);
			close(conexion);
			break;
		}

	}
}



void escuchar_broker(uint32_t conexion, uint32_t seconds, char* queue){
	log_debug(logger, "Escuchando en el socket: %d", conexion);

	listen_t* listening_for = malloc(sizeof(listen_t));
	listening_for -> conexion = conexion;
	listening_for -> seconds = seconds;

	log_info(logger, "Suscrito a %s por %d segundos.", queue, seconds);

	pthread_t thread;
	pthread_create(&thread, NULL, escucharPorTiempoLimitado, listening_for);
	pthread_detach(&thread);

	int i = 1;
	while(i) {

		t_paquete* paquete = recibirPaquete(conexion);

		if(paquete == NULL){
			break;
		}

		if(paquete -> type != ID)
			enviarACK(paquete -> id);

		switch(paquete -> type) {

			case NEW_POKEMON:
				procesarNewPokemon(paquete);
				break;

			case APPEARED_POKEMON:
				procesarAppearedPokemon(paquete);
				break;

			case LOCALIZED_POKEMON:
				procesarLocalizedPokemon(paquete);
				break;

			case CATCH_POKEMON:
				procesarCatchPokemon(paquete);
				break;

			case CAUGHT_POKEMON:
				procesarCaughtPokemon(paquete);
				break;

			case GET_POKEMON:
				procesarGetPokemon(paquete);
				break;

			default:
				log_debug(logger, "What is this SHIT?.");
				break;
		}

	}
}

void procesarNewPokemon(t_paquete* paquete){

	void* stream = paquete -> buffer -> stream; // Para poder hacer free nomás
	t_new_pokemon* new_pokemon = deserializarNewPokemon(paquete -> buffer);

	log_info(logger, "Se recibió un NEW POKEMON");
	log_info(logger, "Pokemon: %s", new_pokemon -> pokemon -> name);
	log_info(logger, "Cantidad: %d", new_pokemon -> cantidad);
	log_info(logger, "Posición: (%d, %d)\n", new_pokemon -> coords -> posX, new_pokemon -> coords -> posY);

	free(new_pokemon -> pokemon);
	free(new_pokemon -> coords);
	free(new_pokemon);

	free(stream);
	free(paquete -> buffer);
	free(paquete);


}

void procesarAppearedPokemon(t_paquete* paquete){

	void* stream = paquete -> buffer -> stream; // Para poder hacer free nomás
	t_appeared_pokemon* appeared_pokemon = deserializarAppearedPokemon(paquete -> buffer);

	log_info(logger, "Se recibió un APPEARED POKEMON");
	log_info(logger, "ID del NEW: %d", paquete -> correlative_id);
	log_info(logger, "Pokemon: %s", appeared_pokemon -> pokemon -> name);
	log_info(logger, "Posición: (%d, %d)\n", appeared_pokemon -> coords -> posX, appeared_pokemon -> coords -> posY);

	free(appeared_pokemon -> pokemon -> name);
	free(appeared_pokemon -> pokemon);
	free(appeared_pokemon -> coords);
	free(appeared_pokemon);

	free(stream);
	free(paquete -> buffer);
	free(paquete);
}

void procesarCatchPokemon(t_paquete* paquete){

	void* stream = paquete -> buffer -> stream; // Para poder hacer free nomás
	t_catch_pokemon* catch_pokemon = deserializarCatchPokemon(paquete -> buffer);

	log_info(logger, "Se recibió un CATCH POKEMON");
	log_info(logger, "Pokemon: %s", catch_pokemon -> pokemon -> name);
	log_info(logger, "Posición: (%d, %d)\n", catch_pokemon -> coords -> posX, catch_pokemon -> coords -> posY);

	free(catch_pokemon -> pokemon -> name);
	free(catch_pokemon -> pokemon);
	free(catch_pokemon -> coords);
	free(catch_pokemon);

	free(stream);
	free(paquete -> buffer);
	free(paquete);

}
void procesarCaughtPokemon(t_paquete* paquete){

	t_caught_pokemon* caught_pokemon = deserializarCaughtPokemon(paquete -> buffer);

	log_info(logger, "Se recibió un CAUGHT POKEMON");
	log_info(logger, "ID del CATCH: %d", paquete -> correlative_id);
	log_info(logger, "Atrapado: %s\n", *caught_pokemon == YES? "Si" : "No");

	free(caught_pokemon);

	//free(stream);
	free(paquete -> buffer);
	free(paquete);
}
void procesarLocalizedPokemon(t_paquete* paquete){

	void* stream = paquete -> buffer -> stream; // Para poder hacer free nomás
	t_localized_pokemon* localized_pokemon = deserializarLocalizedPokemon(paquete -> buffer);

	log_info(logger, "Se recibió un LOCALIZED POKEMON");
	log_info(logger, "Pokemon: %s", localized_pokemon -> pokemon -> name);
	log_info(logger, "Cantidad de coordenadas: %d", localized_pokemon -> cant_coords);

	for(int i = 0; i < localized_pokemon -> cant_coords; i++){
		log_info(logger, "Posición: (%d, %d)%s",
				localized_pokemon -> coords_array[i] -> posX,
				localized_pokemon -> coords_array[i] -> posY,
				i == localized_pokemon -> cant_coords - 1? "\n": "");

		free(localized_pokemon -> coords_array[i]);
	}

	free(localized_pokemon -> pokemon -> name);
	free(localized_pokemon -> pokemon);
	free(localized_pokemon -> coords_array);
	free(localized_pokemon);

	free(stream);
	free(paquete -> buffer);
	free(paquete);

}
void procesarGetPokemon(t_paquete* paquete){

	void* stream = paquete -> buffer -> stream; // Para poder hacer free nomás
	t_get_pokemon* get_pokemon = deserializarPokemon(&(paquete -> buffer));


	log_info(logger, "Se recibió un GET POKEMON");
	log_info(logger, "Pokemon: %s\n", get_pokemon -> name);

	free(get_pokemon -> name);
	free(get_pokemon);
	free(stream);
	free(paquete -> buffer);
	free(paquete);

}

// Abstraer junto con el de conexionesTeam
void enviarACK(uint32_t id){

	int conexion = abrirUnaConexion("IP_BROKER", "PUERTO_BROKER");

	log_debug(logger,"Enviaré un ACK por el id: %d",id);
	t_ack* _ack = ack(process_id, id);

	uint32_t bytes_ack;
	void* serialized_ack = serializarACK(_ack, &bytes_ack);

	uint32_t bytes;
	void* a_enviar = crear_paquete(ACK, serialized_ack, bytes_ack, &bytes);

	//int status = send(conexion, a_enviar, bytes, 0);
	int status = send_msg(conexion, a_enviar, bytes);
	log_debug(logger, "Envié un ACK al ID: %d, con status: %d", id, status);
	free(a_enviar);
	close(conexion);


}

//IDEM
int abrirUnaConexion(char* campo_ip, char* campo_puerto) {
	int conexion = crear_conexion_con_config(config, campo_ip, campo_puerto);
	if(conexion == CANT_CONNECT){
		log_error(logger, "No se ha podido realizar la conexión");
		terminar_programa(conexion, logger, config);
	} else {
		log_debug(logger, "Conexión Abierta");
	}
	return conexion;
}

void* escucharPorTiempoLimitado(void* listening_for){

	listen_t* listen_for = (listen_t*)listening_for;
	sleep(listen_for -> seconds);
	log_debug(logger, "LISTO");
	terminar_programa(listen_for -> conexion, logger, config);
	exit(1);
	return NULL;
}


void wrong_parameters(){
	log_error(logger, "Parámetros incorrectos");
	terminar_programa(CANT_CONNECT, logger, config);
	exit(1);
}

message_type string_to_queue(char* msg){

	if(compare_string(msg, "NEW_POKEMON"))
		return NEW_POKEMON;

	if(compare_string(msg, "APPEARED_POKEMON"))
		return APPEARED_POKEMON;

	if(compare_string(msg, "CATCH_POKEMON"))
		return CATCH_POKEMON;

	if(compare_string(msg, "CAUGHT_POKEMON"))
		return CAUGHT_POKEMON;

	if(compare_string(msg, "GET_POKEMON"))
		return GET_POKEMON;

	if(compare_string(msg, "LOCALIZED_POKEMON"))
		return LOCALIZED_POKEMON;

	return WRONG_PARAMETERS;

}










