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
//#include<commons/collections/queue.h>
#include<commons/collections/list.h>

#include "../Utils/mensajes.h"

#include<pthread.h>
#include<semaphore.h>

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

typedef struct{
	pthread_mutex_t mx; // Acceso exclusivo
	sem_t q; // Queue
	sem_t c; // Recepción del cliente
} queue_sem_t;

typedef struct{

	uint32_t socket_to_recv;
	t_id id_to_assing;

} next_socket_t;




#endif /* BROKER_QUEUES_H_ */
