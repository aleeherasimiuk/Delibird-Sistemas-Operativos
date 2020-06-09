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

uint32_t suscribirCliente(t_buffer* msg, uint32_t cliente) {

	t_subscribe* subscribe = deserializarSubscribe(msg);

	message_type type = subscribe -> queue_to_subscribe;

	t_client* client = malloc(sizeof(t_client));
	client -> socket = malloc(sizeof(uint32_t));
	memcpy(client -> socket, &cliente, sizeof(uint32_t));
	log_debug(logger, "Hola soy un log muy extraño que siempre digo que el socket es el: %d", *(client -> socket));
	client -> process_id = malloc(sizeof(uint32_t));
	memcpy(client -> process_id, &(subscribe -> process_id), sizeof(uint32_t));

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
	log_debug(logger, "Voy a suscribir al cliente %d, a la cola %d", *(client -> socket), queue);
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
			void* element = list_get(subscribers -> appeared_pokemon, 0);
			t_client* cliente_que_guardo = (t_client*) element;
			log_debug(logger, "UN cliente se suscribió: %d", *(cliente_que_guardo -> socket));

			/*
			 * t_pokemon* pok = crearPokemon("PIKACHU");
			t_appeared_pokemon* ap_pok = appeared_pokemon(pok, 10, 10);
			int bytes;
			void* ser = serializarAppearedPokemon(ap_pok, &bytes);
			int bytes_p;
			void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, ser, bytes, 10, &bytes_p);

			send(cliente_que_guardo -> socket, a_enviar, bytes_p, 0);
			 * */
			break;

		default:
			break; // Devuelve unsigned int, entonces no debería devolver -1 no?


	}
}
