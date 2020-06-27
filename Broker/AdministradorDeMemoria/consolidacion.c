/*
 * consolidacion.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "consolidacion.h"

/*
 * Proceso de consolidación
 *
 * Todo bloque que se libera debe consolidarse con los contiguos en caso de estar libres
 *
 *
 *  1° Tomo el bloque anterior al bloque eliminado
 *  2° Tomo el bloque siguiente al bloque eliminado
 *  3° Si el bloque anterior existe y está libre consolido con el bloque eliminado y continuo al paso 4. Sino al paso 5
 *  4° Si el bloque siguiente existe y está libre consolido con el bloque obtenido en el paso anterior y termino la consolidación
 *  5° Si el bloque anterior no existe pero existe el siguiente y está libre consolido el bloque eliminado con el siguiente y termino la consolidación
 *  6° Si no existe bloque anterior y/o siguiente o ambos están ocupados no se realiza ninguna acción.
 *
 * */

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


/*
 * Proceso Merge
 *
 * Une 2 bloques que fueron liberados
 *
 *  1° El siguiente del nuevo bloque es el siguiente del segundo bloque
 *  2° El tamaño del nuevo bloque es la suma de los tamaños de ambos bloques
 *  3° Si el bloque siguiente existe, el anterior del bloque siguiente es el nuevo bloque
 *  4° Se libera la memoria de la estructura administrativa del segundo bloque
 *  5° Se retorna el primer bloque como nuevo bloque.
 *
 *
 * */

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

/*TODO*/
int tieneBuddy(memory_block_t* bloque_eliminado){
	return esBuddy(bloque_eliminado, bloque_eliminado -> next) || esBuddy(bloque_eliminado, bloque_eliminado -> previous);
}

int esBuddy(memory_block_t* block, memory_block_t* buddy){

	if(buddy != NULL)
		return (buddy -> data -> status == LIBRE && buddy -> data -> size == block -> data -> size);
	return 0;
}
