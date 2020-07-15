/*
 * deadlock.c
 *
 *  Created on: 12 jul. 2020
 *      Author: utnso
 */

#include "deadlock.h"

pthread_mutex_t mutex_deadlock;

void inicializarDeadlock(void) {
	pthread_mutex_init(&mutex_deadlock, NULL);
}

void deteccionYCorreccionDeadlock(void) {

	pthread_mutex_lock(&mutex_deadlock);
	pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
	int cant_blocked_full = list_size(entrenadores_blocked_full->lista);
	pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

	while (cant_blocked_full >= 2) {
		corregirUnDeadlock();

		pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
		cant_blocked_full = list_size(entrenadores_blocked_full->lista);
		pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));
	}
	pthread_mutex_unlock(&mutex_deadlock);
	/*
	 * Si queda 1 solo entrenador, significa que se capturó un pokemon que no tendría que haberse capturado
	 */
}

void corregirUnDeadlock(void) {
	// Buscar un entrenador que necesite un pokemon que otro entrenador no necesite
	pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
	int cantidad_enrenadores_full = list_size(entrenadores_blocked_full->lista);
	pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

	log_debug(logger, "Se lanza algoritmo de detección de deadlock");

	t_tcb* necesitado;
	t_tcb* buscado;
	char* pokemon_necesitado;
	char* pokemon_a_dar;

	t_intercambio* intercambio = malloc(sizeof(t_intercambio));
	t_list* pokemones_no_necesarios = NULL;

	for (int pos_necesitado = 0; pos_necesitado < cantidad_enrenadores_full; pos_necesitado++) {
		pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
		necesitado = list_get(entrenadores_blocked_full->lista, pos_necesitado);
		pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

		for (int pos_buscado = 0; pos_buscado < cantidad_enrenadores_full; pos_buscado++) {

			if (pos_necesitado == pos_buscado)	// Si son el mismo salteo
				continue;

			pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
			buscado = list_get(entrenadores_blocked_full->lista, pos_buscado);
			pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

			pokemon_necesitado = pokemonQueNoNecesiteYelOtroSi(buscado->entrenador, necesitado->entrenador);

			if (pokemon_necesitado != NULL) {
				log_debug(logger, "El entrenador %d necesita un %s y se lo va a dar el entrenador %d", necesitado->entrenador->id_entrenador, pokemon_necesitado, buscado->entrenador->id_entrenador);

				intercambio->tcb = buscado;
				intercambio->su_pokemon = pokemon_necesitado;

				// Trato de darle un pokemon que necesite, sino uno random
				pokemon_a_dar = pokemonQueNoNecesiteYelOtroSi(necesitado->entrenador, buscado->entrenador);
				if (pokemon_a_dar == NULL) {
					pokemones_no_necesarios = pokemonesNoNecesariosDe(necesitado->entrenador);
					t_inventario* inv = (t_inventario*) list_get(pokemones_no_necesarios, 0);
					pokemon_a_dar = malloc(inv->pokemon->name_size);
					memcpy(pokemon_a_dar, inv->pokemon->name, inv->pokemon->name_size);	// Lo copio para poder hacer free de la lista entera
				}

				intercambio->mi_pokemon = pokemon_a_dar;
				necesitado->intercambio = intercambio;

				if (pokemones_no_necesarios != NULL)
					liberarListaDeInventario(pokemones_no_necesarios);

				cambiarDeCola(buscado, entrenadores_blocked_full, entrenadores_blocked_waiting_trade);
				cambiarDeCola(necesitado, entrenadores_blocked_full, entrenadores_ready);
				return;
			}
		}
	}
}
