#ifndef GAMECARD_GAMECARD_H_
#define GAMECARD_GAMECARD_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "conexionesGamecard.h"
#include "var_globales_gamecard.h"

//#define CANT_CONNECT -10

void siNoConectaConBroker(char*, uint32_t, t_config*);
void inicializar_gamecard();

t_log* iniciar_logger(char*);
t_config* leer_config();


#endif /* GAMECARD_GAMECARD_H_ */
