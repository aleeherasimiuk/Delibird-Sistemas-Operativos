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

void liberarListaDeInventario(t_list* lista) {
	t_inventario* inv;
	for(int i = 0; i < list_size(lista); i++) {
		inv = list_get(lista, i);
		liberarInventario(inv);
	}
	list_destroy(lista);
}

void liberarInventario(t_inventario* inventario) {
	free(inventario->pokemon->name);
	free(inventario->pokemon);
	free(inventario);
}

//////////////////////////////////////////
//					MATH				//
//////////////////////////////////////////

double maximoDouble(double x, double y) {
	if (x > y) {
		return x;
	} else {
		return y;
	}
}
