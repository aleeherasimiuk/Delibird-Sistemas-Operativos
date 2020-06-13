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
/*
 typedef struct{
	t_queue* new_pokemon;
	t_queue* appeared_pokemon;
	t_queue* catch_pokemon;
	t_queue* caught_pokemon;
	t_queue* get_pokemon;
	t_queue* localized_pokemon;
}t_queues;
*/

typedef struct{

	t_list* new_pokemon;
	t_list* appeared_pokemon;
	t_list* catch_pokemon;
	t_list* caught_pokemon;
	t_list* get_pokemon;
	t_list* localized_pokemon;
}t_subscribers;

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

void appeared_pokemon_to_subscribers(t_paquete*);




#endif /* BROKER_QUEUES_H_ */
