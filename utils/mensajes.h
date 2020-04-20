/*
 * mensajes.h
 *
 *  Created on: 19 abr. 2020
 *      Author: Nico Rickert
 */

#ifndef MENSAJES_H_
#define MENSAJES_H_

#include<stdlib.h>
#include<stdint.h>

typedef enum {
	NEW_POKEMON,
	APPEARED_POKEMON,
	CATCH_POKEMON,
	CAUGHT_POKEMON,
	GET_POKEMON,
	LOCALIZED_POKEMON
} message_type;

typedef struct {
	uint32_t name_size;
	char* name;
} t_pokemon;

typedef struct {
	uint32_t posx;
	uint32_t posy;
} t_coords;

// STRUCTS DE MENSAJES


/* Este mensaje tendrá el nombre del Pokemon a enviar, las coordenadas de la posición donde se encuentra y
 * la cantidad de pokémon de esta especie que habra en dicha posicion.
 */

typedef struct {
	t_pokemon pokemon;
	t_coords coords;
	uint32_t cantidad;
} t_new_pokemon;

// Este mensaje tendrá el nombre del pokemon y para indicar la posición en X y en Y.

typedef struct {
	t_pokemon pokemon;
	t_coords coords;
} t_appeared_pokemon;

// Este mensaje tendrá el nombre del pokemon y la posición en X y en Y.

typedef struct {
	t_pokemon pokemon;
	t_coords coords;
} t_catch_pokemon;

// Este mensaje tendrá un valor para indicar si se pudo o no atrapar al pokemon (0 o 1)

typedef struct {
	uint32_t status;
} t_caught_pokemon;

// Este mensaje tendrá el nombre del pokemon.

typedef struct {
	t_pokemon pokemon;
} t_get_pokemon;

/* Este mensaje tendrá el nombre del pokémon, un entero para la cantidad de pares de coordenadas
 * y los pares de coordenadas donde se encuentra el mismo.
 */

typedef struct {
	t_pokemon pokemon;
	uint32_t cant_coords;
	t_coords* coords_array;
} t_localized_pokemon;

// FIN STRUCTS MENSAJES

// MENSAJE: Struct que es lo que se va a enviar
// type (tipo de mensaje (ENUM)), data: un puntero al struct correspondiente del tipo del mensaje

typedef struct {
	message_type type;
	void* data;
} t_message;

#endif /* MENSAJES_H_ */
