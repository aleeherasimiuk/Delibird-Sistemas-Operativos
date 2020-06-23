/*
 * compactacion.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "compactacion.h"


void compactar(){

	memory_block_t* mem_block = memory;
	memory_block_t* compacted_memory = malloc(sizeof(memory_block_t));
	compacted_memory -> previous = NULL;
	compacted_memory -> next = NULL;
	compacted_memory -> data = malloc(sizeof(memory_info_t));
	compacted_memory -> data -> base = cache;
	compacted_memory -> data -> flag = 0;
	compacted_memory -> data -> size = bytes;
	printf("Size de caché: %d\n", compacted_memory -> data -> size);
	compacted_memory -> data -> status = LIBRE;

	memory_block_t* actual = compacted_memory;

	while(mem_block != NULL){

		if(mem_block -> data -> status == OCUPADO){
			actual = particionar(actual, mem_block -> data -> size);
			memcpy(actual -> data -> base, mem_block -> data -> base, mem_block -> data -> size);
			actual -> data -> flag = mem_block -> data -> flag;
			actual -> data -> status = OCUPADO;
			actual -> data -> size = mem_block -> data -> size;
			actual = actual -> next;
		}

		mem_block = mem_block -> next;

	}

	memory = compacted_memory;
	estadoDeLaMemoria();
}


