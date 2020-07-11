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

t_pokemon_en_mapa* crearPokemonEnMapa(t_pokemon* pokemon, t_coords* posicion);

//      INICIALIZACION
void cargarEntrenadores(void);
void enviarGetsAlBroker(void);
void iniciarPlanificador(void);

// Estados
int indexOf(t_tcb* tcb, t_list* lista);
void* sacarDeLista(t_tcb* tcb, t_list* lista);
void agregarALista(t_tcb* tcb, t_list* lista);
void cambiarDeLista(t_tcb* tcb, t_list* lista_actual, t_list* lista_destino);
void cambiarListaSegunCapacidad(t_tcb* tcb);

void ponerAEjecutarEntrenador(t_tcb* tcb);
void terminarDeEjecutar(void);

void bloquearPorIdle(t_tcb* tcb);
void bloquearPorEsperarCaught(t_tcb* tcb);

// Planificacion largo plazo
t_tcb* entrenadorMasCercanoA(t_pokemon_en_mapa* pokemon, t_list** lista);
void *mandarABuscarPokemones(void*);

// Planificacion corto plazo
void *planificadorCortoPlazo(void* _);

void planificarSegunFifo(void);

void esperarCpuLibre(void);


//		EJECUCION
void realizarCicloDeCPU(void);
void realizarXCiclosDeCPU(int cant_ciclos);


// 		OBJETIVOS + MAPA
int pokemonNecesario(t_pokemon*);
void agregarPokemonAlMapa(t_pokemon*, t_coords*);
void buscarPokemonAuxiliarYPasarAlMapa(char* pokemon_name);

#endif /* PLANIFICADOR_H_ */
