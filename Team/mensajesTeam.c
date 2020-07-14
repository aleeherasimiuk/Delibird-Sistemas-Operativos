/*
 * mensajesTeam.c
 *
 *  Created on: 7 jul. 2020
 *      Author: utnso
 */

#include "mensajesTeam.h"

t_list* get_enviados;	// lista de uint32_t, Se guardan los ids de los gets enviados para verificar localizeds

sem_t mutex_get_enviados;

t_list* pokemones_recibidos; // lista de char*, se guardan los nombres de pokemones que se recibieron mediante appeared o localized

sem_t mutex_pokemones_recibidos;

t_list* catch_enviados; // lista de t_mensaje_catch*, se guardan los catch enviados y el tcb que se tiene que activar dependiendo la respuesta

sem_t mutex_catch_enviados;

void inciarListasMensajes (void) {
	get_enviados = list_create();
	pokemones_recibidos = list_create();
	catch_enviados = list_create();

	sem_init(&mutex_get_enviados, 0, 1);
	sem_init(&mutex_pokemones_recibidos, 0, 1);
	sem_init(&mutex_catch_enviados, 0, 1);
}

void addGetEnviado(uint32_t id) {
	uint32_t* idPtr = malloc(sizeof(uint32_t));
	*idPtr = id;
	log_debug(logger, "Se añade el get con id %d", id);

	sem_wait(&mutex_get_enviados);
	list_add(get_enviados, idPtr);
	sem_post(&mutex_get_enviados);
}

void addPokemonRecibido(char* pokemon_name) {
	log_debug(logger, "Se añade el pokemon %s a la lista de recibidos", pokemon_name);
	sem_wait(&mutex_pokemones_recibidos);
	list_add(pokemones_recibidos, pokemon_name);
	sem_post(&mutex_pokemones_recibidos);
}

void addCatchEnviado(uint32_t id, t_tcb* tcb) {
	t_mensaje_catch* msj = malloc(sizeof(t_mensaje_catch));
	msj->id = id;
	msj->tcb = tcb;
	log_debug(logger, "Se añade el catch con id %d", id);
	sem_wait(&mutex_catch_enviados);
	list_add(catch_enviados, msj);
	sem_post(&mutex_catch_enviados);
}

int getEnviadoConID(uint32_t id, int* index) {
	int position = 0;
	uint32_t* actual;
	sem_wait(&mutex_get_enviados);
	actual = list_get(get_enviados, position);
	sem_post(&mutex_get_enviados);

	while (actual != NULL && id != *actual) {
		// Recorro la lista hasta que se termine o que encuentre el id correspondiente
		position++;
		sem_wait(&mutex_get_enviados);
		actual = list_get(get_enviados, position);
		sem_post(&mutex_get_enviados);
	}

	if (index != NULL)
		*index = position;

	return actual != NULL;
}

int pokemonYaRecibido(char* pokemon_name) {
	int position = 0;
	char* actual;
	sem_wait(&mutex_pokemones_recibidos);
	actual = list_get(pokemones_recibidos, position);
	sem_post(&mutex_pokemones_recibidos);

	while (actual != NULL && strcmp(actual, pokemon_name) != 0) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		position++;
		sem_wait(&mutex_pokemones_recibidos);
		actual = list_get(pokemones_recibidos, position);
		sem_post(&mutex_pokemones_recibidos);
	}

	return actual != NULL;
}

t_mensaje_catch* buscarCatchEnviadoSegunIDMensaje(uint32_t id, uint32_t* index) {
	int position = 0;
	t_mensaje_catch* actual;
	sem_wait(&mutex_catch_enviados);
	actual = list_get(catch_enviados, position);
	sem_post(&mutex_catch_enviados);

	while (actual != NULL && actual->id != id) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		position++;
		sem_wait(&mutex_catch_enviados);
		actual = list_get(catch_enviados, position);
		sem_post(&mutex_catch_enviados);
	}

	if (index != NULL)
		*index = position;

	return actual;
}

t_tcb* traerTcbDelCatchConID(uint32_t id) {
	t_mensaje_catch* catch;

	catch = buscarCatchEnviadoSegunIDMensaje(id, NULL);

	if (catch == NULL)
		return NULL;

	return catch->tcb;
}

void eliminarGetEnviado(uint32_t id) {
	int index;
	uint32_t* id_get;

	if (!getEnviadoConID(id, &index))
		return;

	sem_wait(&mutex_get_enviados);
	id_get = list_remove(get_enviados, index);
	sem_post(&mutex_get_enviados);

	free(id_get);

	log_debug(logger, "Se elimina el GET enviado con id %d", id);

	return;
}

void eliminarCatchEnviado(uint32_t id) {
	uint32_t index;
	t_mensaje_catch* catch;

	catch = buscarCatchEnviadoSegunIDMensaje(id, &index);

	if (catch == NULL)
		return;
	sem_wait(&mutex_catch_enviados);
	list_remove(catch_enviados, index);
	sem_post(&mutex_catch_enviados);

	free(catch);

	log_debug(logger, "Se elimina el CATCH enviado con id %d", id);

	return;
}
