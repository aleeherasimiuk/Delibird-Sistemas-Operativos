/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"
#include"var_globales.h"

uint32_t id_siguiente = 1;

pthread_mutex_t id_mx;

void iniciar_servidor(char* ip, char* puerto){
	pthread_mutex_init(&id_mx, NULL);
	crear_servidor(ip, puerto, serve_client);
}

void serve_client(int* socket) {

	message_type type = recibirCodigoDeOperacion(*socket);
	if(type != NULL){
		log_debug(logger, "Procesando solicitud");
		process_request(type, *socket);
	}else {
		log_debug(logger, "No puedo procesar la solicitud");
	}
}

void process_request(message_type type, uint32_t socket_cliente){

	log_debug(logger, "Procesando código de operacion: %d", type);

	if(type == SUBSCRIBE){
		t_paquete* paquete = recibirPaqueteSi(socket_cliente, type);
		suscribirCliente(paquete -> buffer, socket_cliente);
		free(paquete -> buffer);
		return;
	}

	if(type == ACK){
		t_paquete* paquete = recibirPaqueteSi(socket_cliente, type);
		uint32_t id_ack;
		//procesarACK(); TODO: Implementar process_id para identificar al proceso
		memcpy(&id_ack, paquete -> buffer -> stream, paquete -> buffer -> stream_size);
		log_debug(logger, "El cliente %d recibió el paquete con el id: %d", socket_cliente, id_ack);
		return;
	}

	uint32_t id_message_to_module;

	sem_wait(&(sem_sockets[type].c));
	pthread_mutex_lock(&(sem_sockets[type].mx));

	next_socket[type].socket_to_recv = socket_cliente;

	pthread_mutex_lock(&id_mx);
	next_socket[type].id_to_assing = id_siguiente++;
	id_message_to_module = id_siguiente++;
	pthread_mutex_unlock(&id_mx);

	pthread_mutex_unlock(&(sem_sockets[type].mx));
	sem_post(&(sem_sockets[type].q));

	uint32_t bytes;
	void* paquete = crear_paquete_con_id(ID, &next_socket[type].id_to_assing, id_message_to_module, sizeof(uint32_t), &bytes);
	int status = send(socket_cliente, paquete, bytes, 0);
	log_debug(logger, "Envié el ID: %d, con status: %d", next_socket[type].id_to_assing, status);


}




