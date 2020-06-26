/*
 * liberacion_memoria.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "liberacion_memoria.h"

void librerarUnBloque(){

	memory_block_t* bloque_a_eliminar =  bloqueAEliminar();
	bloque_a_eliminar -> data -> status = LIBRE;
	log_debug(logger, "El bloque a eliminar se encuentra: %d", bloque_a_eliminar -> data -> status);
	consolidar(bloque_a_eliminar);
}


memory_block_t* bloqueAEliminar(){

	memory_block_t* mem_block = memory;
	memory_block_t* a_eliminar = NULL;

	while(mem_block != NULL){
		if(mem_block -> data -> status == OCUPADO)
			if(eliminable(mem_block, a_eliminar))
				a_eliminar = mem_block;

		mem_block = mem_block -> next;
	}

	return a_eliminar;

}

int eliminable(memory_block_t* mem_block, memory_block_t* a_eliminar){
	return a_eliminar == NULL || mem_block -> data -> flag < a_eliminar -> data -> flag;
}

