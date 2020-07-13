/*
 * mensajesTeam.c
 *
 *  Created on: 7 jul. 2020
 *      Author: utnso
 */

#include "mensajesTeam.h"

t_list* get_enviados;	// lista de uint32_t, Se guardan los ids de los gets enviados para verificar localizeds

t_list* pokemones_recibidos; // lista de char*, se guardan los nombres de pokemones que se recibieron mediante appeared o localized

t_list* catch_enviados; // lista de t_mensaje_catch*, se guardan los catch enviados y el tcb que se tiene que activar dependiendo la respuesta

void inciarListasMensajes (void) {
	get_enviados = list_create();
	pokemones_recibidos = list_create();
	catch_enviados = list_create();
}

void addGetEnviado(uint32_t id) {
	uint32_t* idPtr = malloc(sizeof(uint32_t));
	*idPtr = id;
	log_debug(logger, "Se añade el get con id %d", id);
	list_add(get_enviados, idPtr);
}

void addPokemonRecibido(char* pokemon_name) {
	log_debug(logger, "Se añade el pokemon %s a la lista de recibidos", pokemon_name);
	list_add(pokemones_recibidos, pokemon_name);
}

void addCatchEnviado(uint32_t id, t_tcb* tcb) {
	t_mensaje_catch* msj = malloc(sizeof(t_mensaje_catch));
	msj->id = id;
	msj->tcb = tcb;
	log_debug(logger, "Se añade el catch con id %d", id);
	list_add(catch_enviados, msj);
}

int getEnviadoConID(uint32_t id, int* index) {
	int position = 0;
	uint32_t* actual;
	actual = list_get(get_enviados, position);

	while (actual != NULL && id != *actual) {
		// Recorro la lista hasta que se termine o que encuentre el id correspondiente
		position++;
		actual = list_get(get_enviados, position);
	}

	if (index != NULL)
		*index = position;

	return actual != NULL;
}

int pokemonYaRecibido(char* pokemon_name) {
	int position = 0;
	char* actual;
	actual = list_get(pokemones_recibidos, position);

	while (actual != NULL && strcmp(actual, pokemon_name) != 0) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		position++;
		actual = list_get(pokemones_recibidos, position);
	}

	return actual != NULL;
}

t_mensaje_catch* buscarCatchEnviadoSegunIDMensaje(uint32_t id, uint32_t* index) {
	int position = 0;
	t_mensaje_catch* actual;
	actual = list_get(catch_enviados, position);

	while (actual != NULL && actual->id != id) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		position++;
		actual = list_get(catch_enviados, position);
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
	uint32_t index;
	uint32_t* id_get;

	if (!getEnviadoConID(id, &index))
		return;

	id_get = list_remove(catch_enviados, index);

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

	list_remove(catch_enviados, index);

	free(catch);

	log_debug(logger, "Se elimina el CATCH enviado con id %d", id);

	return;
}
