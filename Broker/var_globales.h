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
#include<semaphore.h>
#include<pthread.h>
#include<commons/collections/queue.h>


extern t_config* config;
extern t_log* logger;



extern t_list* subscribers[7];

extern t_list* mensajes;

extern t_queue* datos_para_guardar;
extern sem_t sem_msg_data;
extern pthread_mutex_t mx_mem;
extern pthread_mutex_t msg_mx;
extern pthread_mutex_t id_mx;




#endif /* VAR_GLOBALES_H_ */
