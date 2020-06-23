/*
 * particionamiento.h
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_PARTICIONAMIENTO_H_
#define BROKER_ADMINISTRADORDEMEMORIA_PARTICIONAMIENTO_H_

#include <stdlib.h>
#include <stdint.h>
#include "organizacion_de_memoria.h"

memory_block_t* first_fit(uint32_t);
memory_block_t* best_fit(uint32_t);
int puedeEntrar(memory_info_t*, uint32_t);
int mejorAjuste(memory_block_t*, memory_block_t*);
memory_block_t* particionar(memory_block_t*, uint32_t);

#endif /* BROKER_ADMINISTRADORDEMEMORIA_PARTICIONAMIENTO_H_ */
