/*
 * queues.h
 *
 *  Created on: 3 may. 2020
 *      Author: utnso
 */

#ifndef BROKER_QUEUES_H_
#define BROKER_QUEUES_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include"var_globales.h"
#include<commons/collections/list.h>

#include "queue_thread_vars.h"
#include"AdministradorDeMemoria/asignacion_de_memoria.h"
#include "../Utils/mensajes.h"

// Cliente movido a mensajes.h


uint32_t suscribirCliente(t_buffer* msg, uint32_t size);
void suscribir(t_client* client, message_type queue);

void iniciarColas();
void* new_pokemon_queue();
void* appeared_pokemon_queue();
void* catch_pokemon_queue();
void* caught_pokemon_queue();
void* localized_pokemon_queue();
void* get_pokemon_queue();
void iniciarVectorDeSemaforos();
void iniciarVectorDeSockets();

void* queue(void*);

void asignar_id(t_paquete* paquete, uint32_t id);

void iniciarMensajes();

void guardar(t_paquete*);



typedef struct{
	uint32_t id_mensaje;
	uint32_t id_correlativo;
	t_list* suscriptores;
	memory_block_t* memory_block;

} clientes_por_mensaje_t;

typedef struct{

	uint32_t process_id;
	uint32_t ack;

}status_mensaje_t;

int fueEnviado(t_paquete* paquete, t_client* client);
clientes_por_mensaje_t* agregarMensaje(t_paquete* paquete);
status_mensaje_t* agregarCliente(clientes_por_mensaje_t* cxm, t_client* client);
clientes_por_mensaje_t* obtenerMensaje(int id_mensaje);
status_mensaje_t* obtenerStatus(t_list* suscriptores, int);
void procesarACK(t_buffer* buffer);




#endif /* BROKER_QUEUES_H_ */
