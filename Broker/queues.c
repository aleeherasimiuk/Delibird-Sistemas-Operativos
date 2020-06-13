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
pthread_t thread_new_pokemon;
pthread_t thread_appeared_pokemon;
pthread_t thread_catch_pokemon;
pthread_t thread_caught_pokemon;
pthread_t thread_localized_pokemon;
pthread_t thread_get_pokemon;

uint32_t next_socket[9];


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

void iniciarColas(){
	pthread_create(&thread_new_pokemon,NULL,(void*)new_pokemon_queue,NULL);
	pthread_create(&thread_appeared_pokemon,NULL,(void*)queue, APPEARED_POKEMON);
	pthread_create(&thread_localized_pokemon,NULL,(void*)localized_pokemon_queue,NULL);
	pthread_create(&thread_catch_pokemon,NULL,(void*)catch_pokemon_queue,NULL);
	pthread_create(&thread_caught_pokemon,NULL,(void*)caught_pokemon_queue,NULL);
	pthread_create(&thread_get_pokemon,NULL,(void*)get_pokemon_queue,NULL);
	//Quedan hacer más threads

	pthread_detach(&thread_new_pokemon);
	pthread_detach(&thread_appeared_pokemon);
	pthread_detach(&thread_localized_pokemon);
	pthread_detach(&thread_catch_pokemon);
	pthread_detach(&thread_caught_pokemon);
	pthread_detach(&thread_get_pokemon);
}

void iniciarVectorDeSockets(){
	for(int i = 0; i < 9; i++){
		next_socket[i] = -1;
	}

}

void iniciarVectorDeSemaforos(){
	for(int i = 0; i < 9; i++){
		pthread_mutex_init(&(sem_sockets[i]), NULL);
		pthread_mutex_lock(&(sem_sockets[i]));
	}

}

void* queue(void* message_type){

	uint32_t type = (uint32_t) message_type;
	log_debug(logger, "El código de operacion es: %d", type);

	while(1){
		t_paquete* paquete = NULL;
		pthread_mutex_lock(&(sem_sockets[type]));
		if(next_socket[type] != -1)
			paquete = recibirPaqueteSi(next_socket[type], type);
		next_socket[type] = -1;
		pthread_mutex_unlock(&(sem_sockets[type]));

		if(paquete != NULL){
			send_to_subscribers(paquete);
		}
	}


	return NULL;
}

void send_to_subscribers(t_paquete* paquete){

}


void* new_pokemon_queue(){

	pthread_mutex_lock(&(sem_sockets[NEW_POKEMON]));
	log_debug(logger, "Alguien ha enviado un NEW_POKEMON");
	pthread_mutex_unlock(&(sem_sockets[NEW_POKEMON]));
	return NULL;

}
void* appeared_pokemon_queue(){

	while(1){
		t_paquete* paquete = NULL;
		pthread_mutex_lock(&(sem_sockets[APPEARED_POKEMON]));
		if(next_socket[APPEARED_POKEMON] != -1)
			paquete = recibirPaqueteSi(next_socket[APPEARED_POKEMON], APPEARED_POKEMON);
		next_socket[APPEARED_POKEMON] = -1;
		pthread_mutex_unlock(&(sem_sockets[APPEARED_POKEMON]));

		if(paquete != NULL){
			appeared_pokemon_to_subscribers(paquete);
		}
	}


	return NULL;
}

void appeared_pokemon_to_subscribers(t_paquete* paquete){
	log_debug(logger, "Alguien ha enviado un APPEARED_POKEMON");

	t_appeared_pokemon* appeared_pokemon_msg = deserializarAppearedPokemon(paquete -> buffer);
	t_list* app_subscribers = subscribers -> appeared_pokemon;

	log_debug(logger, "Apareció un: %s", appeared_pokemon_msg -> pokemon -> name);

	for(int i = 0; i < list_size(app_subscribers); i++){
		void* list_element = list_get(app_subscribers, i);
		t_client* client = deserializarCliente(list_element);
		log_debug(logger, "Intentaré enviar APPEARED_POKEMON al cliente %d", client -> socket);
		int bytes;
		void* ser = serializarAppearedPokemon(appeared_pokemon_msg, &bytes);
		int bytes_p;
		void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, ser, bytes, paquete -> correlative_id, &bytes_p);

		log_debug(logger, "Antes del send");
		/*
		 * MSG_NOSIGNAL logrará hacer que en el caso de que el socket esté cerrado porque cayó la conexión
		 * con el cliente, el broker no caiga
		 * */
		int status = send(client -> socket, a_enviar, bytes_p, MSG_NOSIGNAL);
		log_debug(logger, "Envié APPEARED_POKEMON al suscriptor %d con status: %d", client -> socket ,status);
	}
}
void* catch_pokemon_queue(){
	pthread_mutex_lock(&(sem_sockets[CATCH_POKEMON]));
	log_debug(logger, "Alguien ha enviado un CATCH_POKEMON");
	pthread_mutex_unlock(&(sem_sockets[CATCH_POKEMON]));
	return NULL;
}
void* caught_pokemon_queue(){

	pthread_mutex_lock(&(sem_sockets[CAUGHT_POKEMON]));
	t_paquete* paquete = recibirPaqueteSi(next_socket[CAUGHT_POKEMON], CAUGHT_POKEMON);
	pthread_mutex_unlock(&(sem_sockets[CAUGHT_POKEMON]));


	log_debug(logger, "Alguien ha enviado un CAUGHT_POKEMON");
	t_caught_pokemon* cau_pokemon = deserializarCaughtPokemon(paquete -> buffer);
	t_list* cau_subscribers = subscribers -> caught_pokemon;
	log_debug(logger, "Pudo el cliente atrapar a un pokemon?: %d", *((uint32_t*)(paquete -> buffer -> stream)));

	for(int i = 0; i < list_size(cau_subscribers); i++){
		void* list_element = list_get(cau_subscribers, i);
		t_client* client = deserializarCliente(list_element);
		log_debug(logger, "Intentaré enviar CAUGHT_POKEMON al cliente %d", client -> socket);
		int bytes;
		void* ser = serializarCaughtPokemon(cau_pokemon, &bytes);

		int bytes_p;
		void* a_enviar = crear_paquete_con_id_correlativo(CAUGHT_POKEMON, ser, bytes, paquete -> correlative_id, &bytes_p);

		int status = send(client -> socket, a_enviar, bytes_p, MSG_NOSIGNAL);
		log_debug(logger, "Envié CAUGHT_POKEMON al suscriptor %d con status: %d", client -> socket ,status);
	}


	return NULL;
}
void* localized_pokemon_queue(){
	pthread_mutex_lock(&(sem_sockets[LOCALIZED_POKEMON]));
	log_debug(logger, "Alguien ha enviado un LOCALIZED_POKEMON");
	pthread_mutex_unlock(&(sem_sockets[LOCALIZED_POKEMON]));
	return NULL;
}
void* get_pokemon_queue(){
	pthread_mutex_lock(&(sem_sockets[GET_POKEMON]));
	log_debug(logger, "Alguien ha enviado un GET_POKEMON");
	pthread_mutex_unlock(&(sem_sockets[GET_POKEMON]));
	return NULL;
}
