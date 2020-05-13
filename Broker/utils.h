/*
 * conexiones.h
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<pthread.h>
#include"queues.h"

#include"../utils/mensajes.h"

pthread_t thread;

void* recibir_buffer(int*, int);

void iniciar_servidor(char*, char*);
void esperar_cliente(int);
t_buffer* recibir_mensaje(int socket_cliente, uint32_t* size);
int recibir_operacion(int);
void process_request(int cod_op, int cliente_fd);
void serve_client(int* socket);
void* serializar_paquete(t_paquete* paquete, int bytes);
void devolver_mensaje(void* payload, int size, int socket_cliente);


#endif /* CONEXIONES_H_ */
