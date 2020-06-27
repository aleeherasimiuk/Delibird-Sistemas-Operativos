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
#include "compactacion.h"
#include "../../Utils/mensajes.h"
#include "liberacion_memoria.h"
#include "../queues.h"
#include "commons/memory.h"

t_queue* datos_para_guardar;
void* guardarEnMemoria();
memory_block_t* asignarUnaParticion(uint32_t);
uint32_t max(uint32_t, uint32_t);
void iniciarCola();
void copiarDatos(memory_block_t*, t_paquete*);
void liberarPaquete(t_paquete*);
void relacionarBloqueConMensaje(memory_block_t*, t_paquete*);
//void actualizarFlag(clientes_por_mensaje_t*);
void* acomodarMemoria(uint32_t);
void estadoDeLaMemoria();


#endif /* BROKER_ADMINISTRADORDEMEMORIA_ASIGNACION_DE_MEMORIA_H_ */
