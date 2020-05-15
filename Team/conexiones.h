/*
 * conexiones.h
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#ifndef CONEXIONES_H_
#define CONEXIONES_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<stdint.h>
#include<unistd.h>
#include <sys/socket.h>
#include<netdb.h>
#include<string.h>
#include <pthread.h>
#include<commons/config.h>

#include "var_globales.h"
#include "../utils/mensajes.h"


int crear_conexion(char* ip, char* puerto);
void enviar_mensaje(char* mensaje, int socket_cliente);
void* recibir_mensaje(int socket_cliente);
void liberar_conexion(int socket_cliente);

void suscribirseAlBroker(void);
void* escucharAlBroker(void*);
void enviarGetPokemon(t_pokemon* pokemon);

#endif /* CONEXIONES_H_ */
