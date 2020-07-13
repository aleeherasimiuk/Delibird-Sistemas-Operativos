/*
 * deadlock.c
 *
 *  Created on: 12 jul. 2020
 *      Author: utnso
 */

#include "deadlock.h"

void deteccionYCorreccionDeadlock(void) {
	while (list_size(entrenadores_blocked_full) >= 2) {
		corregirUnDeadlock();
	}
	/*
	 * Si queda 1 solo entrenador, significa que se capturó un pokemon que no tendría que haberse capturado
	 */
}

void corregirUnDeadlock(void) {
	// Buscar un entrenador que necesite un pokemon que otro entrenador no necesite
	int cantidad_enrenadores_full = list_size(entrenadores_blocked_full);
	log_debug(logger, "Se lanza algoritmo de detección de deadlock");

	t_pokemon_en_mapa* objetivo = malloc(sizeof(t_pokemon_en_mapa));
	objetivo->pokemon = NULL;	// Si es null, lo va a tomar como que está en deadlock

	t_tcb* necesitado;
	t_tcb* buscado;
	char* pokemon_necesitado;

	for (int pos_necesitado = 0; pos_necesitado < cantidad_enrenadores_full; pos_necesitado++) {
		necesitado = list_get(entrenadores_blocked_full, pos_necesitado);
		for (int pos_buscado = 1; pos_buscado < cantidad_enrenadores_full; pos_buscado++) {

			if (pos_necesitado == pos_buscado)	// Si son el mismo salteo
				continue;

			buscado = list_get(entrenadores_blocked_full, pos_buscado);
			pokemon_necesitado = pokemonQueNoNecesiteYelOtroSi(buscado->entrenador, necesitado->entrenador);

			if (pokemon_necesitado != NULL) {
				log_debug(logger, "El entrenador %d necesita un %s y se lo va a dar el entrenador %d", necesitado->entrenador->id_entrenador, pokemon_necesitado, buscado->entrenador->id_entrenador);

				objetivo->posicion = buscado->entrenador->posicion;
				necesitado->entrenador->objetivo = objetivo;

				cambiarDeLista(necesitado, entrenadores_blocked_full, entrenadores_ready);
			}
		}
	}
}
