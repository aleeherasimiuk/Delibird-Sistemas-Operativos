/*
 * planificador.c
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#include "planificador.h"

t_list* entrenadores_new;
t_list* entrenadores_ready;
t_list* entrenadores_blocked;
t_list* entrenadores_exit;
t_entrenador* entrenador_exec;

t_list* objetivo_global;


void *threadfunction(void *arg)
{
	t_entrenador* entrenador = (t_entrenador*)arg;
	printf("Soy el entrenador %d\n", entrenador->id_entrenador); /*printf() is specified as thread-safe as of C11*/
	return 0;
}

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
