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

	memory_block_t* last = NULL;
	memory_block_t* actual = compacted_memory;

	while(mem_block != NULL){

		if(mem_block -> data -> status == OCUPADO){
			actual = particionar(actual, mem_block -> data -> size);
			memmove(actual -> data -> base, mem_block -> data -> base, mem_block -> data -> size);
			actual -> data -> flag = mem_block -> data -> flag;
			actual -> data -> status = OCUPADO;
			actual -> data -> size = mem_block -> data -> size;
			actual -> data -> msg_id = mem_block -> data -> msg_id;
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

	clientes_por_mensaje_t* cli = obtenerMensaje(id);
	cli -> memory_block = new_block;

}

//void compactar(){
//
//	memory_block_t* mem_block = memory;
//	memory_block_t* primero_libre = NULL;
//	log_debug(logger, "Empiezo la compactación");
//
//	while(mem_block != NULL){
//
//		if(mem_block -> data -> status == LIBRE){
//			log_debug(logger, "Encontré un bloque libre");
//			if(primero_libre == NULL){
//				primero_libre = mem_block;
//			} else {
//				mem_block = mem_block -> next;
//				continue;
//			}
//		}
//
//		if(primero_libre == NULL){
//			log_debug(logger, "Este bloque está compactado");
//			mem_block = mem_block -> next;
//			continue;
//		}
//
//
//		if(primero_libre -> data -> size > mem_block -> data -> size){
//			log_debug(logger, "Compactaré en un espacio mayor");
//			memory_block_t* nuevo_bloque = particionar(primero_libre, mem_block -> data -> size);
//			memcpy(nuevo_bloque -> data -> base, mem_block -> data -> base, mem_block -> data -> size);
//			mem_block -> data -> status = LIBRE;
//			consolidar(nuevo_bloque -> next);
//			primero_libre = NULL;
//		} else {
//			log_debug(logger, "Compactaré en un espacio menor");
//			mergeWithContent(primero_libre, mem_block);
//			primero_libre = NULL;
//			log_debug(logger, "Terminé de compactar en un espacio menor");
//		}
//
//		if(mem_block == NULL){
//			log_debug(logger, "Soy null wacho");
//		} else {
//			mem_block = mem_block -> next;
//			if(mem_block == NULL){
//				log_debug(logger, "Ahora si soy null");
//			}
//		}
//	}
//
//	log_debug(logger, "Listo");
//
//}
//
//void mergeWithContent(memory_block_t* fst, memory_block_t* snd){
//
//	log_debug(logger, "Estoy mergeando");
//
//	fst -> data -> status = OCUPADO;
//	uint32_t tamano_total = fst -> data -> size + snd -> data -> size;
//	uint32_t tamano_bloque = snd -> data -> size > min_part? snd -> data -> size : min_part;
//	fst -> data -> size = snd -> data -> size;
//	memmove(snd -> data -> base, fst -> data -> base, snd -> data -> size);
//
//	log_debug(logger, "Terminé de mover");
//
//	snd -> data -> base = fst -> data -> base + fst -> data -> size;
//	snd -> data -> status = LIBRE;
//	snd -> data -> flag = 0;
//	snd -> data -> size = tamano_total - (fst -> data -> size);
//
//	log_debug(logger, "Voy a consolidar");
//	consolidar(snd);
//	log_debug(logger, "Terminé de consolidar");
//}






