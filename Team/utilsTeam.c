/*
 * utilsTeam.c
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */


#include "utilsTeam.h"

//////////////////////////////////////////
//				LIBERACION				//
//////////////////////////////////////////


void liberarListaDePunteros(char** list) {
	int i = 0;
	while(list[i] != NULL) {
		free(list[i]);
		i++;
	}
	free(list);
}
