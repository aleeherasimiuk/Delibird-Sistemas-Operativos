/*
 * broker.h
 *
 *  Created on: 24 abr. 2020
 *      Author: utnso
 */

#ifndef BROKER_H_
#define BROKER_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<signal.h>

#include "../Utils/mensajes.h"
#include "AdministradorDeMemoria/administracion_de_memoria.h"
#include "utils.h"
#include "queues.h"
#include "var_globales.h"
#include "AdministradorDeMemoria/dump_cache.h"

t_config* leer_config(void);
void iniciarSubscribers(void);
t_log* iniciar_logger(char*);
void iniciarSignals();



#endif /* BROKER_H_ */
