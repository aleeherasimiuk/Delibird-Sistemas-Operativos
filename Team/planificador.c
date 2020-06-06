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

t_queue* pokemones_en_el_mapa; // Lista de t_pokemon_en_mapa*

int retardo_ciclo_cpu;

// VER DE USAR SEM_T para hacer contadores
pthread_mutex_t mutex_pokemones_libres; // para ver si hay pokemones que no están siendo buscados por algún entrenador
pthread_mutex_t mutex_entrenadores_disponibles; // para ver si hay entrenadores disponibles (new/blocked_idle)

//////////////////////////////////////
//				STRUCTS				//
//////////////////////////////////////

t_pokemon_en_mapa* crearPokemonEnMapa(t_pokemon* pokemon, t_coords* posicion) {
	t_pokemon_en_mapa* pokemon_en_mapa = malloc(sizeof(t_pokemon_en_mapa));
	pokemon_en_mapa->pokemon = pokemon;
	pokemon_en_mapa->posicion = posicion;

	return pokemon_en_mapa;
}

//////////////////////////////////////
//			INICIALIZACION			//
//////////////////////////////////////

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
	pthread_t thread;
	for(int i = 0; i < objetivo_global->elements_count; i++) {
		objetivo = list_get(objetivo_global, i);
		pthread_create(&thread, NULL, enviarGetPokemon, objetivo->pokemon);
		pthread_detach(thread);
	}
}

void iniciarPlanificador(void) {
	pokemones_en_el_mapa = queue_create();
	retardo_ciclo_cpu = config_get_int_value(config, "RETARDO_CICLO_CPU");

	pthread_mutex_init(&mutex_pokemones_libres, NULL);
	pthread_mutex_lock(&mutex_pokemones_libres); // Lo lockeo porque todavía no hay pokemones en la lista

	pthread_t thread;

	pthread_create(&thread, NULL, mandarABuscarPokemones, NULL);
}


//////////////////////////////////////
//				EJECUCION			//
//////////////////////////////////////

	//////////////////////////////////////
	//			PLANI LARGO PLAZO		//
	//////////////////////////////////////

t_entrenador* entrenadorMasCercanoA(t_pokemon_en_mapa* pokemon) {

	t_entrenador* entrenador_temp;
	int distancia_temp;

	if (list_is_empty(entrenadores_new)) {
		// TODO if (list_is_empty(entrenadores_blocked_idle))
	}
	t_entrenador* entrenador_mas_cercano = list_get(entrenadores_new, 0);
	int menor_distancia = distanciaA(entrenador_mas_cercano->posicion, pokemon->posicion);

	int index; // Para recorrer los entrenadores
	// Recorro en los de estado new
	for (index = 1; index < entrenadores_new->elements_count; index++) {
		if (menor_distancia == 0) break;	// corto porque sería la distancia minima, entonces dejo de recorrer

		entrenador_temp = list_get(entrenadores_new, index);
		distancia_temp = distanciaA(entrenador_temp->posicion, pokemon->posicion);
		if (distancia_temp < menor_distancia) {
			entrenador_mas_cercano = entrenador_temp;
			menor_distancia = distancia_temp;
		}
	}

	// Si ya tengo al minimo, directamente salgo
	if (menor_distancia == 0) return entrenador_mas_cercano;

	// busco en blocked_idle
	for (index = 0; index < entrenadores_blocked_idle->elements_count; index++) {
		if (menor_distancia == 0) break;	// corto porque sería la distancia minima, entonces dejo de recorrer

		entrenador_temp = list_get(entrenadores_blocked_idle, index);
		distancia_temp = distanciaA(entrenador_temp->posicion, pokemon->posicion);
		if (distancia_temp < menor_distancia) {
			entrenador_mas_cercano = entrenador_temp;
			menor_distancia = distancia_temp;
		}
	}

	return entrenador_mas_cercano;
}

void *mandarABuscarPokemones(void) { //Pasar de new/blocked_idle a ready (Planificador a largo plazo)
	t_entrenador* entrenador; // entrenador a pasar a ready - desde new o blocked_idle
	t_pokemon_en_mapa* pokemon;
	while(1)  { // TODO no esté en exit el team
		pthread_mutex_lock(&mutex_pokemones_libres);
		pthread_mutex_lock(&mutex_entrenadores_disponibles);
		pokemon = queue_pop(pokemones_en_el_mapa);
		entrenador = entrenadorMasCercanoA(pokemon);
	}
}

void realizarCicloDeCPU(void) {
	realizarXCiclosDeCPU(1);
}

void realizarXCiclosDeCPU(int cant_ciclos) {
	sleep(retardo_ciclo_cpu* cant_ciclos);
}

