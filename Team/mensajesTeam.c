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

t_tcb* traerTcbDelCatchConID(uint32_t id) {
	int position = 0;
	t_mensaje_catch* actual;
	actual = list_get(catch_enviados, position);

	while (actual != NULL && actual->id != id) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		position++;
		actual = list_get(catch_enviados, position);
	}

	return actual;
}
