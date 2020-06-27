/*
 * queue_thread_vars.h
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_QUEUE_THREAD_VARS_H_
#define BROKER_QUEUE_THREAD_VARS_H_

#include<pthread.h>
#include<semaphore.h>
#include<stdint.h>
#include"../Utils/mensajes.h"

typedef struct{
	pthread_mutex_t mx; // Acceso exclusivo
	sem_t q; // Queue
	sem_t c; // Recepción del cliente
} queue_sem_t;

typedef struct{

	uint32_t socket_to_recv;
	t_id id_to_assing;

} next_socket_t;


extern next_socket_t next_socket[9];
extern queue_sem_t sem_sockets[9];
extern pthread_t thread_new_pokemon;
extern pthread_t thread_appeared_pokemon;
extern pthread_t thread_catch_pokemon;
extern pthread_t thread_caught_pokemon;
extern pthread_t thread_localized_pokemon;
extern pthread_t thread_get_pokemon;


#endif /* BROKER_QUEUE_THREAD_VARS_H_ */
