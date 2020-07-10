/*
 * dump_cache.h
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_DUMP_CACHE_H_
#define BROKER_ADMINISTRADORDEMEMORIA_DUMP_CACHE_H_

#include <commons/txt.h>
#include <stdio.h>
#include <time.h>

#include "../var_globales.h"
#include "organizacion_de_memoria.h"
#include "../queues.h"
#include "../../Utils/mensajes.h"

void dump_cache(int signal);
char* obtener_hora();
char* obtener_status(memory_block_t* mem_block);
char* guiones(int);

#endif /* BROKER_ADMINISTRADORDEMEMORIA_DUMP_CACHE_H_ */
