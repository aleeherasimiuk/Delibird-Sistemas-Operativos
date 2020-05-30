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

#include "../Utils/mensajes.h"
#include "utils.h"
#include "queues.h"

t_config* leer_config(void);
t_subscribers* iniciarSubscribers(void);



#endif /* BROKER_H_ */
