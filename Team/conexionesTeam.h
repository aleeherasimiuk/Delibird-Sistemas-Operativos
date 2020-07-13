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

#include "entrenadores.h"
#include "mensajesTeam.h"
#include "planificador.h"

typedef struct {
	int socket;
	message_type cola;
} t_escucha_socket;

void  suscribirseAlBroker(void);
void* escucharAlSocket(void*);
void  suscribirAUnaCola(int conexion, message_type cola);
int   abrirUnaConexion(t_config*);
void* abrirSocketParaGameboy();
void  serve_client(int*);
void  process_request(message_type, int);
uint32_t esperarID (int socket);
uint32_t procesarID(t_paquete* paquete);
void  escucharAlGameboy();
void  enviarACK(uint32_t);

void*  enviarGetPokemon(void* data);
void*  procesarLocalized(void* paquete);
void*  procesarAppeared(void* paquete);
void  enviarCatchPokemon(t_pokemon_en_mapa* pokemon_en_mapa, t_tcb* tcb);
void*  procesarCaughtPokemon(void* paquete);

#endif /* CONEXIONES_H_ */
