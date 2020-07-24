/*
 * compactacion.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "compactacion.h"

void compactar(){

	log_info(logger, "Ejecutando compactación");

	/*Proceso de Compactación
	 *
	 * 1° Creo un bloque de memoria --> Nueva estructura administrativa
	 * 2° Seteo sus valores por default
	 * 3° Mantengo variables auxiliares para guardar
	 * 		a) El bloque actual
	 * 		b) El bloque anterior
	 * 		c) El bloque a compactar
	 *
	 * 4° Si existe un bloque y está ocupado --> Paso 5. Otro caso: Paso 13
	 * 5° Particiono el bloque actual, para que ocupe lo mismo que los datos
	 * 6° Muevo la memoria de su lugar original al nuevo lugar asignado
	 * 7° Asigno los datos necesarios a la estructura administrativa del bloque actual
	 * 8° Actualizo la posición del bloque en la lista de mensajes.
	 * 9° Este bloque pasa a ser el anterior
	 * 10° El próximo bloque pasa a ser el actual
	 * 11° Actualizo la variable del bloque a compactar con el siguiente.
	 * 12° Vuelta al paso 4.
	 * 13° Libero la estructura administrativa antigua
	 * 14° Reemplazo la estructura administrativa por la nueva compactada.
	 *
	 *
	 *
	 * */

	memory_block_t* mem_block = memory;
	memory_block_t* compacted_memory = malloc(sizeof(memory_block_t));

	valoresPorDefault(compacted_memory);

	memory_block_t* last = NULL;
	memory_block_t* actual = compacted_memory;

	while(mem_block != NULL){

		if(mem_block -> data -> status == OCUPADO){
			actual = particionar(actual, mem_block -> data -> size);
			memmove(actual -> data -> base, mem_block -> data -> base, mem_block -> data -> size);
			moverValoresAdministrativos(mem_block, actual);
			actualizarMensaje(actual, mem_block -> data -> msg_id);
			actual -> previous = last;
			last = actual;
			actual = actual -> next;
		}

		mem_block = mem_block -> next;
	}

	liberarMemoriaVieja();
	memory = compacted_memory;
	estadoDeLaMemoria();
	log_info(logger, "Se ha finalizado la compactación");
}

void liberarMemoriaVieja(){
	memory_block_t* memoria_vieja = memory;
	memory_block_t* siguiente = NULL;

	while(memoria_vieja != NULL){

		siguiente = memoria_vieja -> next;
		free(memoria_vieja -> data);
		free(memoria_vieja);
		memoria_vieja = siguiente;

	}
}

void actualizarMensaje(memory_block_t* new_block, uint32_t id){

	int i = 0;
	clientes_por_mensaje_t* cli = obtenerMensajeYPosicion(id, &i);
	if(new_block == NULL && cli != NULL){
		list_destroy_and_destroy_elements(cli -> suscriptores, free);
		pthread_mutex_lock(&msg_mx);
		list_remove_and_destroy_element(mensajes, i, free);
		pthread_mutex_unlock(&msg_mx);
		return;

	}

	if(cli != NULL){
		cli -> memory_block = new_block;
	}

}

void valoresPorDefault(memory_block_t* mem_block){
	mem_block -> previous = NULL;
	mem_block -> next = NULL;
	mem_block -> data = malloc(sizeof(memory_info_t));
	mem_block -> data -> base = cache;
	mem_block -> data -> flag = 0;
	mem_block -> data -> size = bytes;
	mem_block -> data -> fragmentacion = 0;
	mem_block -> data -> status = LIBRE;
}

void moverValoresAdministrativos(memory_block_t* antiguo_bloque, memory_block_t* nuevo_bloque){
	nuevo_bloque -> data -> flag	= antiguo_bloque -> data -> flag;
	nuevo_bloque -> data -> size    = antiguo_bloque -> data -> size;
	nuevo_bloque -> data -> msg_id  = antiguo_bloque -> data -> msg_id;
	nuevo_bloque -> data -> status  = OCUPADO;
	nuevo_bloque -> data -> fragmentacion = antiguo_bloque -> data -> fragmentacion;
}






