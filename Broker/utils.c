/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"
#include"var_globales.h"

int server_socket;

void iniciar_servidor(char* ip, char* puerto){
	pthread_mutex_init(&id_mx, NULL);
	crear_servidor_cuando_se_pueda(ip, puerto, serve_client, logger_extra);
}

void serve_client(int* socket) {

	message_type type = recibirCodigoDeOperacion(*socket);
	if(type != -1){
		log_info(logger, "Se ha conectado un proceso"); //TODO: Aclarar cual?
		log_debug(logger, "Procesando solicitud");
		process_request(type, *socket);
		free(socket);
	}else {
		log_debug(logger, "No puedo procesar la solicitud");
	}
}

void process_request(message_type type, uint32_t socket_cliente){

	log_debug(logger, "Procesando código de operacion: %d", type);
	log_debug(logger, "Recibiendo del socket: %d", socket_cliente);

	if(type < 0){
		log_error(logger, "Error al obtener el código de operacion");
		return;
	}

	if(type == SUBSCRIBE){
		t_paquete* paquete = recibirPaqueteSi(socket_cliente, type);
		suscribirCliente(paquete -> buffer, socket_cliente);
		suscripcionOk(socket_cliente);
		free(paquete -> buffer -> stream);
		free(paquete -> buffer);
		free(paquete);
		return;
	}

	if(type == ACK){
		t_paquete* paquete = recibirPaqueteSi(socket_cliente, type);
		procesarACK(paquete -> buffer);
		//free(paquete -> buffer -> stream);
		//free(paquete -> buffer);
		free(paquete);
		close(socket_cliente);
		return;
	}

	if(type < NEW_POKEMON || type > LOCALIZED_POKEMON){
		log_error(logger_extra, "Cierro la conexión por ser un proceso desconocido.");
		close(socket_cliente);
		return;
	}

	//uint32_t id_message_to_module;

	sem_wait(&(sem_sockets[type].c));
	pthread_mutex_lock(&(sem_sockets[type].mx));

	next_socket[type].socket_to_recv = socket_cliente;

	pthread_mutex_unlock(&(sem_sockets[type].mx));
	sem_post(&(sem_sockets[type].q));


}




