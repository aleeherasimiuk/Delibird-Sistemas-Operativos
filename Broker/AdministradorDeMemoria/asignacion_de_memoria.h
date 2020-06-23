/*
 * asignacion_de_memoria.h
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_ASIGNACION_DE_MEMORIA_H_
#define BROKER_ADMINISTRADORDEMEMORIA_ASIGNACION_DE_MEMORIA_H_

#include "administracion_de_memoria.h"
#include "organizacion_de_memoria.h"
#include "particionamiento.h"
#include "../../Utils/mensajes.h"

t_queue* datos_para_guardar;
void* guardarEnMemoria();
void* asignarUnaParticion(uint32_t);
uint32_t max(uint32_t, uint32_t);
void iniciarCola();


#endif /* BROKER_ADMINISTRADORDEMEMORIA_ASIGNACION_DE_MEMORIA_H_ */
