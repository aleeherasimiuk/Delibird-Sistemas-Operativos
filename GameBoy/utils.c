/*
 * utils.c
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#include "utils.h"



int enviar_mensaje(int argc, char* argv[]){
	char* proceso = argv[0];
	int conexion;
	uint32_t paquete_size;
	void* paquete = preparar_mensaje(--argc, &argv[1], &paquete_size);

	if(compare_string(proceso, "SUSCRIPTOR")){
		//TODO: Que pasa cuando es suscriptor?

		// indico tiempo de subscripción
		uint32_t tiempoDeRetardo;
		sleep(tiempoDeRetardo);

	} else {
		char* ip, *puerto;
		ip = concat_string_config(proceso, IP);
		puerto = concat_string_config(proceso, PUERTO);

		// Abro conexión con el proceso en cuestión
		conexion = crear_conexion_con_config(config, ip, puerto);

	}


	//int status = send(conexion, paquete, paquete_size, 0);
	return 0;

}

void* preparar_mensaje(int argc, char* argv[], uint32_t* paquete_size){

	char* mensaje = argv[0];
	void* serialized_paquete;

	if(compare_string(mensaje, "NEW_POKEMON")){
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
		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = convert_to_int(argv[2]);
		uint32_t posY = convert_to_int(argv[3]);
		t_catch_pokemon* _catch_pokemon = catch_pokemon(pokemon, posX, posY);

		uint32_t message_bytes;
		void* serialized_message = serializarCatchPokemon(_catch_pokemon, &message_bytes);
		serialized_paquete = crear_paquete(CATCH_POKEMON, serialized_message, message_bytes, paquete_size);

	}

	if(compare_string(mensaje, "CAUGHT_POKEMON")) {

		uint32_t id_correlativo = convert_to_int(argv[1]);
		uint32_t caught = 0;
		char* ok = argv[2];

		caught = compare_string(ok, "OK");

		t_caught_pokemon* _caught_pokemon = caught_pokemon(&caught);

		void* serialized_message = _caught_pokemon;
		serialized_paquete = crear_paquete_con_id_correlativo(CAUGHT_POKEMON, serialized_message,sizeof(serialized_message) ,id_correlativo, paquete_size);

	}

	if(compare_string(mensaje, "GET_POKEMON")){
		t_pokemon* pokemon = crearPokemon(argv[1]);
		t_get_pokemon* _get_pokemon = get_pokemon(pokemon);
		void* serialized_message = _get_pokemon;
		serialized_paquete = crear_paquete(GET_POKEMON, serialized_message, sizeof(serialized_message), paquete_size);
	}

	return serialized_paquete;

}

// compara si el mensaje recibido es igual a: BROKER, GAMECARD o TEAM.
int compare_string(char* mensaje_recv, char* mensaje) {
	return !strcmp(mensaje_recv, mensaje);
}

// retorna un string donde es la combinación del campo(IP o PUERTO) y el proceso(TEAM, BROKER o GAMECARD)
char* concat_string_config(char* proceso, char* campo) {
	char* str = (char *) malloc(1 + strlen(campo)+ strlen(proceso));
	strcpy(str, campo);
	strcat(str, proceso);

	return str;
}










