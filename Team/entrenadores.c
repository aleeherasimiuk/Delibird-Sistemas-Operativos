/*
 * entrenadores.c
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#include"entrenadores.h"



//////////////////////////////////////////
//				INICIALIZACION			//
//////////////////////////////////////////

t_coords* crearCoordenadas(char* string_coord) {
	char** coords_array = string_split(string_coord, "|");
	t_coords* coords_nuevas = crear_coordenadas_from_int(atoi(coords_array[0]), atoi(coords_array[1]));

	liberarListaDePunteros(coords_array);

	return coords_nuevas;
}

//////////////////////////////////////////
//				INVENTARIO				//
//////////////////////////////////////////

t_list* crearListaDeInventario(char* pokemones_string, t_list* lista_global) {
	char** pokemones_array = string_split(pokemones_string, "|");
	t_list* lista_inventario = list_create();

	int i = 0;
	while(pokemones_array[i] != NULL) {
		char* pokemon_name = pokemones_array[i];

		cargarPokemonEnListaDeInventario(lista_inventario, pokemon_name);

		if (lista_global != NULL) {	// Cargo los pokemones en la lista global (actuales, objetivo)
			cargarPokemonEnListaDeInventario(lista_global, pokemon_name);
		}

		i++;
	}

	liberarListaDePunteros(pokemones_array);

	return lista_inventario;
}

void cargarPokemonEnListaDeInventario(t_list* lista_inventario, char* pokemon_name) {
	t_inventario* nuevo_inventario;
	// Verifico que el pokemon no esté cargado
	nuevo_inventario = buscarInventarioPorPokemonName(lista_inventario, pokemon_name, NULL);
	if(nuevo_inventario != NULL) {
		// Si ese pokemon ya está cargado
		nuevo_inventario->cantidad++;
	} else {
		// Si es un pokemon nuevo
		nuevo_inventario = malloc(sizeof(t_inventario));
		nuevo_inventario->pokemon = crearPokemon(pokemon_name);
		nuevo_inventario->cantidad = 1;

		list_add(lista_inventario, nuevo_inventario);
	}
}

// Saca el inventario de la lista, en caso de que no exista devuelve NULL
t_inventario* sacarPokemonEnListaDeInventario(t_list* lista_inventario, char* pokemon_name) {
	t_inventario* inventario;
	// Verifico que el pokemon no esté cargado
	int index;
	inventario = buscarInventarioPorPokemonName(lista_inventario, pokemon_name, &index);

	if(inventario != NULL) {
		if (inventario->cantidad > 1) {
			inventario->cantidad--;
		} else {
			list_remove(lista_inventario, index);
		}
	}

	return inventario;
}

t_inventario* buscarInventarioPorPokemonName(t_list* lista, char* pokemon_name, int* position) {
	int pos = 0;
	t_inventario* actual;
	actual = list_get(lista, pos);

	while (actual != NULL && strcmp(actual->pokemon->name, pokemon_name) != 0) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		pos++;
		actual = list_get(lista, pos);
	}

	if (position != NULL)
		*position = pos;

	return actual;
}

int cantidadDePokemonesEnInventario(t_list* inventario) {
	int cantidadTotal = 0;
	t_inventario* inv;

	for(int pos = 0; pos < list_size(inventario); pos++)
	{
		inv = list_get(inventario, pos);
		cantidadTotal += inv->cantidad;
	}

	return cantidadTotal;
}

int entrenadorAlMaximoDeCapacidad(t_entrenador* entrenador) {
	return cantidadDePokemonesEnInventario(entrenador->pokes_actuales) >= cantidadDePokemonesEnInventario(entrenador->pokes_objetivos);
}

int objetivoCumplidoSegunPokemon(t_pokemon* pokemon, t_list* actuales, t_list* objetivo) {
	t_inventario* inv_obj = buscarInventarioPorPokemonName(objetivo, pokemon->name, NULL);

	if (inv_obj != NULL) {
		t_inventario* inv_actual = buscarInventarioPorPokemonName(actuales, pokemon->name, NULL);
		return !(inv_actual == NULL || inv_actual->cantidad < inv_obj->cantidad);
	} else {
		return 1;	// Si no se tiene ese objetivo no se deberia llegar a este punto
	}
}

char* pokemonQueNoNecesiteYelOtroSi(t_entrenador* buscado, t_entrenador* necesitado) {
	t_list* pokemones_necesitados = pokemonesNecesitadosDe(necesitado);

	for (int i = 0; i < list_size(pokemones_necesitados); i++) {
		t_inventario* inv_pok = list_get(pokemones_necesitados, i);
		if (tienePokemonYNoLoNecesita(buscado, inv_pok->pokemon->name)) {
			return inv_pok->pokemon->name;
		}
	}

	return NULL;
}

// Devuelve una lista de t_inventario* con los pokemones que le falta para completar el objetivo
t_list* pokemonesNecesitadosDe(t_entrenador* entrenador) {
	return diferenciaDeInventarios(entrenador->pokes_objetivos, entrenador->pokes_actuales);
}

// Devuelve lista de t_inventario* con los pokemones que le sobren (no necesarios para el objetivo) al entrenador
t_list* pokemonesNoNecesariosDe(t_entrenador* entrenador) {
	return diferenciaDeInventarios(entrenador->pokes_actuales, entrenador->pokes_objetivos);
}

t_list* diferenciaDeInventarios(t_list* minuendo, t_list* sustraendo) {
	t_list* resultado = list_duplicate(minuendo);

	t_inventario* inv;

	for(int i = 0; i < list_size(sustraendo); i++) {
		inv = list_get(sustraendo, i);
		sacarPokemonEnListaDeInventario(resultado, inv->pokemon->name);
	}
	return resultado;
}

int tienePokemonYNoLoNecesita(t_entrenador* entrenador, char* pokemon_name) {
	return buscarInventarioPorPokemonName(pokemonesNoNecesariosDe(entrenador), pokemon_name, NULL) != NULL;
}

//////////////////////////////////////////
//				MOVIMIENTO				//
//////////////////////////////////////////


int distanciaA(t_coords* desde, t_coords* hasta) {
	int distX = abs(desde->posX - hasta->posX);
	int distY = abs(desde->posY - hasta->posY);

	return distX + distY;
}

// devuelve 1, 0 o -1 dependiendo del signo del numero
int signo(int n) {
	return (0 < n) - (n < 0);
}

void moverseAlobjetivo(t_entrenador* entrenador) {
	t_coords* pos = entrenador->posicion;
	t_pokemon_en_mapa* obj = entrenador->objetivo;

	int direccion = signo(obj->posicion->posX - pos->posX);
	log_debug(logger, "El entrenador %d va a buscar un %s en la posición x: %d y: %d", entrenador->id_entrenador, obj->pokemon->name, obj->posicion->posX, obj->posicion->posY);
	for (int x = pos->posX + direccion; pos->posX != obj->posicion->posX; x += direccion) {
		realizarCicloDeCPU();
		pos->posX = x;
		log_debug(logger, "El entrenador %d está en la posición x: %d y: %d", entrenador->id_entrenador, pos->posX, pos->posY);
	}

	direccion = signo(obj->posicion->posY - pos->posY);

	for (int y = pos->posY + direccion; pos->posY != obj->posicion->posY; y += direccion) {
		realizarCicloDeCPU();
		pos->posY = y;
		log_debug(logger, "El entrenador %d está en la posición x: %d y: %d", entrenador->id_entrenador, pos->posX, pos->posY);
	}
}


//////////////////////////////////////
//				EJECUCION			//
//////////////////////////////////////

void intentarAtraparPokemon(t_tcb* tcb) {
	log_debug(logger, "Entrenador %d va a enviar catch", tcb->entrenador->id_entrenador);
	enviarCatchPokemon(tcb->entrenador->objetivo, tcb);
	terminarDeEjecutar(tcb);
	log_debug(logger, "Entrenador %d se bloquea por esperar caught", tcb->entrenador->id_entrenador);
	bloquearPorEsperarCaught(tcb);
}

void *entrenadorMain(void* arg) {
	t_tcb* tcb = (t_tcb*)arg;
	t_entrenador* entrenador = tcb->entrenador;
	log_debug(logger, "Soy el entrenador %d", entrenador->id_entrenador);
	while(1){	// TODO proceso no esté en finalizado
		log_debug(logger, "Entrenador %d esperando para ejecutarse", entrenador->id_entrenador);
		sem_wait(&(tcb->sem_ejecucion));
		log_debug(logger, "Entrenador %d empieza a ejecutarse", entrenador->id_entrenador);

		// Moverse al objetivo
		moverseAlobjetivo(entrenador);
		log_debug(logger, "El entrenador %d llega a su objetivo", entrenador->id_entrenador);

		terminarDeEjecutar();
		log_debug(logger, "Entrenador %d va a intentar atrapar al pokemon", entrenador->id_entrenador);

		intentarAtraparPokemon(tcb);

		// intento atrapar y se bloquea

		/*	TODO: tengo que bloquearlo aca? o al recibir el caught
			sem_wait(&(tcb->sem_ejecucion));

			log_debug(logger, "Entrenador %d se va a bloquear por idle", entrenador->id_entrenador);
			terminarDeEjecutar(tcb);
			bloquearPorIdle(tcb);
		 *
		 * */
	}

	return NULL;
}
