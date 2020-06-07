/*
 * queues.c
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#include "queues.h"

extern t_subscribers* subscribers;

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

	message_type type = subscribe -> queue_to_subscribe;

	t_client* client = malloc(sizeof(t_client));
	client -> socket = cliente;
	client -> process_id = subscribe -> process_id;

	suscribir(client, type);

	return 0;
}

//TODO: Segundos!
uint32_t suscribirGameboy(t_buffer* msg, uint32_t cliente) {

	t_gameboy_queue_to_subscribe* subscribe = deserializarSubscribeGameboy(msg);

	t_client* client = malloc(sizeof(t_client));
	client -> socket = cliente;
	client -> process_id = 0;

	message_type type = subscribe -> queue_to_subscribe;

	suscribir(client, type);

	return 0;


}

void suscribir(t_client* client, message_type queue) {
	switch(queue){

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
			break; // Devuelve unsigned int, entonces no debería devolver -1 no?
	}
}
