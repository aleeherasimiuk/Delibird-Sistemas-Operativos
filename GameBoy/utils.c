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
	conexion = crear_conexion_con_config(config, ip, puerto);

	if(conexion == CANT_CONNECT){
		log_debug(logger, "No pude conectar :(");
		terminar_programa(conexion, logger, config);
		exit(1);
	} else {
		log_debug(logger, "Conexión Abierta");
	}


	int status = send(conexion, paquete, paquete_size, 0);
	log_debug(logger, "Envié un mensaje con status: %d", status);

	if(compare_string(proceso, "SUSCRIPTOR"))
		escuchar_broker(conexion, (convert_to_int(argv[2])));


	terminar_programa(conexion, logger, config);
	return 0;

}

void* preparar_mensaje(char* process, int argc, char* argv[], uint32_t* paquete_size){
	char* mensaje = argv[0];
	void* serialized_paquete;

	if(compare_string(process, "SUSCRIPTOR")){
		if(!handleSuscriptor(argc, &argv[0])){
			log_debug(logger, "TEST1");
			wrong_parameters();
		}

		message_type queue = 2;

		t_subscribe* subscripcion = subscribe(queue, process_id);

		uint32_t subscripcion_size;
		void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);
		return crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, paquete_size);

	}

	if(compare_string(mensaje, "NEW_POKEMON")){
		if(!handleNewPokemon(process, argc - 1, &argv[1]))
			wrong_parameters();

		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = convert_to_int(argv[2]);
		uint32_t posY = convert_to_int(argv[3]);
		uint32_t cant = convert_to_int(argv[4]);
		t_new_pokemon* _new_pokemon = new_pokemon(pokemon, posX, posY, cant);

		uint32_t message_bytes;
		void* serialized_message = serializarNewPokemon(_new_pokemon, &message_bytes);
		serialized_paquete = crear_paquete(NEW_POKEMON, serialized_message, message_bytes, paquete_size);

	}

	if(compare_string(mensaje, "APPEARED_POKEMON")){

		if(!handleAppearedPokemon(process, argc - 1, &argv[1])){
			wrong_parameters();
		}

		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = convert_to_int(argv[2]);
		uint32_t posY = convert_to_int(argv[3]);
		t_appeared_pokemon* _appeared_pokemon = appeared_pokemon(pokemon, posX, posY);

		uint32_t message_bytes;
		void* serialized_message = serializarAppearedPokemon(_appeared_pokemon, &message_bytes);
		uint32_t id_correlativo = convert_to_int(argv[4]);
		serialized_paquete = crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_message, message_bytes, id_correlativo, paquete_size);

	}


	if(compare_string(mensaje, "CATCH_POKEMON")){
		int st = handleCatchPokemon(process, --argc, &argv[1]);
		if(st == WRONG_PARAMETERS)
			wrong_parameters();
		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = convert_to_int(argv[2]);
		uint32_t posY = convert_to_int(argv[3]);
		t_catch_pokemon* _catch_pokemon = catch_pokemon(pokemon, posX, posY);

		uint32_t message_bytes;
		void* serialized_message = serializarCatchPokemon(_catch_pokemon, &message_bytes);
		serialized_paquete = crear_paquete(CATCH_POKEMON, serialized_message, message_bytes, paquete_size);

	}

	if(compare_string(mensaje, "CAUGHT_POKEMON")) {

		int st = handleCaughtPokemon(process, --argc, &argv[1]);
		if(st == WRONG_PARAMETERS)
			wrong_parameters();

		uint32_t id_correlativo = convert_to_int(argv[1]);
		uint32_t caught = 0;
		char* ok = argv[2];

		caught = compare_string(ok, "YES");

		t_caught_pokemon* _caught_pokemon = caught_pokemon(&caught);


		uint32_t bytes;
		void* serialized_message = serializarCaughtPokemon(_caught_pokemon, &bytes);
		serialized_paquete = crear_paquete_con_id_correlativo(CAUGHT_POKEMON, serialized_message, bytes, id_correlativo, paquete_size);

		log_debug(logger, "Envié un Caught con el mensaje: %d", *((uint32_t*) serialized_message));
	}

	if(compare_string(mensaje, "GET_POKEMON")){
		int st = handleGetPokemon(process, --argc, &argv[1]);
		if(st == WRONG_PARAMETERS)
			wrong_parameters();

		t_pokemon* pokemon = crearPokemon(argv[1]);
		t_get_pokemon* _get_pokemon = get_pokemon(pokemon);
		void* serialized_message = _get_pokemon;
		serialized_paquete = crear_paquete(GET_POKEMON, serialized_message, sizeof(serialized_message), paquete_size);
	}

	return serialized_paquete;

}



void escuchar_broker(uint32_t conexion, uint32_t seconds){
	log_debug(logger, "Escuchando en el socket: %d", conexion);

	listen_t* listening_for = malloc(sizeof(listen_t));
	listening_for -> conexion = conexion;
	listening_for -> seconds = seconds;

	pthread_t thread;
	pthread_create(&thread, NULL, escucharPorTiempoLimitado, listening_for);
	pthread_detach(&thread);

	int i = 1;
	while(i) {

		t_paquete* paquete = recibirPaquete(conexion);

		if(paquete != NULL){
			enviarACK(paquete -> id);

			switch(paquete->type) {
				case ID:
					log_debug(logger, "Me llegó un ID");
					break;

				case NEW_POKEMON:
					log_debug(logger, "Spawning POKEMON");
					break;

				case APPEARED_POKEMON:
					log_debug(logger, "Wow! Apareció un Pokemon");
					break;

				case LOCALIZED_POKEMON:
					log_debug(logger, "Que Google Maps ni Google Maps!. Localized Pokemon PAPÁ");
					break;

				case CATCH_POKEMON:
					log_debug(logger, "ATRAPALO!");
					break;

				case CAUGHT_POKEMON:
					log_debug(logger, "Me llegó un CAUGHT_POKEMON");
					break;

				case GET_POKEMON:
					log_debug(logger, "Llegó un GET_POKEMON");
					break;

				default:
					log_debug(logger, "What is this SHIT?.");
					break;
			}

		} else {
			// Políticas de reconexión
			break;
		}
	}
}

// Abstraer junto con el de conexionesTeam
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
	free(a_enviar);
	close(conexion);


}

//IDEM
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










