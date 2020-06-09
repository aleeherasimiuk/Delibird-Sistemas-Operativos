/*
 * conexiones.h
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#ifndef UTILS_CONEXIONES_H_
#define UTILS_CONEXIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <commons/config.h>
#include <string.h>
#include <unistd.h>
#include "mensajes.h"

#define CANT_CONNECT -10


int crear_conexion(char* ip, char* puerto);
int crear_conexion_con_config(t_config* config, char* campo_ip, char* campo_puerto);
void liberar_paquete(t_paquete* paquete);



void liberar_conexion(int socket_cliente);

#endif /* UTILS_CONEXIONES_H_ */
