/*
 * planificador.c
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#include "planificador.h"

t_list* entrenadores_new; // lista de t_entrenador*
t_list* entrenadores_ready; // lista de t_entrenador*
t_list* entrenadores_blocked; // lista de t_entrenador*
t_list* entrenadores_exit; // lista de t_entrenador*
t_entrenador* entrenador_exec;

t_list* objetivo_global;  // lista de t_inventario*


void cargarEntrenadores(void) {
	entrenadores_new = list_create();
	objetivo_global = list_create();

	char** posiciones_entrenadores = config_get_array_value(config, "POSICIONES_ENTRENADORES");
	char** pokemon_entrenadores    = config_get_array_value(config, "POKEMON_ENTRENADORES");
	char** objetivos_entrenadores  = config_get_array_value(config, "OBJETIVOS_ENTRENADORES");

	t_entrenador* entrenador_nuevo;
	pthread_t thread;

	int i = 0;
	while(posiciones_entrenadores[i] != NULL) {
		// CADA i ES UN ENTRENADOR NUEVO
		entrenador_nuevo = malloc(sizeof(t_entrenador));

		entrenador_nuevo->id_entrenador = i + 1;
		entrenador_nuevo->posicion = crearCoordenadas(posiciones_entrenadores[i]);
		entrenador_nuevo->pokes_actuales = crearListaDeInventario(pokemon_entrenadores[i], NULL);
		entrenador_nuevo->pokes_objetivos = crearListaDeInventario(objetivos_entrenadores[i], objetivo_global);

		list_add(entrenadores_new, entrenador_nuevo);

		pthread_create(&thread, NULL, entrenadorMain, entrenador_nuevo);

		i++;
	}
}

void enviarGetsAlBroker(void) {
	t_inventario* objetivo;
	for(int i = 0; i < objetivo_global->elements_count; i++) {
		objetivo = list_get(objetivo_global, i);
		enviarGetPokemon(objetivo->pokemon);
	}
}

