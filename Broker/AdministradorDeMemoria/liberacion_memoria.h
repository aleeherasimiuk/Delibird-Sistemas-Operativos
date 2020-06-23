/*
 * liberacion_memoria.h
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_LIBERACION_MEMORIA_H_
#define BROKER_ADMINISTRADORDEMEMORIA_LIBERACION_MEMORIA_H_

#include <stdlib.h>
#include "organizacion_de_memoria.h"
#include <stdint.h>
#include <stdio.h>

void librerarUnBloque();
memory_block_t* bloqueAEliminar();
int eliminable(memory_block_t*, memory_block_t*);

#endif /* BROKER_ADMINISTRADORDEMEMORIA_LIBERACION_MEMORIA_H_ */
