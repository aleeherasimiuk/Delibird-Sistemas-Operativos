/*
 * entrenadores.c
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#include"entrenadores.h"

t_coords* crearCoordenadas(char* string_coord) {
	char separador = '|';
	char** coords_array = string_split(string_coord, &separador);
	t_coords* coords_nuevas = malloc(sizeof(t_coords));

	coords_nuevas->posX = atoi(coords_array[0]); // atoi transforma de char * a int
	coords_nuevas->posY = atoi(coords_array[1]);
	free(coords_array);
	return coords_nuevas;
}

t_list* crearListaDeInventario(char* pokemones_string) {
	char separador = '|';
	char** pokemones_array = string_split(pokemones_string, &separador);
	t_list* lista_inventario = list_create();

	t_inventario* nuevo_inventario;

	int i = 0;
	while(pokemones_array[i] != NULL) {
		char* pokemon_name = pokemones_array[i];
		// Verifico que el pokemon no esté cargado
		nuevo_inventario = findInventarioByPokemonName(lista_inventario, pokemon_name);
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

		i++;
	}
	return lista_inventario;
}

t_inventario* findInventarioByPokemonName(t_list* list, char* pokemon_name) {
	int position = 0;
	t_inventario* actual;
	actual = list_get(list, position);

	while (actual != NULL && strcmp(actual->pokemon->name, pokemon_name) != 0) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		position++;
		actual = list_get(list, position);
	}

	return actual;
}


