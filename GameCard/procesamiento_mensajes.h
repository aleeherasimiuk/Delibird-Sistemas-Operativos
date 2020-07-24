/*
 * procesamiento_mensajes.h
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#ifndef GAMECARD_PROCESAMIENTO_MENSAJES_H_
#define GAMECARD_PROCESAMIENTO_MENSAJES_H_

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
#include "gestion_de_archivos.h"

void procesarID(t_paquete*);
void procesarNew(t_paquete*);
void procesarCatch(t_paquete*);
void procesarGet(t_paquete*);

void liberar_coords_con_cantidad(t_coords_con_cant*);

#endif /* GAMECARD_PROCESAMIENTO_MENSAJES_H_ */
