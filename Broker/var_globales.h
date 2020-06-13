/*
 * var_globales.h
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#ifndef VAR_GLOBALES_H_
#define VAR_GLOBALES_H_

#include<commons/config.h>
#include<commons/collections/list.h>
#include<commons/log.h>
#include "queues.h"
#include<pthread.h>

extern t_config* config;
extern t_log* logger;
extern t_subscribers* subscribers;

extern pthread_t thread_new_pokemon;
extern pthread_t thread_appeared_pokemon;
extern pthread_t thread_catch_pokemon;
extern pthread_t thread_caught_pokemon;
extern pthread_t thread_localized_pokemon;
extern pthread_t thread_get_pokemon;

uint32_t next_socket[9];
pthread_mutex_t sem_sockets[9];


#endif /* VAR_GLOBALES_H_ */
