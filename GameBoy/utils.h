/*
 * utils.h
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#ifndef GAMEBOY_UTILS_H_
#define GAMEBOY_UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include"../Utils/mensajes.h"


int enviar_mensaje(int argc, char* argv[]);
void* preparar_mensaje(int argc, char* argv[], uint32_t*);



#endif /* GAMEBOY_UTILS_H_ */
