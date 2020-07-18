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

	if(memoria == PARTICIONES)
		consolidarParticiones(bloque_eliminado);
	else
		consolidarBuddySystem(bloque_eliminado);




}

void consolidarParticiones(memory_block_t* bloque_eliminado){
	memory_block_t* bloque_anterior = bloque_eliminado -> previous;
	memory_block_t* bloque_siguiente = bloque_eliminado -> next;

	if(bloque_anterior != NULL){
		if(bloque_anterior -> data != NULL && bloque_anterior -> data -> status == LIBRE){
			memory_block_t* nuevo_bloque = merge(bloque_anterior, bloque_eliminado);

			if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
				merge(nuevo_bloque, bloque_siguiente);
			}

		} else if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
			merge(bloque_eliminado, bloque_siguiente);
			log_info(logger_extra, "Se consolidarán particiones con el siguiente");
		}


	} else if(bloque_siguiente != NULL && bloque_siguiente -> data -> status == LIBRE){
		merge(bloque_eliminado, bloque_siguiente);
		log_info(logger_extra, "Se consolidarán particiones con el siguiente");
	}


}

void consolidarBuddySystem(memory_block_t* bloque_eliminado){

	if(elSiguienteEsBuddy(bloque_eliminado)){
		memory_block_t* merged = merge(bloque_eliminado, bloque_eliminado -> next);
		consolidarBuddySystem(merged);
	}

	if(elAnteriorEsBuddy(bloque_eliminado)){
		memory_block_t* merged = merge(bloque_eliminado -> previous, bloque_eliminado);
		consolidarBuddySystem(merged);
	}

}

int elSiguienteEsBuddy(memory_block_t* bloque_eliminado) {
	return (bloque_eliminado -> next != NULL) && (bloque_eliminado -> next -> data -> status == LIBRE) && sonBuddies(bloque_eliminado, bloque_eliminado -> next);
}

int elAnteriorEsBuddy(memory_block_t* bloque_eliminado) {
	return (bloque_eliminado -> previous != NULL) && (bloque_eliminado -> previous -> data -> status == LIBRE) && sonBuddies(bloque_eliminado, bloque_eliminado -> previous);
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

	log_info(logger, "Se consolidará la partición con base en <%6p> y la partición con base en <%6p>", fst -> data -> base, snd -> data -> base);

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
