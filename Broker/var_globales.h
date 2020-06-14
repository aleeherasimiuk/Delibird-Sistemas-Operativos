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

extern t_config* config;
extern t_log* logger;

extern pthread_t thread_new_pokemon;
extern pthread_t thread_appeared_pokemon;
extern pthread_t thread_catch_pokemon;
extern pthread_t thread_caught_pokemon;
extern pthread_t thread_localized_pokemon;
extern pthread_t thread_get_pokemon;


extern t_list* subscribers[7];
uint32_t next_socket[9];
queue_sem_t sem_sockets[9];




#endif /* VAR_GLOBALES_H_ */
