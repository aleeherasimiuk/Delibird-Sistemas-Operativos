/*
 * buddy_system.c
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */


#include "buddy_system.h"

/*
 * Algoritmo de reemplazo BUDDY SYSTEM
 *
 * 1° Divido el tamaño del bloque asignado por 2.
 * 2° Si los datos entran particiono el bloque en mitades.
 * 3° Verifico si puedo seguir dividiendo, volviendo al paso 1. Si no puedo continuar retorno el bloque particionado.
 *
 *
 * */


/*                       			 256 Bytes
 *   32 Bytes   32 Bytes     64 Bytes               	128 Bytes
 * *-------------------------------------------------------------------------------*
 * * 		 |  		 |           	 |							               *
 * * 	     |	     	 | 				 |										   *
 * * 		 |		     |				 |								     	   *
 * *   DATO	 |		     |				 |								     	   *
 * * 30 Bytes|		     |				 |		  							       *
 * *  		 |		     |				 |									       *
 * *  		 |		     |				 |									       *
 * *-------------------------------------------------------------------------------*
 * */

memory_block_t* buddy_system(memory_block_t* mem_block, uint32_t size){

	int division = mem_block -> data -> size / 2;

	if(division >= size){
		memory_block_t* new_block = particionar(mem_block, division);
		return buddy_system(new_block, size);
	}

	return mem_block;

}

int sonBuddies(memory_block_t* block1, memory_block_t* block2){
	return (block1 -> data -> size == block2 -> data -> size) && block1 -> data -> base == ((uint32_t)block2 -> data -> base ^ block2 -> data -> size);
}

