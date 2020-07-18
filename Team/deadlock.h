/*
 * deadlock.h
 *
 *  Created on: 12 jul. 2020
 *      Author: utnso
 */

#ifndef DEADLOCK_H_
#define DEADLOCK_H_

#include <semaphore.h>

#include "var_globales.h"
#include "planificador.h"
#include "entrenadores.h"

void inicializarDeadlock(void);
void deteccionYCorreccionDeadlock(void);
void deteccionDeadlock(void);
int agregarEntrenadorQueTengaElQueNecesita(t_list* entrenadores_en_deadlock, t_tcb* tcb_necesitado);
void sacarDeadlocksRepetidos(t_list* lista_deadlock);
int deadlockRepetidoEn(t_list* lista_deadlock, t_list* deadlock, int index_max);
int tieneMismosTcbsPeroNoSonIguales(t_list* lista_deadlock, t_list* deadlock);


void corregirUnDeadlock(void);

#endif /* DEADLOCK_H_ */
