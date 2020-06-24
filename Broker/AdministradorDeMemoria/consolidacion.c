/*
 * consolidacion.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "consolidacion.h"

void consolidar(memory_block_t* bloque_eliminado){


	log_debug(logger, "Estoy acá-1");
	memory_block_t* bloque_anterior = bloque_eliminado -> previous;
	memory_block_t* bloque_siguiente = bloque_eliminado -> next;

	log_debug(logger, "Estoy acá0");
	if(bloque_anterior != NULL ){
		log_debug(logger, "TEEEEEST");
		if(bloque_anterior -> data -> status == LIBRE){
			log_debug(logger, "TEEEEESTssdasdf");
			log_debug(logger, "Estoy acá0.5");
			memory_block_t* nuevo_bloque = merge(bloque_anterior, bloque_eliminado);
			log_debug(logger, "Estoy acá1");

			if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
				log_debug(logger, "Estoy acá 0.5");
				merge(nuevo_bloque, bloque_siguiente);
				log_debug(logger, "Estoy acá 1");
			}
			log_debug(logger, "Estoy acá2");
		}


	} else if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
		log_debug(logger, "Test");
		merge(bloque_eliminado, bloque_siguiente);
	}

	log_debug(logger, "Estoy acá3");

}

memory_block_t* merge(memory_block_t* fst, memory_block_t* snd){
	log_debug(logger, "Voy a hacer un merge de consolidacion");
	fst -> next = snd -> next;
	fst -> data -> size = (fst -> data -> size) + (snd -> data -> size);
	log_debug(logger, "Terminé el merge y voy a liberar");
	free(snd -> data);
	free(snd);

	return fst;
}
