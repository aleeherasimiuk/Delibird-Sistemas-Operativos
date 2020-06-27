/*
 * liberacion_memoria.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "liberacion_memoria.h"

/*
 * Proceso de liberación de memoria
 *
 * 1° Busco un bloque que pueda eliminar
 * 2° Asigno el status LIBRE
 * 3° Actualizo mensaje TODO: Debe eliminarse de la lista
 * 4° Consolido bloques.
 *
 *
 * */

void librerarUnBloque(){

	memory_block_t* bloque_a_eliminar =  bloqueAEliminar();
	bloque_a_eliminar -> data -> status = LIBRE;
	log_debug(logger, "El bloque a eliminar se encuentra: %d", bloque_a_eliminar -> data -> status);
	int id = bloque_a_eliminar -> data -> msg_id;
	log_info(logger, "Se ha eliminado el mensaje #%d, de su partición [%6p]", id, bloque_a_eliminar -> data -> base);
	actualizarMensaje(NULL, id);
	consolidar(bloque_a_eliminar);
}


/*
 * Algoritmo de elección de víctima
 *
 * 1° Asigno un bloque que será la victima
 * 2° Si el bloque existe paso al siguiente paso sino al paso 6
 * 3° Si el bloque está ocupado paso al siguiente paso. Sino al paso 5
 * 4° Si el bloque es mejor víctima que el último establecido lo establezco como nueva víctima y vuelvo al paso 2. Sino no ejecuto acción y vuelvo al paso 2
 * 5° Apunto al bloque siguiente.
 * 6° Retorno la víctima definitiva.
 *
 * */

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

/*Un bloque es más eliminable que otro, si el otro no existe o su flag de LRU (o FIFO) es menor*/

int eliminable(memory_block_t* mem_block, memory_block_t* a_eliminar){
	return a_eliminar == NULL || mem_block -> data -> flag < a_eliminar -> data -> flag;
}

