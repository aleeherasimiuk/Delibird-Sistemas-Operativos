/*
 * deadlock.c
 *
 *  Created on: 12 jul. 2020
 *      Author: utnso
 */

#include "deadlock.h"

pthread_mutex_t mutex_deadlock;
int hubo_deadlock;	// Se pone en 1 si no se produce deadlock entre los que están en la lista
int hay_deadlock;
t_list* lista_de_deadlocks;

void inicializarDeadlock(void) {
	pthread_mutex_init(&mutex_deadlock, NULL);
	lista_de_deadlocks = list_create();
}

void deteccionYCorreccionDeadlock(void) {

	pthread_mutex_lock(&mutex_deadlock);
	pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
	int cant_blocked_full = list_size(entrenadores_blocked_full->lista);
	pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));
	hubo_deadlock = 0;
	hay_deadlock = 1;

	if (log_deadlocks_producidos == 0) {
		log_info(logger, "INICIO DE ALGORITMO DE DETECCIÓN DE DEADLOCK");
		deteccionDeadlock();
		if (log_deadlocks_producidos == 0) {
			log_info(logger, "NO HAY DEADLOCKS");
		}
	}
	while (cant_blocked_full >= 2 && hay_deadlock == 1 && log_deadlocks_producidos > 0) {
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

void deteccionDeadlock(void) {
	t_list* entrenadores_en_deadlock = list_create();
	t_tcb* tcb = NULL;
	char* log_msg;

	int cant_blocked_full = list_size(entrenadores_blocked_full->lista);

	for (int index = 0; index < cant_blocked_full; index++) {
		tcb = (t_tcb*) list_get(entrenadores_blocked_full->lista, index);
		list_add(entrenadores_en_deadlock, tcb);
		agregarEntrenadorQueTengaElQueNecesita(entrenadores_en_deadlock, tcb);
		list_clean(entrenadores_en_deadlock);
	}

	t_list* list_temp = NULL;
	sacarDeadlocksRepetidos(lista_de_deadlocks);

	for (int index_lista = 0; index_lista < list_size(lista_de_deadlocks); index_lista++) {
		list_temp = list_get(lista_de_deadlocks, index_lista);
		if (list_size(list_temp) > 1){
			log_msg = string_from_format("DEADLOCK ENTRE LOS ENTRENADORES:");
			for (int i = 0; i < list_size(list_temp); i++) {
				tcb = (t_tcb*) list_get(list_temp, i);
				string_append_with_format(&log_msg, " %d", tcb->entrenador->id_entrenador);
			}
			log_info(logger, log_msg);
			free(log_msg);
		}
		list_destroy(list_temp);
	}

	// LOG
	if (log_deadlocks_producidos == 0)
		log_deadlocks_producidos = list_size(lista_de_deadlocks);

	list_clean(lista_de_deadlocks);
	free(entrenadores_en_deadlock);
}

int agregarEntrenadorQueTengaElQueNecesita(t_list* entrenadores_en_deadlock, t_tcb* tcb_necesitado) {
	int cant_blocked_full = list_size(entrenadores_blocked_full->lista);
	t_tcb* tcb;
	t_tcb* primer_elemento = (t_tcb*) list_get(entrenadores_en_deadlock, 0);

	char* pokemon_name = NULL;
	for (int index = 0; index < cant_blocked_full; index++) {
		tcb = list_get(entrenadores_blocked_full->lista, index);

		// ignora si ya está en la lista, excepto que sea el primero, ya que eso sería un deadlock propio del tcb_necesitado actual
		if (tcb == tcb_necesitado){
			continue;
		}

		pokemon_name = pokemonQueNoNecesiteYelOtroSi(tcb->entrenador, tcb_necesitado->entrenador);

		if (pokemon_name != NULL) {
			free(pokemon_name);

			// Si se cierra el ciclo, hago return, sino sigo buscando
			if (tcb->entrenador->id_entrenador == primer_elemento->entrenador->id_entrenador) {
				return 1;
			} else {
				// Si ya estaba en la lista devuelvo por error
				if (indexOf(tcb, entrenadores_en_deadlock) != -1)
					return 0;

				// Lo agrego porque tiene que verificar en los otros niveles, y por si termina
				list_add(entrenadores_en_deadlock, tcb);

				if (agregarEntrenadorQueTengaElQueNecesita(entrenadores_en_deadlock, tcb)) {
					list_add(lista_de_deadlocks, list_duplicate(entrenadores_en_deadlock));
				}
				list_remove(entrenadores_en_deadlock, list_size(entrenadores_en_deadlock) - 1);

			}
		}
	}
	return 0;
}


void sacarDeadlocksRepetidos(t_list* lista_deadlock) {
	t_list* deadlock_temp = NULL;
	for (int i = 0; i < list_size(lista_deadlock); i++) {
		deadlock_temp = list_get(lista_deadlock, i);

		if (deadlockRepetidoEn(lista_deadlock, deadlock_temp, i)) {
			list_remove(lista_deadlock, i);
			i--;
			list_destroy(deadlock_temp);
		}
	}
}

int deadlockRepetidoEn(t_list* lista_deadlock, t_list* deadlock, int index_max) {
	t_list* deadlock_temp = NULL;
	for (int i = 0; i < index_max; i++) {
		deadlock_temp = list_get(lista_deadlock, i);

		if (deadlock_temp == deadlock)
				continue;

		if (tieneMismosTcbsPeroNoSonIguales(deadlock_temp, deadlock))
			return 1;
	}
	return 0;
}

// Tienen los mismos tcbs
int tieneMismosTcbsPeroNoSonIguales(t_list* deadlock1, t_list* deadlock2) {
	t_tcb* tcb_temp = NULL;
	for (int i = 0; i < list_size(deadlock1); i++) {
		tcb_temp = list_get(deadlock1, i);

		if (indexOf(tcb_temp, deadlock2) == -1)
			return 0;

	}
	return 1;
}


void corregirUnDeadlock(void) {
	// Buscar un entrenador que necesite un pokemon que otro entrenador no necesite
	pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
	int cantidad_entrenadores_full = list_size(entrenadores_blocked_full->lista);
	pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

	log_debug(logger, "Se lanza algoritmo de detección de deadlock");

	t_tcb* necesitado;
	t_tcb* buscado;
	char* pokemon_necesitado;
	char* pokemon_a_dar;

	t_intercambio* intercambio = malloc(sizeof(t_intercambio));
	t_list* pokemones_no_necesarios = NULL;

	hay_deadlock = 0;

	for (int pos_necesitado = 0; pos_necesitado < cantidad_entrenadores_full; pos_necesitado++) {
		pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
		necesitado = list_get(entrenadores_blocked_full->lista, pos_necesitado);
		pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

		for (int pos_buscado = 0; pos_buscado < cantidad_entrenadores_full; pos_buscado++) {

			if (pos_necesitado == pos_buscado)	// Si son el mismo salteo
				continue;

			pthread_mutex_lock(&(entrenadores_blocked_full->mutex));
			buscado = list_get(entrenadores_blocked_full->lista, pos_buscado);
			pthread_mutex_unlock(&(entrenadores_blocked_full->mutex));

			pokemon_necesitado = pokemonQueNoNecesiteYelOtroSi(buscado->entrenador, necesitado->entrenador);

			if (pokemon_necesitado != NULL) {

				hubo_deadlock = 1;
				hay_deadlock = 1;

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

				log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: [Entrenador %d] -> BLOCKED_WAITING_TRADE: Está esperando a que llegue [Entrenador %d] para hacer un intercambio", buscado->entrenador->id_entrenador, necesitado->entrenador->id_entrenador);
				cambiarDeCola(buscado, entrenadores_blocked_full, entrenadores_blocked_waiting_trade);
				
				log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: [Entrenador %d] -> READY: Irá a la posición del [Entrenador %d] para realizar un intercambio", necesitado->entrenador->id_entrenador, buscado->entrenador->id_entrenador);
				cambiarDeCola(necesitado, entrenadores_blocked_full, entrenadores_ready);
				return;
			} else {
				free(pokemon_necesitado);
			}
		}
	}
	free(intercambio);
}
