/*
 * buddy_system.h
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_BUDDY_SYSTEM_H_
#define BROKER_ADMINISTRADORDEMEMORIA_BUDDY_SYSTEM_H_

#include "organizacion_de_memoria.h"
#include <stdint.h>

memory_block_t* buddy_system(memory_block_t*, uint32_t);

#endif /* BROKER_ADMINISTRADORDEMEMORIA_BUDDY_SYSTEM_H_ */
