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



void  suscribirseAlBroker(void);
void* escucharAlSocket(void*);
void  suscribirAUnaCola(int conexion, message_type cola, uint32_t process_id);
int   abrirUnaConexion(t_config*);
void* abrirSocketParaGameboy();
void  serve_client(int*);
void  process_request(message_type, int);
uint32_t esperarID (int socket);
uint32_t procesarID(t_paquete* paquete);
void  escucharAlGameboy();
void  enviarACK(uint32_t);

void  enviarGetPokemon(t_pokemon* pokemon);
void  procesarAppeared(t_paquete* paquete);
void  procesarAppeared(t_paquete* paquete);
uint32_t  enviarCatchPokemon(t_pokemon_en_mapa* pokemon_en_mapa);
void  procesarCaughtPokemon(t_paquete* paquete);

#endif /* CONEXIONES_H_ */
