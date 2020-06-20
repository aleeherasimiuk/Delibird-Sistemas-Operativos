/*
 * administracion_de_memoria.h
 *
 *  Created on: 20 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRACION_DE_MEMORIA_H_
#define BROKER_ADMINISTRACION_DE_MEMORIA_H_

#include<stdint.h>
#include<commons/config.h>
#include "var_globales.h"

#define MEMORIA "ALGORITMO_MEMORIA"
#define REEMPLAZO "ALGORITMO_REEMPLAZO"
#define BYTES_TO_ALLOC "TAMANO_MEMORIA"
#define PART_LIBRE "ALGORITMO_PARTICION_LIBRE"
#define FREQ_COMPACT "FRECUENCIA_COMPACTACION"
#define MIN_PART "TAMANO_MINIMO_PARTICION"

typedef enum{
	PARTICIONES,
	BUDDY_SYSTEM
} alg_memoria_t;

typedef enum{
	FIFO,
	LRU
} alg_reemplazo_t;

typedef enum{
	FIRST_FIT,
	BEST_FIT
} alg_part_libre_t;

void* cache;
alg_memoria_t memoria;
alg_reemplazo_t reemplazo;
alg_part_libre_t part_libre;
uint32_t freq_compact;
uint32_t min_part;

void allocarMemoria();
void liberarCache();
void allocarMemoria();
void algoritmoMemoria();
void algoritmoReemplazo();
void algoritmoParticionLibre();
void frecuenciaDeCompactacion();
void minimaParticion();

int compare_string(char*, char*);



#endif /* BROKER_ADMINISTRACION_DE_MEMORIA_H_ */
