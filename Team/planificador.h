/*
 * planificador.h
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#ifndef PLANIFICADOR_H_
#define PLANIFICADOR_H_

#include <pthread.h>
#include<commons/string.h>
#include<commons/collections/list.h>

#include "entrenadores.h"
#include "var_globales.h"



void cargarEntrenadores(void);
void crearHilos(void);

#endif /* PLANIFICADOR_H_ */
