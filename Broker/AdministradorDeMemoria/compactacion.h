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

void liberarMemoriaVieja();
void compactar();


#endif /* BROKER_ADMINISTRADORDEMEMORIA_COMPACTACION_H_ */
