/*
 * utils.c
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#include "utils.h"

int enviar_mensaje(int argc, char* argv[]){
	char* proceso = argv[0];
	uint32_t paquete_size;
	void* t_paquete = preparar_mensaje(--argc, &argv[1], &paquete_size);

	//TODO: Usar Switch?
	if(!strcmp(proceso, "BROKER")){

	}

	if(!strcmp(proceso, "GAME_CARD")){

	}

	if(!strcmp(proceso, "TEAM")){

	}

	if(!strcmp(proceso, "SUSCRIPTOR")){

	}

	return 0;

}

void* preparar_mensaje(int argc, char* argv[], uint32_t* paquete_size){

	char* mensaje = argv[0];
	void* serialized_paquete;

	if(!strcmp(mensaje, "NEW_POKEMON")){
		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = atoi(argv[2]);
		uint32_t posY = atoi(argv[3]);
		uint32_t cant = atoi(argv[4]);
		t_new_pokemon* _new_pokemon = new_pokemon(pokemon, posX, posY, cant);

		uint32_t message_bytes;
		void* serialized_message = serializarNewPokemon(_new_pokemon, &message_bytes);
		serialized_paquete = crear_paquete(NEW_POKEMON, serialized_message, message_bytes, paquete_size);

	}

	if(!strcmp(mensaje, "APPEARED_POKEMON")){
		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = atoi(argv[2]);
		uint32_t posY = atoi(argv[3]);
		t_appeared_pokemon* _appeared_pokemon = appeared_pokemon(pokemon, posX, posY);

		uint32_t message_bytes;
		void* serialized_message = serializarAppearedPokemon(_appeared_pokemon, &message_bytes);
		uint32_t id_correlativo = atoi(argv[4]);
		serialized_paquete = crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_message, message_bytes, id_correlativo, paquete_size);

	}


	if(!strcmp(mensaje, "CATCH_POKEMON")){
		t_pokemon* pokemon = crearPokemon(argv[1]);
		uint32_t posX = atoi(argv[2]);
		uint32_t posY = atoi(argv[3]);
		t_catch_pokemon* _catch_pokemon = catch_pokemon(pokemon, posX, posY);

		uint32_t message_bytes;
		void* serialized_message = serializarCatchPokemon(_catch_pokemon, &message_bytes);
		serialized_paquete = crear_paquete(CATCH_POKEMON, serialized_message, message_bytes, paquete_size);

	}

	if(!strcmp(mensaje, "CAUGHT_POKEMON")) {

		uint32_t id_correlativo = atoi(argv[1]);
		uint32_t caught = 0;
		char* ok = argv[2];

		caught = !strcmp(ok, "OK");

		t_caught_pokemon* _caught_pokemon = caught_pokemon(&caught);

		void* serialized_message = _caught_pokemon;
		serialized_paquete = crear_paquete_con_id_correlativo(CAUGHT_POKEMON, serialized_message,sizeof(serialized_message) ,id_correlativo, paquete_size);

	}

	if(!strcmp(mensaje, "GET_POKEMON")){
		t_pokemon* pokemon = crearPokemon(argv[1]);
		t_get_pokemon* _get_pokemon = get_pokemon(pokemon);
		void* serialized_message = _get_pokemon;
		serialized_paquete = crear_paquete(GET_POKEMON, serialized_message, sizeof(serialized_message), paquete_size);
	}

	return serialized_paquete;

	}






