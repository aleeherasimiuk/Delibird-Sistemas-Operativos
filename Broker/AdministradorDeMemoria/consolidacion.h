/*
 * consolidacion.h
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_CONSOLIDACION_H_
#define BROKER_ADMINISTRADORDEMEMORIA_CONSOLIDACION_H_

#include "organizacion_de_memoria.h"
#include <stdlib.h>
#include "../var_globales.h"

void consolidar(memory_block_t* bloque_eliminado);
memory_block_t* merge(memory_block_t*, memory_block_t*);


#endif /* BROKER_ADMINISTRADORDEMEMORIA_CONSOLIDACION_H_ */
