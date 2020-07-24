/*
 * administracion_de_memoria.h
 *
 *  Created on: 20 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_ADMINISTRACION_DE_MEMORIA_H_
#define BROKER_ADMINISTRADORDEMEMORIA_ADMINISTRACION_DE_MEMORIA_H_

#include<stdlib.h>
#include<stdint.h>
#include<commons/config.h>
#include<math.h>
#include "../var_globales.h"
#include"asignacion_de_memoria.h"

#define MEMORIA "ALGORITMO_MEMORIA"
#define REEMPLAZO "ALGORITMO_REEMPLAZO"
#define BYTES_TO_ALLOC "TAMANO_MEMORIA"
#define PART_LIBRE "ALGORITMO_PARTICION_LIBRE"
#define FREQ_COMPACT "FRECUENCIA_COMPACTACION"
#define MIN_PART "TAMANO_MINIMO_PARTICION"
#define DUMP_PATH "DUMP_CACHE_PATH"

void* cache;

void iniciarMemoria();
void* allocarMemoria();
void liberarCache();
int algoritmoMemoria();
int algoritmoReemplazo();
int algoritmoParticionLibre();
int frecuenciaDeCompactacion();
int minimaParticion();
char* rutaDump();
void liberarCache();

int compare_string(char*, char*);
void errorConfig(char*);
int potenciaDeDos(double n);



#endif /* BROKER_ADMINISTRADORDEMEMORIA_ADMINISTRACION_DE_MEMORIA_H_ */
