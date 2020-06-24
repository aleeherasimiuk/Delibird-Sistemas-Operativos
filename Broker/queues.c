/*
 * queues.c
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#include "queues.h"
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
t_list* mensajes;


uint32_t suscribirCliente(t_buffer* msg, uint32_t cli) {

	t_subscribe* subscribe = deserializarSubscribe(msg);

	message_type type = subscribe -> queue_to_subscribe;

	t_client* client = cliente(subscribe -> process_id, cli);

	suscribir(client, type);

	free(subscribe);
	free(client);

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

	pthread_detach(thread_new_pokemon);
	pthread_detach(thread_appeared_pokemon);
	pthread_detach(thread_localized_pokemon);
	pthread_detach(thread_catch_pokemon);
	pthread_detach(thread_caught_pokemon);
	pthread_detach(thread_get_pokemon);
}

void iniciarMensajes(){

	mensajes = list_create();

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


		if(paquete != NULL){
			send_to_subscribers(paquete);
			guardar(paquete);

		}

	}


	return NULL;
}


void send_to_subscribers(t_paquete* paquete){

	message_type type = paquete -> type;
	t_list* list_to_send = subscribers[type];
	listar_mensaje(paquete);

	for(int i = 0; i < list_size(list_to_send); i++){
		void* list_element = list_get(list_to_send, i);
		t_client* client = deserializarCliente(list_element);
		log_debug(logger, "Intentaré enviar el mensaje al cliente %d", client -> socket);

		if(fueEnviado(paquete, client))
			continue;

		int bytes;
		int bytes_p;
		//TODO: ID Correlativo
		void* a_enviar = crear_paquete_con_id(type, paquete -> buffer -> stream, paquete -> buffer -> stream_size, paquete -> id, &bytes_p);

		/*
		 * MSG_NOSIGNAL logrará hacer que en el caso de que el socket esté cerrado porque cayó la conexión
		 * con el cliente, el broker no caiga
		 * */
		int status = send(client -> socket, a_enviar, bytes_p, MSG_NOSIGNAL);
		log_debug(logger, "Envié el mensaje al suscriptor %d con status: %d", client -> socket ,status);

		free(client);
		free(a_enviar);

		if(status == -1)
			list_remove(list_to_send, i);
	}
}

void listar_mensaje(t_paquete* paquete){

	clientes_por_mensaje_t* cxm = malloc(sizeof(clientes_por_mensaje_t));
	cxm -> id_mensaje = paquete -> id;
	cxm -> id_correlativo = paquete -> correlative_id;
	cxm -> suscriptores = list_create();

	list_add(mensajes, cxm);

}

void asignar_id(t_paquete* paquete, uint32_t id){
	paquete -> id = id;
}

int fueEnviado(t_paquete* paquete, t_client* client){

	uint32_t id_mensaje = paquete -> id;

	clientes_por_mensaje_t* msg = obtenerMensaje(id_mensaje);

	if(msg == NULL)
		log_error(logger, "FATAL ERROR: Message not listed");

	status_mensaje_t* status_msg = obtenerStatus(msg -> suscriptores, client -> process_id);

	if(status_msg == NULL)
		status_msg = agregarCliente(msg, client);


	return status_msg -> ack;
}

clientes_por_mensaje_t* agregarMensaje(t_paquete* paquete){

	clientes_por_mensaje_t* cxm = malloc(sizeof(clientes_por_mensaje_t));
	cxm -> id_mensaje = paquete -> id;
	cxm -> id_correlativo = paquete -> correlative_id;
	cxm -> suscriptores = list_create();

	list_add(mensajes, cxm);
	return cxm;

}

status_mensaje_t* agregarCliente(clientes_por_mensaje_t* cxm, t_client* client){

	status_mensaje_t* st = malloc(sizeof(status_mensaje_t));
	st -> process_id = client -> process_id;
	st -> ack = 0;

	list_add(cxm -> suscriptores, st);
	return st;

}

clientes_por_mensaje_t* obtenerMensaje(int id_mensaje){

	for(int i = 0; i < list_size(mensajes); i++){

		clientes_por_mensaje_t* msg = list_get(mensajes, i);

		if(msg -> id_mensaje == id_mensaje){
			return msg;
		}

	}
	return NULL;

}

status_mensaje_t* obtenerStatus(t_list* suscriptores, int pid){

	for(int i = 0; i < list_size(suscriptores); i++){
		status_mensaje_t* st = list_get(suscriptores, i);
		if(st -> process_id == pid)
			return st;
	}

	return NULL;

}

void procesarACK(t_buffer* buffer){

	t_ack* ack = deserializarACK(buffer);
	log_debug(logger, "El proceso %d, recibió el mensaje cuyo ID es: %d", ack -> process_id, ack -> id);
	clientes_por_mensaje_t* cxm = obtenerMensaje(ack -> id);

	if(cxm == NULL){
		//TODO
		free(ack);
		return;
	}

	status_mensaje_t* st = obtenerStatus(cxm-> suscriptores, ack -> process_id);
	st -> ack = 1;
	free(ack);
}

void guardar(t_paquete* paquete){

	pthread_mutex_lock(&mx_mem);
	queue_push(datos_para_guardar, paquete);
	pthread_mutex_unlock(&mx_mem);
	sem_post(&sem_msg_data);

}







