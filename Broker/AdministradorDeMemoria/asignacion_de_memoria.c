/*
 * asignacion_de_memoria.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#include "asignacion_de_memoria.h"

sem_t sem_msg_data;
pthread_mutex_t mx_mem;
pthread_mutex_t mx_flag;
uint32_t next_flag = 0;
uint32_t compact;

void iniciarCola(){
	sem_init(&sem_msg_data, 0, 0);
	pthread_mutex_init(&mx_mem, NULL);
	pthread_mutex_init(&mx_flag, NULL);
	datos_para_guardar = queue_create();
}

void* guardarEnMemoria(){

	/* Proceso para guardar un dato en la caché
	 *
	 * 1° Esperar a que haya un paquete en la cola. (Los threads correspondientes darán una señal al semáforo cuando esto pase)
	 * 2° Bloquear el uso de la memoria mediante un MUTEX.
	 * 3° Actualizar el valor de frecuencia de compactación (Tiene scope por mensaje NO ES GLOBAL)
	 * 4° Asigno una partición
	 * 5° Copio los datos
	 * 6° Relaciono el bloque generado con el mensaje en la lista
	 * 7° Libero el paquete
	 * 8° Desbloqueo la memoria
	 * 9° Vuelta al paso 1
	 *
	 *
	 * */

	while(1){

		sem_wait(&sem_msg_data);
		pthread_mutex_lock(&mx_mem);

		compact = freq_compact; /*https://bit.ly/2BEfVk2*/
		t_paquete* data = queue_pop(datos_para_guardar);
		memory_block_t* particion = asignarUnaParticion(data -> buffer -> stream_size);
		copiarDatos(particion, data);
		relacionarBloqueConMensaje(particion, data);
		log_debug(logger, "Guardé un dato en una particion de tamaño: %d, para un dato de tamaño: %d", particion -> data -> size, data -> buffer -> stream_size);
		liberarPaquete(data);
		estadoDeLaMemoria();
		pthread_mutex_unlock(&mx_mem);

	}

}



memory_block_t* asignarUnaParticion(uint32_t size){

	/*
	 * Proceso de asignación de una partición
	 *
	 * 1° Establezco el tamaño de la partición teniendo en cuenta el valor de la mínima particion establecida en configuración.
	 * 2° Establezco la fragmentación interna que tendrá ese bloque (Solo si el tamaño de los datos es menor a la minima partición)
	 * 3° Ubico un bloque en memoria según FIRST_FIT o BEST_FIT
	 * 4° Si no se encuentra ningún bloque se procede a acomodar la memoria, que llama recursivamente a asignarUnaParticion.
	 * 5° Particiono el bloque según lo calculado en el paso 1 usando Particiones dinámicas o Buddy System según configuración
	 * 6° Actualizo el valor de fragmentación interna en el bloque
	 *
	 *
	 * */

	uint32_t tamano_particion = max(size, min_part);
	uint32_t fragmentacion    = tamano_particion - size;
	memory_block_t* bloque = NULL;

	if(part_libre == FIRST_FIT){
		bloque = first_fit(tamano_particion);
	}

	if(part_libre == BEST_FIT){
		bloque = best_fit(tamano_particion);
	}

	if(bloque == NULL){
		log_debug(logger, "Tengo que acomodar la memoria");
		return acomodarMemoria(size);
	}

	memory_block_t* block = NULL;
	if(memoria == PARTICIONES)
		block = particionar(bloque, tamano_particion);
	if(memoria == BUDDY_SYSTEM)
		block = buddy_system(bloque, tamano_particion);

	block -> data -> fragmentacion = fragmentacion;
	return block;
}

uint32_t max(uint32_t a, uint32_t b){
	return a > b? a : b;
}

void copiarDatos(memory_block_t* destino, t_paquete* paquete){
	memcpy(destino -> data -> base, paquete -> buffer -> stream, paquete -> buffer -> stream_size);
	destino -> data -> status = OCUPADO;


}

void relacionarBloqueConMensaje(memory_block_t* particion, t_paquete* data){

	//pthread_mutex_lock(&msg_mx); obtenerMensaje ya tiene su propio lock.
	clientes_por_mensaje_t* cxm = obtenerMensaje(data -> id);
	cxm -> memory_block = particion;
	actualizarFlag(cxm);
	particion -> data -> msg_id = cxm -> id_mensaje;
}

void actualizarFlag(clientes_por_mensaje_t* cxm){
	pthread_mutex_lock(&mx_flag);
	cxm -> memory_block -> data -> flag = next_flag++;
	pthread_mutex_unlock(&mx_flag);
}

void liberarPaquete(t_paquete* data){
	free(data -> buffer -> stream);
	free(data -> buffer);
	free(data);
}

void* acomodarMemoria(uint32_t size){

	/*
	 * Proceso para el reemplazo de bloques de memoria:
	 *
	 * * Si el contador de compactación es != 0 libero un bloque y resto el contador
	 *
	 * * Si el contador es 0 pero el algoritmo de reemplazo es Buddy System libero un bloque
	 *
	 * * Si el contador es 0 y el algoritmo de reemplazo es Particiones Dinámicas entonces compacto la memoria.
	 *
	 * */

	log_debug(logger, "Valor de compact: %d", compact);

	if(memoria != BUDDY_SYSTEM && compact == 0){
		compactar();
	} else {
		librerarUnBloque();
		compact--;
	}

	return asignarUnaParticion(size);

}

void estadoDeLaMemoria(){

	memory_block_t* mem_block = memory;
	int i = 0;

	while(mem_block != NULL){

		log_debug(logger, "Partición número: %d \nPosition: %4p \nAnterior: %4p \nInicio: %4p \nTamaño: %d \nFragmentacion: %d \nEstado: %d \nFlag: %d \nSiguiente: %4p\n\n",
				i++,
				mem_block,
				mem_block -> previous == NULL? 0: mem_block -> previous,
				&(mem_block -> data -> base),
				mem_block -> data -> size,
				mem_block -> data -> fragmentacion,
				mem_block -> data -> status,
				mem_block -> data -> flag,
				mem_block -> next == NULL? 0: mem_block -> next);

//		mem_hexdump(&(mem_block -> data -> base), mem_block -> data -> size);

		mem_block = mem_block -> next;
	}

}
