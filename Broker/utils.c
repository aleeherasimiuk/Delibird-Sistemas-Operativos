/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"
#include"var_globales.h"

uint32_t id_siguiente = 1;

void iniciar_servidor(char* ip, char* puerto){
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

	sem_wait(&(sem_sockets[type].c));
	pthread_mutex_lock(&(sem_sockets[type].mx));

	next_socket[type].socket_to_recv = socket_cliente;
	next_socket[type].id_to_assing = id_siguiente++;

	pthread_mutex_unlock(&(sem_sockets[type].mx));
	sem_post(&(sem_sockets[type].q));

	uint32_t bytes;
	void* paquete = crear_paquete(ID, &next_socket[type].id_to_assing, sizeof(uint32_t), &bytes);
	int status = send(socket_cliente, paquete, bytes, 0);
	log_debug(logger, "Envié el ID: %d, con status: %d", next_socket[type].id_to_assing, status);


}




