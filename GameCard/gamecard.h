#ifndef GAMECARD_GAMECARD_H_
#define GAMECARD_GAMECARD_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<commons/bitarray.h>
#include<readline/readline.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "conexionesGamecard.h"
#include "var_globales_gamecard.h"
#include <fcntl.h>

//#define CANT_CONNECT -10

void intentarReconexionConBroker(char*, uint32_t, t_config*);
void inicializar_gamecard();

t_log* iniciar_logger(char*);
t_config* leer_config();
t_bitarray* iniciar_bitarray(void);


#endif /* GAMECARD_GAMECARD_H_ */
