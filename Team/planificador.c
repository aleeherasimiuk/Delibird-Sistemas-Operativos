/*
 * planificador.c
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#include "planificador.h"

t_list* entrenadores_new; // lista de t_tcb*
t_list* entrenadores_ready; // lista de t_tcb*
t_list* entrenadores_blocked_idle; // lista de t_tcb* que se bloquea sin tareas
t_list* entrenadores_blocked_waiting_caught; // acá van los que se bloquean esperando a recibir un caught
t_list* entrenadores_blocked_full; // Bloqueados por no poder agarrar mas pokemones, pero no cumplen su objetivo
t_list* entrenadores_exit; // lista de t_tcb*
t_tcb* entrenador_exec;

t_list* objetivo_global;  // lista de t_inventario*


void cargarEntrenadores(void) {
	entrenadores_new = list_create();
	objetivo_global = list_create();

	char** posiciones_entrenadores = config_get_array_value(config, "POSICIONES_ENTRENADORES");
	char** pokemon_entrenadores    = config_get_array_value(config, "POKEMON_ENTRENADORES");
	char** objetivos_entrenadores  = config_get_array_value(config, "OBJETIVOS_ENTRENADORES");

	t_tcb* tcb_nuevo;
	pthread_t thread;


	int i = 0;
	while(posiciones_entrenadores[i] != NULL) {

		// CADA i ES UN ENTRENADOR NUEVO

		tcb_nuevo = malloc(sizeof(t_tcb));
		tcb_nuevo->entrenador = malloc(sizeof(t_entrenador));

		tcb_nuevo->entrenador->id_entrenador = i + 1;
		tcb_nuevo->entrenador->posicion = crearCoordenadas(posiciones_entrenadores[i]);
		tcb_nuevo->entrenador->pokes_actuales = crearListaDeInventario(pokemon_entrenadores[i], NULL);
		tcb_nuevo->entrenador->pokes_objetivos = crearListaDeInventario(objetivos_entrenadores[i], objetivo_global);

		pthread_mutex_init(&(tcb_nuevo->mutex_ejecucion), NULL); // TODO pthread_mutex_destroy cuando se deje de usar para siempre
		pthread_mutex_lock(&(tcb_nuevo->mutex_ejecucion)); // Lo bloqueo al principio asi no empieza la ejecucion del entrenador, se desbloquea cuando lo pase a ejecucion

		list_add(entrenadores_new, tcb_nuevo);

		pthread_create(&thread, NULL, entrenadorMain, tcb_nuevo);
		pthread_detach(thread);
		i++;
	}
}

void enviarGetsAlBroker(void) {
	t_inventario* objetivo;
	for(int i = 0; i < objetivo_global->elements_count; i++) {
		objetivo = list_get(objetivo_global, i);
		enviarGetPokemon(objetivo->pokemon);
		// TODO VER QUE CARAJO HACE CUANDO NO FUNCIONA EL BROKER
	}
}

