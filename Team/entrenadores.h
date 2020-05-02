/*
 * entrenadores.h
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#ifndef ENTRENADORES_H_
#define ENTRENADORES_H_

#include <stdio.h>
#include <string.h>
#include <commons/string.h>
#include <commons/collections/list.h>

#include "var_globales.h"
#include "../utils/mensajes.h"

// STRUCT ENTRENADOR

/*
 * t_inventario: me guarda un pokemon y una cantidad de ese pokemon
 */
typedef struct {
	t_pokemon* pokemon;
	uint32_t cantidad;
} t_inventario;

/*
 * t_entrenador:
 * id_entrenador: id para identificar al entrenador dentro del sistema
 * posicion: posicion del entrenador dentro del mapa
 * pokes_actuales: lista de punteros a t_inventario de los pokemons actuales que tiene
 * pokes_objetivos: lista de punteros a t_inventario que necesita obtener
 */
typedef struct {
	uint32_t id_entrenador;
	t_coords* posicion;
	t_list* pokes_actuales;
	t_list* pokes_objetivos;
} t_entrenador;

// FIN ESTRUCTURAS

// FUNCIONES PARA CREACION

/*
 * Crea un t_coords a partir de la posiciones de la config, formato "x|y"
 */
t_coords* crearCoordenadas(char*);
t_list* crearListaDeInventario(char*);
t_inventario* findInventarioByPokemonName(t_list* list, char* pokemon_name);

#endif /* ENTRENADORES_H_ */
