/*
 * asignacion_de_memoria.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#include "asignacion_de_memoria.h"

sem_t sem_msg_data;
pthread_mutex_t mx_mem;

void iniciarCola(){
	sem_init(&sem_msg_data, 0, 0);
	pthread_mutex_init(&mx_mem, NULL);
	datos_para_guardar = queue_create();
}

void* guardarEnMemoria(){

	log_debug(logger, "Algoritmo de partición libre: %d", part_libre);
	log_debug(logger, "Algoritmo de reemplazo: %d", reemplazo);
	log_debug(logger, "Algoritmo de memoria: %d", memoria);


	while(1){

		sem_wait(&sem_msg_data);
		pthread_mutex_lock(&mx_mem);

		t_paquete* data = queue_pop(datos_para_guardar);
		memory_block_t* particion = asignarUnaParticion(data -> buffer -> stream_size);
		if(particion == NULL){
			log_debug(logger, "NULL: size: %d", data -> buffer -> stream_size);
		} else {

		log_debug(logger, "Voy a guardar un dato en una particion de tamaño: %d, para un dato de tamaño: %d", particion -> data -> size, data -> buffer -> stream_size);
		}

		pthread_mutex_unlock(&mx_mem);

	}

}



void* asignarUnaParticion(uint32_t size){

	uint32_t tamano_particion = max(size, min_part);
	memory_block_t* bloque = NULL;

	if(part_libre == FIRST_FIT){
		bloque = first_fit(tamano_particion);
	}

	if(part_libre == BEST_FIT){
		bloque = best_fit(tamano_particion);
	}

	if(bloque == NULL){
		// Compactar y/o borrar
	}

	return particionar(bloque, tamano_particion);
}

uint32_t max(uint32_t a, uint32_t b){
	return a > b? a : b;
}
