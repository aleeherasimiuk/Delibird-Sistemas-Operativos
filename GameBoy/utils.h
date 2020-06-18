/*
 * utils.h
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#ifndef GAMEBOY_UTILS_H_
#define GAMEBOY_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include "../Utils/conexiones.h"
#include "var_globales_gameboy.h"
#include "args_handler.h"
#include <pthread.h>

#define convert_to_int atoi
#define concat_string strcat

typedef struct {
	uint32_t seconds;
	uint32_t conexion;
} listen_t;


int enviar_mensaje(int argc, char* argv[]);
void* preparar_mensaje(char* proceso, int argc, char* argv[], uint32_t*);
void wrong_parameters();
void* escucharPorTiempoLimitado(void*);
void enviarACK(uint32_t);
void escuchar_broker(uint32_t, uint32_t);



#endif /* GAMEBOY_UTILS_H_ */
