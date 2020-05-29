/*
 * gamecard.h
 *
 *  Created on: 29 may. 2020
 *      Author: utnso
 */

#ifndef GAMEBOY_GAMEBOY_H_
#define GAMEBOY_GAMEBOY_H_

#include<stdio.h>
#include<commons/log.h>
#include<commons/config.h>
#include<commons/string.h>
#include<stdlib.h>
#include<unistd.h> // Funcion close
#include"../utils/mensajes.h"

t_log* iniciar_logger(char*);
t_config* leer_config(void);
void terminar_programa(int, t_log*, t_config*);



#endif /* GAMEBOY_GAMEBOY_H_ */
