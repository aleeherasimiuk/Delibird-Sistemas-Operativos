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

#include "../Utils/mensajes.h"
#include "var_globales.h"

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
	t_coords* destino;
	t_list* pokes_actuales;
	t_list* pokes_objetivos;
} t_entrenador;

typedef struct {
	t_entrenador* entrenador;
	//pthread_t thread; // TODO Referencia al hilo=???
	pthread_mutex_t mutex_ejecucion; // Solo se activa cuando pasa a exec
	// TODO Agregar info para los distintos algoritmos de planificacion
} t_tcb;

// FIN ESTRUCTURAS

// FUNCIONES PARA CREACION

/*
 * Crea un t_coords a partir de la posiciones de la config, formato "x|y"
 */
// Inicializacion
t_coords* crearCoordenadas(char*);
t_list* crearListaDeInventario(char*, t_list*);
void cargarPokemonEnListaDeInventario(t_list*, char*);
t_inventario* buscarInventarioPorPokemonName(t_list*, char*);
int distanciaA(t_coords*, t_coords*);

// Estados
int indexOf(t_tcb* tcb, t_list* lista);
void* sacarDeLista(t_tcb* tcb, t_list* lista);
void cambiarDeLista(t_tcb* tcb, t_list* lista_actual, t_list* lista_destino);

// Ejecución
void *entrenadorMain(void*);

#endif /* ENTRENADORES_H_ */
