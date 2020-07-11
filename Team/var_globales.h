/*
 * var_globales.h
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#ifndef VAR_GLOBALES_H_
#define VAR_GLOBALES_H_

#include<commons/config.h>
#include<commons/log.h>
#include<commons/collections/list.h>

extern t_config* config;
extern t_log* logger;
extern uint32_t process_id;

extern t_list* entrenadores_new; // lista de t_tcb*
extern t_list* entrenadores_ready; // lista de t_tcb*
extern t_list* entrenadores_blocked_idle; // lista de t_tcb* que se bloquea sin tareas
extern t_list* entrenadores_blocked_waiting_caught; // acá van los que se bloquean esperando a recibir un caught
extern t_list* entrenadores_blocked_full; // Bloqueados por no poder agarrar mas pokemones, pero no cumplen su objetivo
extern t_list* entrenadores_exit; // lista de t_tcb*

extern t_list* actuales_global;

#endif /* VAR_GLOBALES_H_ */
