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
#include <semaphore.h>

#include "../Utils/mensajes.h"
#include "var_globales.h"


typedef struct {
	t_pokemon* pokemon;
	t_coords* posicion;
} t_pokemon_en_mapa;

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
	t_pokemon_en_mapa* objetivo;
	t_list* pokes_actuales;
	t_list* pokes_objetivos;
} t_entrenador;

typedef struct t_intercambio {
	struct t_tcb* tcb;
	char* mi_pokemon;
	char* su_pokemon;
} t_intercambio;

typedef struct t_tcb {
	t_intercambio* intercambio;
	t_entrenador* entrenador;
	pthread_cond_t exec_cond;
	pthread_mutex_t exec_mutex;
	int ejecucion;
	int finalizado;
	// TODO Agregar info para los distintos algoritmos de planificacion
} t_tcb;

// FIN ESTRUCTURAS


// INCLUDES QUE NECESITAN STRUCTS DE ENTRENADORES
#include "utilsTeam.h"
#include "planificador.h"
#include "conexionesTeam.h"

// FUNCIONES PARA CREACION

/*
 * Crea un t_coords a partir de la posiciones de la config, formato "x|y"
 */
// Inicializacion
t_coords* crearCoordenadas(char*);

// Inventario
t_list* crearListaDeInventario(char*, t_list*);
void cargarPokemonEnListaDeInventario(t_list*, char*);
void sacarPokemonEnListaDeInventario(t_list* lista_inventario, char* pokemon_name);
t_inventario* buscarInventarioPorPokemonName(t_list*, char*, int*);

int cantidadDePokemonesEnInventario(t_list* inventario);
t_list* clonarListaInventario (t_list* lista);
int entrenadorAlMaximoDeCapacidad(t_entrenador* entrenador);
int entrenadorCumpleObjetivo(t_entrenador* entrenador);
int seCumplenTodosLosObjetivos(t_list* actuales, t_list* objetivos);
int objetivoCumplidoSegunPokemon(t_pokemon* pokemon, t_list* actuales, t_list* objetivo);

char* pokemonQueNoNecesiteYelOtroSi(t_entrenador* buscado, t_entrenador* necesitado);
t_list* pokemonesNecesitadosDe(t_entrenador* entrenador);
t_list* pokemonesNoNecesariosDe(t_entrenador* entrenador);
t_list* diferenciaDeInventarios(t_list* minuendo, t_list* sustraendo);
int tienePokemonYNoLoNecesita(t_entrenador* entrenador, char* pokemon_name);

// Movimiento
int distanciaA(t_coords*, t_coords*);
int signo(int n);
void moverseAlobjetivo(t_tcb* pos_actual, t_coords* posicion_destino, uint32_t id_entrenador);

// Ejecución
void intentarAtraparPokemon(t_tcb* tcb);
void realizarIntercambio(t_tcb* tcb);
void *entrenadorMain(void*);
void verificarSiTieneQueEjecutar(t_tcb* tcb);
#endif /* ENTRENADORES_H_ */
