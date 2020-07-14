/*
 * deadlock.c
 *
 *  Created on: 12 jul. 2020
 *      Author: utnso
 */

#include "deadlock.h"

sem_t mutex_deadlock;

void inicializarDeadlock(void) {
	sem_init(&mutex_deadlock, 0, 1);
}

void deteccionYCorreccionDeadlock(void) {

	sem_wait(&mutex_deadlock);
	sem_wait(&(entrenadores_blocked_full->mutex));
	int cant_blocked_full = list_size(entrenadores_blocked_full->lista);
	sem_post(&(entrenadores_blocked_full->mutex));

	while (cant_blocked_full >= 2) {
		corregirUnDeadlock();

		sem_wait(&(entrenadores_blocked_full->mutex));
		cant_blocked_full = list_size(entrenadores_blocked_full->lista);
		sem_post(&(entrenadores_blocked_full->mutex));
	}
	sem_post(&mutex_deadlock);
	/*
	 * Si queda 1 solo entrenador, significa que se capturó un pokemon que no tendría que haberse capturado
	 */
}

void corregirUnDeadlock(void) {
	// Buscar un entrenador que necesite un pokemon que otro entrenador no necesite
	sem_wait(&(entrenadores_blocked_full->mutex));
	int cantidad_enrenadores_full = list_size(entrenadores_blocked_full->lista);
	sem_post(&(entrenadores_blocked_full->mutex));

	log_debug(logger, "Se lanza algoritmo de detección de deadlock");

	t_tcb* necesitado;
	t_tcb* buscado;
	char* pokemon_necesitado;
	char* pokemon_a_dar;

	t_intercambio* intercambio = malloc(sizeof(t_intercambio));
	t_list* pokemones_no_necesarios = NULL;

	for (int pos_necesitado = 0; pos_necesitado < cantidad_enrenadores_full; pos_necesitado++) {
		sem_wait(&(entrenadores_blocked_full->mutex));
		necesitado = list_get(entrenadores_blocked_full->lista, pos_necesitado);
		sem_post(&(entrenadores_blocked_full->mutex));

		for (int pos_buscado = 0; pos_buscado < cantidad_enrenadores_full; pos_buscado++) {

			if (pos_necesitado == pos_buscado)	// Si son el mismo salteo
				continue;

			sem_wait(&(entrenadores_blocked_full->mutex));
			buscado = list_get(entrenadores_blocked_full->lista, pos_buscado);
			sem_post(&(entrenadores_blocked_full->mutex));

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

				cambiarDeLista(buscado, entrenadores_blocked_full, entrenadores_blocked_waiting_trade);
				cambiarDeLista(necesitado, entrenadores_blocked_full, entrenadores_ready);
				return;
			}
		}
	}
}
