/*
 * consolidacion.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "consolidacion.h"

void consolidar(memory_block_t* bloque_eliminado){

	log_debug(logger, "Empiezo a consolidar");
	memory_block_t* bloque_anterior = bloque_eliminado -> previous;
	memory_block_t* bloque_siguiente = bloque_eliminado -> next;

	estadoDeLaMemoria();

	log_debug(logger, "El bloque anterior es NULL? %s", bloque_anterior == NULL? "YES" : "NO");
	if(bloque_anterior != NULL ){
		log_debug(logger, "El data es NULL? %s", bloque_anterior -> data == NULL? "YES" : "NO");
		if(bloque_anterior -> data != NULL && bloque_anterior -> data -> status == LIBRE){
			log_debug(logger, "Entré al segundo if");
			memory_block_t* nuevo_bloque = merge(bloque_anterior, bloque_eliminado);

			if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
				merge(nuevo_bloque, bloque_siguiente);
			}
		}
		log_debug(logger, "Hola,no se cumple la condicion");

	} else if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
		log_debug(logger, "Entré pero al tercer if");
		merge(bloque_eliminado, bloque_siguiente);
	}

	log_debug(logger, "Terminé de consolidar");


	//TODO: Hace falta?
//	if(memoria == BUDDY_SYSTEM && tieneBuddy(bloque_eliminado)){
//		log_debug(logger, "Buddy debe consolidar");
//		consolidar(bloque_eliminado);
//	}


}

memory_block_t* merge(memory_block_t* fst, memory_block_t* snd){
	log_debug(logger, "Haciendo un Merge");
	fst -> next = snd -> next;
	fst -> data -> size = (fst -> data -> size) + (snd -> data -> size);

	if(fst -> next != NULL)
		fst -> next -> previous = fst;

	free(snd -> data);
	free(snd);

	log_debug(logger, "Terminé el merge");

	return fst;
}

int tieneBuddy(memory_block_t* bloque_eliminado){
	return esBuddy(bloque_eliminado, bloque_eliminado -> next) || esBuddy(bloque_eliminado, bloque_eliminado -> previous);
}

int esBuddy(memory_block_t* block, memory_block_t* buddy){

	if(buddy != NULL)
		return (buddy -> data -> status == LIBRE && buddy -> data -> size == block -> data -> size);
	return 0;
}
