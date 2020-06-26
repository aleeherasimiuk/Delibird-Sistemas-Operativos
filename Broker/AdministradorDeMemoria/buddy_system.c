/*
 * buddy_system.c
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */


#include "buddy_system.h"

memory_block_t* buddy_system(memory_block_t* mem_block, uint32_t size){

	int division = mem_block -> data -> size / 2;

	if(division > size){
		memory_block_t* new_block = particionar(mem_block, division);
		return buddy_system(new_block, size);
	}

	return mem_block;

}

