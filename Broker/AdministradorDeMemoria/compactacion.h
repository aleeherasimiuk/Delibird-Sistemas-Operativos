/*
 * compactacion.h
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_COMPACTACION_H_
#define BROKER_ADMINISTRADORDEMEMORIA_COMPACTACION_H_

#include <stdlib.h>
#include <stdint.h>
#include "organizacion_de_memoria.h"
#include "particionamiento.h"
#include <stdio.h>
#include "../var_globales.h"
#include "../queues.h"

void liberarMemoriaVieja();
void compactar();
void actualizarMensaje(memory_block_t* new_block, uint32_t id);
void valoresPorDefault(memory_block_t* mem_block);
void moverValoresAdministrativos(memory_block_t* antiguo_bloque, memory_block_t* nuevo_bloque);


#endif /* BROKER_ADMINISTRADORDEMEMORIA_COMPACTACION_H_ */
