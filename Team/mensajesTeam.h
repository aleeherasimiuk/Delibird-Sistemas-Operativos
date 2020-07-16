/*
 * mensajesTeam.h
 *
 *  Created on: 7 jul. 2020
 *      Author: utnso
 */

#ifndef MENSAJESTEAM_H_
#define MENSAJESTEAM_H_

#include<stdint.h>

#include "entrenadores.h"

// Para el catch, al recibir el caught correspondiente, se activa el tcb
typedef struct {
	uint32_t id;
	t_tcb* tcb;
} t_mensaje_catch;


void inciarListasMensajes (void);

void addGetEnviado(uint32_t id);
void addPokemonRecibido(char* pokemon_name);
void addCatchEnviado(uint32_t id, t_tcb* tcb);

int getEnviadoConID(uint32_t id, int* index);
int pokemonYaRecibido(char* pokemon_name);
t_mensaje_catch* buscarCatchEnviadoSegunIDMensaje(uint32_t id, uint32_t* index);
t_tcb* traerTcbDelCatchConID(uint32_t id);
int catchPendientes(void);

void eliminarGetEnviado(uint32_t id);
void eliminarCatchEnviado(uint32_t id);

#endif /* MENSAJESTEAM_H_ */
