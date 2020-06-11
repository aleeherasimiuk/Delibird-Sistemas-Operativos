/*
 * queues.c
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#include "queues.h"
#include "var_globales.h"
t_subscribers* subscribers = NULL;
t_list* suscriptores_app;


void iniciarSubscribers(){
	subscribers = malloc(sizeof(t_subscribers));

	subscribers -> new_pokemon = list_create();
	subscribers -> get_pokemon = list_create();
	subscribers -> catch_pokemon = list_create();
	subscribers -> caught_pokemon = list_create();
	subscribers -> appeared_pokemon = list_create();
	subscribers -> localized_pokemon = list_create();

	//return subscribers;

}

uint32_t suscribirCliente(t_buffer* msg, uint32_t cli) {

	t_subscribe* subscribe = deserializarSubscribe(msg);

	message_type type = subscribe -> queue_to_subscribe;

//	t_client* client = malloc(sizeof(t_client));
//	client -> socket = malloc(sizeof(uint32_t));
//	memcpy(client -> socket, &cliente, sizeof(uint32_t));
//	client -> process_id = malloc(sizeof(uint32_t));
//	memcpy(client -> process_id, &(subscribe -> process_id), sizeof(uint32_t));

	t_client* client = cliente(subscribe -> process_id, cli);

	suscribir(client, type);

	return 0;
}

//TODO: Segundos!
uint32_t suscribirGameboy(t_buffer* msg, uint32_t cli) {

	t_gameboy_queue_to_subscribe* subscribe = deserializarSubscribeGameboy(msg);

	t_client* client = cliente(0, cli);

	message_type type = subscribe -> queue_to_subscribe;

	suscribir(client, type);

	return 0;


}

void suscribir(t_client* client, message_type queue) {
	log_debug(logger, "Voy a suscribir al cliente %d, a la cola %d", client -> socket, queue);
	void* cliente_a_guardar = serializarCliente(client);
	switch(queue){

		case NEW_POKEMON:
			list_add(subscribers -> new_pokemon, cliente_a_guardar);
			break;

		case GET_POKEMON:
			list_add(subscribers -> get_pokemon, cliente_a_guardar);
			break;

		case CATCH_POKEMON:
			list_add(subscribers -> catch_pokemon, cliente_a_guardar);
			break;

		case CAUGHT_POKEMON:
			list_add(subscribers -> caught_pokemon, cliente_a_guardar);
			break;

		case LOCALIZED_POKEMON:
			list_add(subscribers -> localized_pokemon, cliente_a_guardar);
			break;

		case APPEARED_POKEMON:
			list_add(subscribers -> appeared_pokemon, cliente_a_guardar);
			break;

		default:
			break; // Devuelve unsigned int, entonces no debería devolver -1 no?


	}
}
