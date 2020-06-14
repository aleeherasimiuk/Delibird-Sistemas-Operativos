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
#include"../Utils/conexiones.h"
#include"var_globales.h"


int recibir_operacion(int);
void process_request(message_type, uint32_t);
void serve_client(int* socket);


#endif /* CONEXIONES_H_ */
