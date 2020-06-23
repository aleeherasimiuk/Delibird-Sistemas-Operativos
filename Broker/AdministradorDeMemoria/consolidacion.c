/*
 * consolidacion.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "consolidacion.h"

void consolidar(memory_block_t* bloque_eliminado){

	memory_block_t* bloque_anterior = bloque_eliminado -> previous;
	memory_block_t* bloque_siguiente = bloque_eliminado -> next;

	if(bloque_anterior -> data -> status == LIBRE){
		memory_block_t* nuevo_bloque = merge(bloque_anterior, bloque_eliminado);

		if(bloque_siguiente -> data -> status == LIBRE)
			merge(nuevo_bloque, bloque_siguiente);


	} else if(bloque_siguiente -> data -> status == LIBRE)
		merge(bloque_eliminado, bloque_siguiente);



}

memory_block_t* merge(memory_block_t* fst, memory_block_t* snd){
	fst -> next = snd -> next;
	fst -> data -> size = (fst -> data -> size) + (snd -> data -> size);
	free(snd -> data);
	free(snd);

	return fst;
}
