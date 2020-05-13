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

#include "../utils/mensajes.h"
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

// Es probable que haya que poder identificar de otra manera a los clientes
typedef struct{
	uint32_t socket;
} t_client;

typedef struct{
	uint32_t client;
	uint32_t id;
	uint32_t received;
}t_message_by_client;


uint32_t suscribirCliente(t_buffer* msg, uint32_t size);




#endif /* BROKER_QUEUES_H_ */
