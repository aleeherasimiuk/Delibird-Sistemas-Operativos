/*
 * queues.c
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#include "queues.h"
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
pthread_mutex_t msg_mx;
pthread_mutex_t sub_mx;


uint32_t suscribirCliente(t_buffer* msg, uint32_t cli) {

	t_subscribe* subscribe = deserializarSubscribe(msg);

	message_type type = subscribe -> queue_to_subscribe;

	t_client* client = cliente(subscribe -> process_id, cli);

	suscribir(client, type);

	enviarMensajesCacheados(client, type);

	free(subscribe);
	free(client);

	return 0;
}

void suscribir(t_client* client, message_type queue) {
	log_debug(logger, "Voy a suscribir al cliente %d, a la cola %d", client -> socket, queue);
	void* cliente_a_guardar = serializarCliente(client);
	pthread_mutex_lock(&sub_mx);
	list_add(subscribers[queue], cliente_a_guardar);
	pthread_mutex_unlock(&sub_mx);
}

void iniciarColas(){
	pthread_create(&thread_new_pokemon,NULL,(void*)queue, NEW_POKEMON);
	pthread_create(&thread_appeared_pokemon,NULL,(void*)queue, APPEARED_POKEMON);
	pthread_create(&thread_localized_pokemon,NULL,(void*)queue, LOCALIZED_POKEMON);
	pthread_create(&thread_catch_pokemon,NULL,(void*)queue, CATCH_POKEMON);
	pthread_create(&thread_caught_pokemon,NULL,(void*)queue, CAUGHT_POKEMON);
	pthread_create(&thread_get_pokemon,NULL,(void*)queue, GET_POKEMON);

	pthread_setname_np(&thread_new_pokemon, "TH - NEW POKEMON");
	pthread_setname_np(&thread_appeared_pokemon, "TH - APPEARED POKEMON");
	pthread_setname_np(&thread_localized_pokemon, "TH - LOCALIZED POKEMON");
	pthread_setname_np(&thread_catch_pokemon, "TH - CATCH POKEMON");
	pthread_setname_np(&thread_caught_pokemon, "TH - CAUGHT POKEMON");
	pthread_setname_np(&thread_get_pokemon, "TH - GET POKEMON");

	pthread_detach(thread_new_pokemon);
	pthread_detach(thread_appeared_pokemon);
	pthread_detach(thread_localized_pokemon);
	pthread_detach(thread_catch_pokemon);
	pthread_detach(thread_caught_pokemon);
	pthread_detach(thread_get_pokemon);
}

void iniciarMensajes(){
	pthread_mutex_init(&msg_mx, NULL);
	mensajes = list_create();

}

void iniciarSubscribers(){
	pthread_mutex_init(&sub_mx, NULL);
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

	/*
	 * Funcionamiento básico de la cola:
	 *
	 * Esta función se ejecuta en 6 hilos. Uno por cada tipo de mensaje
	 * El hilo queda bloqueado hasta que el servidor deposite un socket en el vector y habilite el semáforo
	 * Una vez habilitado para continuar la ejecución bloquea el vector con un mutex para evitar inconsistencia
	 * Se recibe el resto del paquete (Todo sin contar el Código de Operación)
	 * Se cierra el socket del mensaje.
	 * Se asigna un ID al mensaje que llegó
	 * Se desbloquea el vector de sockets
	 * Y se da la señal al servidor para que pueda depositar un nuevo socket.
	 * Si el paquete efectivamente se recibió se envía a todos los suscriptores y se guarda en la caché
	 *
	 *
	 * */

	uint32_t type = (uint32_t) message_type;

	while(1){
		t_paquete* paquete = NULL;
		sem_wait(&(sem_sockets[type].q));
		pthread_mutex_lock(&(sem_sockets[type].mx));

		paquete = recibirPaqueteSi(next_socket[type].socket_to_recv, type);
		close(next_socket[type].socket_to_recv);
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

	/*
	 * Funcionamiento básico del envío de mensajes a los suscriptores activos.
	 *
	 * Primero obtengo la lista de suscriptores del vector de listas.
	 * Cada posición del vector es una lista para cada cola de mensajes. New Pokemon (1) tiene su lista en subscribers[1]
	 * Luego de acceder de manera exclusiva al vector de listas, se pasa a listar el mensaje en la estructura administrativa.
	 *
	 * Por cada suscriptor de la lista de suscriptores se envía el mensaje
	 * Si no se puede enviar (Status = -1) Se elimina el suscriptor de la lista de suscriptores activos
	 *
	 * */

	message_type type = paquete -> type;
	pthread_mutex_lock(&sub_mx);
	t_list* list_to_send = subscribers[type];
	pthread_mutex_unlock(&sub_mx);
	listar_mensaje(paquete);

	for(int i = 0; i < list_size(list_to_send); i++){
		pthread_mutex_lock(&sub_mx);
		void* list_element = list_get(list_to_send, i);
		pthread_mutex_unlock(&sub_mx);
		t_client* client = deserializarCliente(list_element);
		log_debug(logger, "Intentaré enviar el mensaje al cliente %d", client -> socket);

		/*TODO: No es necesario?*/
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
	cxm -> cola = paquete -> type;

	pthread_mutex_lock(&msg_mx);
	list_add(mensajes, cxm);
	pthread_mutex_unlock(&msg_mx);
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
	cxm -> cola = paquete -> type;

	list_add(mensajes, cxm);
	return cxm;

}

status_mensaje_t* agregarCliente(clientes_por_mensaje_t* cxm, t_client* client){

	status_mensaje_t* st = malloc(sizeof(status_mensaje_t));
	st -> process_id = client -> process_id;
	st -> ack = 0;

	pthread_mutex_lock(&sub_mx);
	list_add(cxm -> suscriptores, st);
	pthread_mutex_unlock(&sub_mx);
	return st;

}

clientes_por_mensaje_t* obtenerMensaje(int id_mensaje){

	int i = 0;
	return obtenerMensajeYPosicion(id_mensaje, &i);

}

clientes_por_mensaje_t* obtenerMensajeYPosicion(int id_mensaje, int* posicion){

	pthread_mutex_lock(&msg_mx);
	int size = list_size(mensajes);
	pthread_mutex_unlock(&msg_mx);

	for(int i = 0; i < size; i++){

		pthread_mutex_lock(&msg_mx);
		clientes_por_mensaje_t* msg = list_get(mensajes, i);
		pthread_mutex_unlock(&msg_mx);

		if(msg -> id_mensaje == id_mensaje){
			*posicion = i;
			return msg;
		}

	}
	return NULL;

}

status_mensaje_t* obtenerStatus(t_list* suscriptores, int pid){

	pthread_mutex_lock(&sub_mx);
	int size = list_size(suscriptores);
	pthread_mutex_unlock(&sub_mx);

	for(int i = 0; i < size; i++){
		pthread_mutex_lock(&sub_mx);
		status_mensaje_t* st = list_get(suscriptores, i);
		pthread_mutex_unlock(&sub_mx);
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
	if(st != NULL)
		st -> ack = 1;
	else
		log_debug(logger, "WTF");
	free(ack);
}

void guardar(t_paquete* paquete){

	pthread_mutex_lock(&mx_mem);
	queue_push(datos_para_guardar, paquete);
	pthread_mutex_unlock(&mx_mem);
	sem_post(&sem_msg_data);

}

void enviarMensajesCacheados(t_client* client, message_type cola){

	/*
	 * Para enviar los mensajes cacheados en la memoria interna del broker:
	 *
	 * Por cada mensaje perteneciente a la cola, se obtiene el status para el cliente.
	 * Si el mensaje contiene el ACK en 1 implica que ese mensaje fue enviado y no debe reenviarse
	 * Caso contrario se extraen los datos de la caché y se envían.
	 *
	 *
	 * */

	int messages_count = list_size(mensajes);

	for(int i = 0; i < messages_count; i++){
		clientes_por_mensaje_t* cxm = list_get(mensajes, i);
		if(cxm != NULL && cxm -> cola == cola){
			t_list* subscribers = cxm -> suscriptores;
			status_mensaje_t* st = obtenerStatus(subscribers, client -> process_id);

			int ok = -1;

			if(st != NULL) 							// El cliente ya estuvo
				if(!st -> ack) 						// El cliente no lo recibió
					ok = enviarCacheado(client, cxm);
				else 								// Ya lo recibió
					continue;
			else{ // El cliente nunca estuvo
				agregarCliente(cxm, client);
				ok = enviarCacheado(client, cxm);
			}

			if(!ok)
				list_remove(mensajes, i);

		}
	}

}

int enviarCacheado(t_client* client, clientes_por_mensaje_t* cxm){

	memory_block_t* mem_block = cxm -> memory_block;

	if(mem_block != NULL){

		if(reemplazo == LRU)
			actualizarFlag(cxm);

		int cola = cxm -> cola;
		int size = mem_block -> data -> size;
		int frag = mem_block -> data -> fragmentacion;
		int tamano_efectivo = size - frag;
		void* stream = malloc(size);
		log_debug(logger, "Con ampersand %p, sin ampersand %p", &(mem_block -> data -> base), mem_block -> data -> base);
		pthread_mutex_lock(&mx_mem);
		memcpy(stream, (mem_block -> data -> base), tamano_efectivo);
		pthread_mutex_unlock(&mx_mem);
		int id = cxm -> id_mensaje;
		int id_c = cxm -> id_correlativo;

		log_debug(logger, "ID: %d, ID_CORRELATIVO: %d, STREAM SIZE: %d, FRAGMENTACION: %d", id, id_c, size, frag);

		int bytes;
		void* a_enviar = crear_paquete_con_ids(cola, stream, size, id, id_c, &bytes);

		int status = send(client -> socket, a_enviar, bytes, MSG_NOSIGNAL);
		log_debug(logger, "Envié un mensaje cacheado con status: %d", status);
		free(stream);
		free(a_enviar);

		return 1;

	} else { // El mensaje fue eliminado
		return 0;

	}
}

//void destruir_colas(){
//
//	pthread_kill(thread_new_pokemon,0);
//	pthread_kill(thread_appeared_pokemon,0);
//	pthread_kill(thread_catch_pokemon,0);
//	pthread_kill(thread_caught_pokemon,0);
//	pthread_kill(thread_get_pokemon,0);
//	pthread_kill(thread_localized_pokemon,0);
//
//	list_destroy_and_destroy_elements(mensajes, free);
//	for(int i = 0; i < 7; i++){
//		list_destroy_and_destroy_elements(subscribers[i], free);
//	}
//
//	for(int i = 0; i < 9; i++){
//		sem_destroy(&sem_sockets[i].c);
//		sem_destroy(&sem_sockets[i].q);
//		pthread_mutex_destroy(&sem_sockets[i].mx);
//	}
//
//
//}

void destruir_mensajes(){

	pthread_mutex_lock(&msg_mx);

	for(int i = 0; i < list_size(mensajes); i++){
		clientes_por_mensaje_t* cxm = list_get(mensajes, i);
		list_destroy_and_destroy_elements(cxm -> suscriptores, free);
	}

	list_destroy_and_destroy_elements(mensajes, free);


}







