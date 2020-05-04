/*
 * queues.c
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#include <queues.h>

t_subscribers* iniciarSubscribers(){
	t_subscribers* subscribers = malloc(sizeof(t_subscribers));

	subscribers -> new_pokemon = list_create();
	subscribers -> get_pokemon = list_create();
	subscribers -> catch_pokemon = list_create();
	subscribers -> caught_pokemon = list_create();
	subscribers -> appeared_pokemon = list_create();
	subscribers -> localized_pokemon = list_create();

	return subscribers;

}

uint32_t suscribirCliente(t_buffer* msg, uint32_t cliente) {

	t_subscribe* subscribe = deserializarSubscribe(msg);

	module_type type = subscribe -> module;

	t_client client = malloc(sizeof(t_client));
	client -> socket = cliente;

	switch(type){

		// https://bit.ly/2KUNH6b
		case TEAM:
			list_add(subscribers -> appeared_pokemon, client);
			list_add(subscribers -> localized_pokemon, client);
			list_add(subscribers -> caught_pokemon, client);
			break;

		// https://bit.ly/3feT1Pr
		case GAME_CARD:
			list_add(subscribers -> new_pokemon, client);
			list_add(subscribers -> catch_pokemon, client);
			list_add(subscribers -> get_pokemon, client);
			break;

		default:
			return -1;
	}

}

//TODO: Segundos!
uint32_t suscribirGameboy(t_buffer* msg, uint32_t cliente) {

	t_gameboy_queue_to_suscribe* subscribe = deserializarSubscribeGameboy(msg);

	t_client client = malloc(sizeof(t_client));
	client -> socket = cliente;

	message_type type = subscribe -> queue_to_suscribe;

	switch(type){

		case NEW_POKEMON:
			list_add(subscribers -> new_pokemon, client);
			break;

		case GET_POKEMON:
			list_add(subscribers -> get_pokemon, client);
			break;

		case CATCH_POKEMON:
			list_add(subscribers -> catch_pokemon, client);
			break;

		case CAUGHT_POKEMON:
			list_add(subscribers -> caught_pokemon, client);
			break;

		case LOCALIZED_POKEMON:
			list_add(subscribers -> localized_pokemon, client);
			break;

		case APPEARED_POKEMON:
			list_add(subscribers -> appeared_pokemon, client);
			break;

		default:
			return -1; // Devuelve unsigned int, entonces no debería devolver -1 no?
	}

	return 1;


}
