/*
 * administracion_de_memoria.c
 *
 *  Created on: 20 jun. 2020
 *      Author: utnso
 */


#include "administracion_de_memoria.h"

void* cache;
memory_block_t* memory;
alg_memoria_t memoria;
alg_reemplazo_t reemplazo;
alg_part_libre_t part_libre;
uint32_t freq_compact;
uint32_t min_part;

void iniciarMemoria(){

	cache        = allocarMemoria();
	memoria      = algoritmoMemoria();
	reemplazo    = algoritmoReemplazo();
	part_libre   = algoritmoParticionLibre();
	freq_compact = frecuenciaDeCompactacion();
	min_part     = minimaParticion();

	iniciarCola();

	log_debug(logger, "Algoritmo de partición libre: %d", part_libre);
	pthread_t memory_admin;
	pthread_create(&memory_admin, NULL, guardarEnMemoria, NULL);
	pthread_detach(memory_admin);
}

void* allocarMemoria(){

	uint32_t bytes = config_get_int_value(config, BYTES_TO_ALLOC);
	void* _cache = malloc(bytes);

	memory = malloc(sizeof(memory_block_t));
	memory -> previous 		 = NULL;

	memory -> data = malloc(sizeof(memory_info_t));
	memory -> data -> base   = _cache;
	memory -> data -> size   = bytes;
	memory -> data -> status = LIBRE;

	memory -> next   		 = NULL;

	return _cache;

}


int algoritmoMemoria(){

	char* algoritmo_memoria = config_get_string_value(config, MEMORIA);

	if(compare_string(algoritmo_memoria, "PARTICIONES"))
		return PARTICIONES;

	if(compare_string(algoritmo_memoria, "BS"))
		return BUDDY_SYSTEM;

	errorConfig(MEMORIA);
	return -1;
}



int algoritmoReemplazo(){

	char* algoritmo_reemplazo = config_get_string_value(config, REEMPLAZO);

	if(compare_string(algoritmo_reemplazo, "FIFO"))
		return FIFO;

	if(compare_string(algoritmo_reemplazo, "LRU"))
		return LRU;


	errorConfig(REEMPLAZO);
	return -1;
}


int algoritmoParticionLibre(){

	char* algoritmo_particion_libre = config_get_string_value(config, PART_LIBRE);

	if(compare_string(algoritmo_particion_libre, "FF"))
		return FIRST_FIT;

	if(compare_string(algoritmo_particion_libre, "BF"))
		return BEST_FIT;

	errorConfig(PART_LIBRE);
	return -1;
}

int frecuenciaDeCompactacion(){
	int freq_compact = config_get_int_value(config, FREQ_COMPACT);

	if(freq_compact > 0)
		return freq_compact;

	errorConfig(FREQ_COMPACT);
	return -1;
}

int minimaParticion(){

	int min_part = config_get_int_value(config, MIN_PART);

	if(min_part > 0)
		return min_part;

	errorConfig(MIN_PART);
	return -1;
}


void liberarCache(){
	free(cache);
}

int compare_string(char* mensaje_recv, char* mensaje) {
	return !strcmp(mensaje_recv, mensaje);
}

void errorConfig(char* error){
	log_error(logger, "Valor de configuración de %s incorrecto", error);
	liberarCache();
	exit(1);
}
