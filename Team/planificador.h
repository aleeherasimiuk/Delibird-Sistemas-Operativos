/*
 * planificador.h
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#ifndef PLANIFICADOR_H_
#define PLANIFICADOR_H_

#include <pthread.h>
#include <semaphore.h>
#include <commons/string.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>

#include "conexionesTeam.h"
#include "entrenadores.h"
#include "var_globales.h"

//		STRUCTS
typedef struct {
	t_pokemon* pokemon;
	t_coords* posicion;
	int	disponible;	// Si algun entrenador no fue planificado para buscarlo
} t_pokemon_en_mapa;

t_pokemon_en_mapa* crearPokemonEnMapa(t_pokemon* pokemon, t_coords* posicion);

//      INICIALIZACION
void cargarEntrenadores(void);
void enviarGetsAlBroker(void);
void iniciarPlanificador(void);

//		EJECUCION
	// Planificacion largo plazo
t_tcb* entrenadorMasCercanoA(t_pokemon_en_mapa* pokemon, t_list* lista);
void *mandarABuscarPokemones(void);


void realizarCicloDeCPU(void);
void realizarXCiclosDeCPU(int cant_ciclos);

#endif /* PLANIFICADOR_H_ */
