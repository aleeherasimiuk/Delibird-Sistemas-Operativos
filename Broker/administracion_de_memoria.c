/*
 * administracion_de_memoria.c
 *
 *  Created on: 20 jun. 2020
 *      Author: utnso
 */


#include "administracion_de_memoria.h"

void* cache;

void iniciarMemoria(){

	allocarMemoria();
	algoritmoMemoria();
	algoritmoReemplazo();
	algoritmoParticionLibre();
	frecuenciaDeCompactacion();
	minimaParticion();
}

void allocarMemoria(){

	uint32_t bytes = config_get_int_value(config, BYTES_TO_ALLOC);
	cache = malloc(bytes);

}


void algoritmoMemoria(){

	char* algoritmo_memoria = config_get_string_value(config, MEMORIA);

	if(compare_string(algoritmo_memoria, "PARTICIONES")){
		memoria = PARTICIONES;
		return;
	}

	if(compare_string(algoritmo_memoria, "BS")){
		memoria = BUDDY_SYSTEM;
		return;
	}

	log_error(logger, "Algoritmo de administración de memoria incorrecto!");
	liberarCache();
	exit(1);
}



void algoritmoReemplazo(){

	char* algoritmo_reemplazo = config_get_string_value(config, REEMPLAZO);

	if(compare_string(algoritmo_reemplazo, "FIFO")){
		reemplazo = FIFO;
		return;
	}

	if(compare_string(algoritmo_reemplazo, "LRU")){
		memoria = LRU;
		return;
	}

	log_error(logger, "Algoritmo de reemplazo de memoria incorrecto!");
	liberarCache();
	exit(1);
}


void algoritmoParticionLibre(){

	char* algoritmo_particion_libre = config_get_string_value(config, PART_LIBRE);

	if(compare_string(algoritmo_particion_libre, "FF")){
		reemplazo = FIRST_FIT;
		return;
	}

	if(compare_string(algoritmo_particion_libre, "BF")){
		memoria = BEST_FIT;
		return;
	}

	log_error(logger, "Algoritmo de ajuste de memoria incorrecto!");
	liberarCache();
	exit(1);

}
void frecuenciaDeCompactacion(){
	freq_compact = config_get_int_value(config, FREQ_COMPACT);

	if(freq_compact > 0)
		return;

	log_error(logger, "Frecuencia de compactacion incorrecta");
	liberarCache();
	exit(1);

}
void minimaParticion(){

	min_part = config_get_int_value(config, MIN_PART);

	if(min_part > 0)
		return;

	log_error(logger, "Mínima partición incorrecta");
	liberarCache();
	exit(1);

}


void liberarCache(){
	free(cache);
}

int compare_string(char* mensaje_recv, char* mensaje) {
	return !strcmp(mensaje_recv, mensaje);
}


