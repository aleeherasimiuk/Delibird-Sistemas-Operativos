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
#include "var_globales.h"

#define convert_to_int atoi
#define concat_string strcat
#define IP "IP_"
#define PUERTO "PUERTO_"


int enviar_mensaje(int argc, char* argv[]);
void* preparar_mensaje(int argc, char* argv[], uint32_t*);
int compare_string(char*, char*);
char* concat_string_config(char*, char*);



#endif /* GAMEBOY_UTILS_H_ */
