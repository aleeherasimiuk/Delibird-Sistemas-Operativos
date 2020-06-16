/*
 * queues.c
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#include "queues.h"
#include "var_globales.h"
t_list* suscriptores_app;
pthread_t thread_new_pokemon;
pthread_t thread_appeared_pokemon;
pthread_t thread_catch_pokemon;
pthread_t thread_caught_pokemon;
pthread_t thread_localized_pokemon;
pthread_t thread_get_pokemon;

next_socket_t next_socket[9];
queue_sem_t sem_sockets[9];
t_list* subscribers[7];


uint32_t suscribirCliente(t_buffer* msg, uint32_t cli) {

	t_subscribe* subscribe = deserializarSubscribe(msg);

	message_type type = subscribe -> queue_to_subscribe;

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
	list_add(subscribers[queue], cliente_a_guardar);
}

void iniciarColas(){
	pthread_create(&thread_new_pokemon,NULL,(void*)queue, NEW_POKEMON);
	pthread_create(&thread_appeared_pokemon,NULL,(void*)queue, APPEARED_POKEMON);
	pthread_create(&thread_localized_pokemon,NULL,(void*)queue, LOCALIZED_POKEMON);
	pthread_create(&thread_catch_pokemon,NULL,(void*)queue, CATCH_POKEMON);
	pthread_create(&thread_caught_pokemon,NULL,(void*)queue, CAUGHT_POKEMON);
	pthread_create(&thread_get_pokemon,NULL,(void*)queue, GET_POKEMON);

	pthread_detach(&thread_new_pokemon);
	pthread_detach(&thread_appeared_pokemon);
	pthread_detach(&thread_localized_pokemon);
	pthread_detach(&thread_catch_pokemon);
	pthread_detach(&thread_caught_pokemon);
	pthread_detach(&thread_get_pokemon);
}

void iniciarSubscribers(){
	for(int i = 1; i < 7; i++)
		subscribers[i] = list_create();
}

//TODO: BORRAR
void iniciarVectorDeSockets(){
	for(int i = 0; i < 9; i++)
		next_socket[i].socket_to_recv = -1;
}

void iniciarVectorDeSemaforos(){
	for(int i = 0; i < 9; i++){

		pthread_mutex_init(&(sem_sockets[i].mx), NULL);
		sem_init(&(sem_sockets[i].c), 0, 1);
		sem_init(&(sem_sockets[i].q), 0, 0);
	}

}

void* queue(void* message_type){

	uint32_t type = (uint32_t) message_type;

	while(1){
		t_paquete* paquete = NULL;
		sem_wait(&(sem_sockets[type].q));
		pthread_mutex_lock(&(sem_sockets[type].mx));

		paquete = recibirPaqueteSi(next_socket[type].socket_to_recv, type);
		asignar_id(paquete, next_socket[type].id_to_assing);

		pthread_mutex_unlock(&(sem_sockets[type].mx));
		sem_post(&(sem_sockets[type].c));

		log_debug(logger, "Se asignó el ID: %d", paquete -> id);


		if(paquete != NULL)
			send_to_subscribers(paquete);

	}


	return NULL;
}

void send_to_subscribers(t_paquete* paquete){

	message_type type = paquete -> type;
	t_list* list_to_send = subscribers[type];

	for(int i = 0; i < list_size(list_to_send); i++){
		void* list_element = list_get(list_to_send, i);
		t_client* client = deserializarCliente(list_element);
		log_debug(logger, "Intentaré enviar el mensaje al cliente %d", client -> socket);
		int bytes;
		int bytes_p;
		void* a_enviar = crear_paquete_con_id_correlativo(type, paquete -> buffer -> stream, paquete -> buffer -> stream_size, paquete -> correlative_id, &bytes_p);

		/*
		 * MSG_NOSIGNAL logrará hacer que en el caso de que el socket esté cerrado porque cayó la conexión
		 * con el cliente, el broker no caiga
		 * */
		int status = send(client -> socket, a_enviar, bytes_p, MSG_NOSIGNAL);
		log_debug(logger, "Envié el mensaje al suscriptor %d con status: %d", client -> socket ,status);
		//NOTA DE MOU TODO: free()
	}
}

void asignar_id(t_paquete* paquete, uint32_t id){
	paquete -> id = id;
}
