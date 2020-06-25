/*
 * asignacion_de_memoria.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#include "asignacion_de_memoria.h"

sem_t sem_msg_data;
pthread_mutex_t mx_mem;
pthread_mutex_t mx_flag;
uint32_t next_flag = 0;
uint32_t compact;

void iniciarCola(){
	sem_init(&sem_msg_data, 0, 0);
	pthread_mutex_init(&mx_mem, NULL);
	pthread_mutex_init(&mx_flag, NULL);
	datos_para_guardar = queue_create();
}

void* guardarEnMemoria(){

	while(1){

		sem_wait(&sem_msg_data);
		pthread_mutex_lock(&mx_mem);

		compact = freq_compact; /*https://bit.ly/2BEfVk2*/
		t_paquete* data = queue_pop(datos_para_guardar);
		memory_block_t* particion = asignarUnaParticion(data -> buffer -> stream_size);
		copiarDatos(particion, data);
		relacionarBloqueConMensaje(particion, data);
		log_debug(logger, "Guardé un dato en una particion de tamaño: %d, para un dato de tamaño: %d", particion -> data -> size, data -> buffer -> stream_size);
		liberarPaquete(data);
		//estadoDeLaMemoria();
		pthread_mutex_unlock(&mx_mem);

	}

}



memory_block_t* asignarUnaParticion(uint32_t size){

	uint32_t tamano_particion = max(size, min_part);
	memory_block_t* bloque = NULL;

	if(part_libre == FIRST_FIT){
		bloque = first_fit(tamano_particion);
	}

	if(part_libre == BEST_FIT){
		bloque = best_fit(tamano_particion);
	}

	if(bloque == NULL){
		estadoDeLaMemoria();
		log_debug(logger, "Tengo que acomodar la memoria");
		return acomodarMemoria(size);
	}

	return particionar(bloque, tamano_particion);
}

uint32_t max(uint32_t a, uint32_t b){
	return a > b? a : b;
}

void copiarDatos(memory_block_t* destino, t_paquete* paquete){
	memcpy(destino -> data -> base, paquete -> buffer -> stream, paquete -> buffer -> stream_size);
	destino -> data -> status = OCUPADO;


}

void relacionarBloqueConMensaje(memory_block_t* particion, t_paquete* data){

	//pthread_mutex_lock(&msg_mx); obtenerMensaje ya tiene su propio lock.
	clientes_por_mensaje_t* cxm = obtenerMensaje(data -> id);
	cxm -> memory_block = particion;
	pthread_mutex_lock(&mx_flag);
	cxm -> memory_block -> data -> flag = next_flag++;
	pthread_mutex_unlock(&mx_flag);

	particion -> data -> msg_id = cxm -> id_mensaje;
}

void liberarPaquete(t_paquete* data){
	free(data -> buffer -> stream);
	free(data -> buffer);
	free(data);
}

void* acomodarMemoria(uint32_t size){

	if(compact == 0){
		log_debug(logger, "Debo compactar");
		compactar();
	} else {
		librerarUnBloque();
		compact--;
	}

	/**/

	return asignarUnaParticion(size);

}

void estadoDeLaMemoria(){

	memory_block_t* mem_block = memory;
	int i = 0;

	while(mem_block != NULL){

		log_debug(logger, "Partición número: %d \nInicio: %d \nTamaño: %d \nEstado: %d \nFlag: %d \nSiguiente: %d\n\n",
				i++,
				&(mem_block -> data -> base),
				mem_block -> data -> size,
				mem_block -> data -> status,
				mem_block -> data -> flag,
				mem_block -> next == NULL? 0: mem_block -> next);

//		mem_hexdump(&(mem_block -> data -> base), mem_block -> data -> size);

		mem_block = mem_block -> next;
	}

}
