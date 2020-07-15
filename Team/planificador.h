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
#include "deadlock.h"

t_pokemon_en_mapa* crearPokemonEnMapa(t_pokemon* pokemon, t_coords* posicion);

//      INICIALIZACION
void iniciarPlanificador(void);
void cargarEntrenadores(void);
void enviarGetsAlBroker(void);

// Estados
void esperarAQueFinalicenLosEntrenadores(void);
int indexOf(t_tcb* tcb, t_cola_planificacion* lista);
void sacarDeCola(t_tcb* tcb, t_cola_planificacion* lista);
void agregarACola(t_tcb* tcb, t_cola_planificacion* lista);
void cambiarDeCola(t_tcb* tcb, t_cola_planificacion* lista_actual, t_cola_planificacion* lista_destino);
void cambiarColaSegunCapacidad(t_tcb* tcb);
void cambiarColaSegunObjetivo(t_tcb* tcb, t_cola_planificacion* lista_actual);

void ponerAEjecutarEntrenador(t_tcb* tcb);
t_tcb* terminarDeEjecutar(void);

void bloquearPorIdle(t_tcb* tcb);
void bloquearPorEsperarCaught(t_tcb* tcb);

// Planificacion largo plazo
t_tcb* entrenadorMasCercanoA(t_pokemon_en_mapa* pokemon, t_cola_planificacion** lista);
void *mandarABuscarPokemones(void*);

// Planificacion corto plazo
void *planificadorCortoPlazo(void* _);
void esperarCpuLibre(void);

	// FIFO
void planificarSegunFifo(void);
	// RR
void planificarSegunRR(void);
void vaciarQuantum(void);
	// SJF
void planificarSegunSJFSD(void);
t_tcb* entrenadorConMenorEstimacion(void);
void calcularEstimacion(t_tcb* tcb);
void actualizarValoresSJF(t_tcb* tcb);

//		EJECUCION
void realizarCicloDeCPU(void);


// 		OBJETIVOS + MAPA
int pokemonNecesario(t_pokemon*);
void agregarPokemonAlMapa(t_pokemon*, t_coords*);
void buscarPokemonAuxiliarYPasarAlMapa(char* pokemon_name);
int teamAlMaximoDeCapacidad(void);
void* verificarSiTeamTerminoDeCapturar(void*);

#endif /* PLANIFICADOR_H_ */
