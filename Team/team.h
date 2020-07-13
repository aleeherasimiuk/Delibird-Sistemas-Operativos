#ifndef TEAM_H_
#define TEAM_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

#include "mensajesTeam.h"
#include "conexionesTeam.h"
#include "entrenadores.h"
#include "planificador.h"
#include "deadlock.h"
#include "var_globales.h"



void inicializar_team(void);
t_log* iniciar_logger(char*);
t_config* leer_config(void);
void terminar_programa(int, t_log*, t_config*);

#endif /* TEAM_H_ */
