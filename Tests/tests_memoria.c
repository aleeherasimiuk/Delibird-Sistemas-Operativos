/*
 * tests_memoria.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */


#include "tests_memoria.h"

context(memoria){

	describe("Pruebas memoria"){

		int esPotenciaDeDos(int n){
			double x;
			return modf(log2(n), &x) == 0;
		}

		it("Potencia de dos"){

			should_int(esPotenciaDeDos(128)) be equal to (1);
			should_int(esPotenciaDeDos(100)) be equal to (0);
		} end


		it("0 y 8: SonBuddies"){

			memory_block_t* block1 = malloc(sizeof(memory_block_t));
			memory_block_t* block2 = malloc(sizeof(memory_block_t));

			block1 -> data = malloc(sizeof(memory_info_t*));
			block2 -> data = malloc(sizeof(memory_info_t*));

			block1 -> data -> base = 0x00;
			block2 -> data -> base = 0x08;

			block1 -> data -> size = 8;
			block2 -> data -> size = 8;

			should_int(sonBuddies(block1, block2)) be equal to (1);

			free(block1 -> data);
			free(block2 -> data);
			free(block1);
			free(block2);


		} end

		it("0 y 20: SonBuddies"){

			memory_block_t* block1 = malloc(sizeof(memory_block_t));
			memory_block_t* block2 = malloc(sizeof(memory_block_t));

			block1 -> data = malloc(sizeof(memory_info_t*));
			block2 -> data = malloc(sizeof(memory_info_t*));

			block1 -> data -> base = 0x00;
			block2 -> data -> base = 0x20;

			block1 -> data -> size = 32;
			block2 -> data -> size = 32;

			should_int(sonBuddies(block1, block2)) be equal to (1);

			free(block1 -> data);
			free(block2 -> data);
			free(block1);
			free(block2);


		} end

		it("0 y 10: SonBuddies"){

			memory_block_t* block1 = malloc(sizeof(memory_block_t));
			memory_block_t* block2 = malloc(sizeof(memory_block_t));

			block1 -> data = malloc(sizeof(memory_info_t*));
			block2 -> data = malloc(sizeof(memory_info_t*));

			block1 -> data -> base = 0x00;
			block2 -> data -> base = 0x10;

			block1 -> data -> size = 16;
			block2 -> data -> size = 16;

			should_int(sonBuddies(block1, block2)) be equal to (1);

			free(block1 -> data);
			free(block2 -> data);
			free(block1);
			free(block2);


		} end

		it("80 y a0: SonBuddies"){

			memory_block_t* block1 = malloc(sizeof(memory_block_t));
			memory_block_t* block2 = malloc(sizeof(memory_block_t));

			block1 -> data = malloc(sizeof(memory_info_t*));
			block2 -> data = malloc(sizeof(memory_info_t*));

			block1 -> data -> base = 0x80;
			block2 -> data -> base = 0xa0;

			block1 -> data -> size = 32;
			block2 -> data -> size = 32;

			should_int(sonBuddies(block1, block2)) be equal to (1);

			free(block1 -> data);
			free(block2 -> data);
			free(block1);
			free(block2);


		} end

		it("c0 y d0: NO Son Buddies"){

			memory_block_t* block1 = malloc(sizeof(memory_block_t));
			memory_block_t* block2 = malloc(sizeof(memory_block_t));

			block1 -> data = malloc(sizeof(memory_info_t*));
			block2 -> data = malloc(sizeof(memory_info_t*));

			block1 -> data -> base = 0xc0;
			block2 -> data -> base = 0xd0;

			block1 -> data -> size = 16;
			block2 -> data -> size = 8;

			should_int(sonBuddies(block1, block2)) be equal to (0);

			free(block1 -> data);
			free(block2 -> data);
			free(block1);
			free(block2);


		} end

		it("16 y 8: NO Son Buddies"){

			memory_block_t* block1 = malloc(sizeof(memory_block_t));
			memory_block_t* block2 = malloc(sizeof(memory_block_t));

			block1 -> data = malloc(sizeof(memory_info_t*));
			block2 -> data = malloc(sizeof(memory_info_t*));

			block1 -> data -> base = 0x16;
			block2 -> data -> base = 0x08;

			block1 -> data -> size = 8;
			block2 -> data -> size = 8;

			should_int(sonBuddies(block1, block2)) be equal to (0);

			free(block1 -> data);
			free(block2 -> data);
			free(block1);
			free(block2);


		} end


	} end

}
