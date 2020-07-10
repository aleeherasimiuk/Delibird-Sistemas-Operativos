/*
 * particionamiento.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */


#include "particionamiento.h"

/*
 * Proceso FIRST FIT
 *
 * Si el bloque existe y puede entrar retorno el bloque.
 * NULL si no encuentra
 *
 *
 * */

memory_block_t* first_fit(uint32_t size){

	memory_block_t* mem_block = memory;

	while(mem_block != NULL){

		if(puedeEntrar(mem_block -> data, size))
			return mem_block;

		mem_block = mem_block -> next;
	}


	return NULL;

}

/*
 * Si el bloque existe, puede entrar y tiene mejor ajuste que el último establecido lo establezco como nuevo mejor bloque.
 * Si no existe retorno el mejor o NULL si no encuentra.
 *
 * */
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


/*
 * Proceso de Particionamiento
 *
 * 1° Establezco el desperdicio como la resta entre el tamaño del bloque a particionar menos el tamaño del nuevo bloque.
 * 2° Guardo la referencia del siguiente bloque.
 * 3° Alloco memoria para la estructura administrativa del bloque desperdicio.
 * 4° Establezco que el anterior del bloque desperdicio es el bloque a particionar.
 * 5° Alloco memoria para la información de la estructura administrativa
 * 6° Establezco que la base del nuevo bloque desperdicio es la base del anterior más el size que particiono.
 * 7° Establezco que el tamaño del bloque desperdicio es el desperdicio calculado en el paso 1.
 * 8° Asigno el status LIBRE al bloque desperdicio
 * 9° Asigno el flag 0 al bloque desperdicio
 * 10° Asigno el ID 0 al bloque desperdicio
 * 11° Asigno como 0 la fragmentación del bloque desperdicio
 * 12° Asigno la referencia del siguiente bloque al bloque desperdicio
 * 13° Si el bloque siguiente existe, el anterior del siguiente es el bloque desperdicio
 * 14° El siguiente del bloque particionado es el bloque desperdicio
 * 15° El tamaño del bloque particionado es el tamaño del bloque inicial menos el desperdicio.
 * 16° Devuelvo el bloque particionado.
 *
 *
 * */
memory_block_t* particionar(memory_block_t* mem_block, uint32_t size){

	uint32_t desperdicio = (mem_block -> data -> size) - size;
	memory_block_t* next = mem_block -> next;

	memory_block_t* bloque_desperdicio = malloc(sizeof(memory_block_t));

	bloque_desperdicio -> previous = mem_block;
	bloque_desperdicio -> data = malloc(sizeof(memory_info_t));
	bloque_desperdicio -> data -> base = ((mem_block -> data -> base) + size);
	bloque_desperdicio -> data -> size = desperdicio;
	bloque_desperdicio -> data -> status = LIBRE;
	bloque_desperdicio -> data -> flag = 0;
	bloque_desperdicio -> data -> msg_id = 0;
	bloque_desperdicio -> data -> fragmentacion = 0;
	bloque_desperdicio -> next = next;
	if(bloque_desperdicio -> next != NULL)
		bloque_desperdicio -> next -> previous = bloque_desperdicio;


	mem_block -> next = bloque_desperdicio;
	(mem_block -> data -> size) = mem_block -> data -> size - desperdicio;

	return mem_block;

}

/*
 * La info puede entrar en un bloque si está libre y si el tamaño es menor al disponible.
 *
 */

int puedeEntrar(memory_info_t* info, uint32_t size){
	return info -> status == LIBRE && info -> size >= size && info -> size > 0;
}

/*
 * Es mejor ajuste si el anterior mejor no existe o si el tamaño es menor que el anterior mejor
 */

int mejorAjuste(memory_block_t* best, memory_block_t* actual){

	return best == NULL || actual -> data -> size < best -> data -> size;

}
