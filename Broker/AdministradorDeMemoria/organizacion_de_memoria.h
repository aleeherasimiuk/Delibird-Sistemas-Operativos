/*
 * organizacion_de_memoria.h
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#ifndef BROKER_ADMINISTRADORDEMEMORIA_ORGANIZACION_DE_MEMORIA_H_
#define BROKER_ADMINISTRADORDEMEMORIA_ORGANIZACION_DE_MEMORIA_H_

#include <commons/collections/list.h>
#include <stdint.h>
#include <string.h>


typedef enum{
	PARTICIONES,
	BUDDY_SYSTEM
} alg_memoria_t;

typedef enum{
	FIFO,
	LRU
} alg_reemplazo_t;

typedef enum{
	FIRST_FIT,
	BEST_FIT
} alg_part_libre_t;

extern void* cache;
extern uint32_t bytes;
extern alg_memoria_t memoria;
extern alg_reemplazo_t reemplazo;
extern alg_part_libre_t part_libre;
extern uint32_t freq_compact;
extern uint32_t min_part;
extern char* dump_path;


typedef enum{LIBRE, OCUPADO} status_t;

typedef struct{

	void* base;
	uint32_t size;
	uint32_t fragmentacion; // La fragmentación me sirve para saber el tamaño efectivo del stream
	status_t status;
	uint32_t flag;
	uint32_t msg_id;

} memory_info_t;

typedef struct memory_block memory_block_t;
struct memory_block{

	memory_block_t* previous;
	memory_info_t* data;
	memory_block_t* next;

};

extern memory_block_t* memory;





#endif /* BROKER_ADMINISTRADORDEMEMORIA_ORGANIZACION_DE_MEMORIA_H_ */
