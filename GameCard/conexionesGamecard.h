/*
 * gamecard.h
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#ifndef GAMECARD_CONEXIONESGAMECARD_H_
#define GAMECARD_CONEXIONESGAMECARD_H_

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
#include "../Utils/conexiones.h"
#include "var_globales_gamecard.h"
#include "procesamiento_mensajes.h"

typedef struct {
	int socket;
	message_type cola;
} t_escucha_socket;


void suscribirGameCardAlBroker(void);
void *escucharAlSocket(void*);
int abrirUnaConexionGameCard(void);
void suscribirAUnaCola(int conexion, message_type cola, uint32_t process_id);

void escucharAlGameboy();
void* abrirSocketParaGameboy();
void serve_client(int* socket);
void process_request(message_type, int);

void enviarACK(uint32_t id);


#endif /* GAMECARD_CONEXIONESGAMECARD_H_ */
