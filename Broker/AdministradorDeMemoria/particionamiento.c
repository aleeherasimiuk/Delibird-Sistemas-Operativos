/*
 * particionamiento.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */


#include "particionamiento.h"

memory_block_t* first_fit(uint32_t size){

	memory_block_t* mem_block = memory;

	while(mem_block != NULL){

		if(puedeEntrar(mem_block -> data, size))
			return mem_block;

		mem_block = mem_block -> next;
	}


	return NULL;

}

memory_block_t* best_fit(uint32_t size){

	memory_block_t* mem_block = memory;
	memory_block_t* last = NULL;

	while(mem_block != NULL){

		if(puedeEntrar(mem_block -> data, size))
			if(mejorAjuste(last, mem_block))
				last = mem_block;

		mem_block = mem_block -> next;

	}

	// NULL si no encuentra
	return last;
}

memory_block_t* particionar(memory_block_t* mem_block, uint32_t size){

	uint32_t desperdicio = (mem_block -> data -> size) - size;
	memory_block_t* next = mem_block -> next;

	memory_block_t* bloque_desperdicio = malloc(sizeof(memory_block_t));

	bloque_desperdicio -> previous = mem_block;
	bloque_desperdicio -> data = malloc(sizeof(memory_info_t));
	bloque_desperdicio -> data -> base = (mem_block -> data -> base) + size;
	bloque_desperdicio -> data -> size = desperdicio;
	bloque_desperdicio -> data -> status = LIBRE;
	bloque_desperdicio -> next = next;

	mem_block -> next = bloque_desperdicio;
	mem_block -> data -> size = size;

	return mem_block;

}

int puedeEntrar(memory_info_t* info, uint32_t size){
	return info -> status == LIBRE && info -> size > size;
}


int mejorAjuste(memory_block_t* best, memory_block_t* actual){

	return best == NULL || actual -> data -> size < best -> data -> size;

}
