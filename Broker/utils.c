/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"
#include"var_globales.h"


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
	next_socket[type] = socket_cliente;
	pthread_mutex_unlock(&(sem_sockets[type].mx));
	sem_post(&(sem_sockets[type].q));

}




