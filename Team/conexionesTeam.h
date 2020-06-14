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
#include "../Utils/conexiones.h"
#include "var_globales.h"




void  suscribirseAlBroker(void);
void* escucharAlSocket(void*);
void  enviarGetPokemon(t_pokemon* pokemon);
void suscribirAUnaCola(int conexion, message_type cola, uint32_t process_id);
int abrirUnaConexion(t_config*);
void procesarAppeared(t_paquete* paquete);
void* abrirSocketParaGameboy();
void serve_client(int*);
void process_request(message_type, int);
void escucharAlGameboy();

#endif /* CONEXIONES_H_ */
