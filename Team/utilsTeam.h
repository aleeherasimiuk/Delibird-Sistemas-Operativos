/*
 * utilsTeam.h
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */

#ifndef UTILSTEAM_H_
#define UTILSTEAM_H_

#include <stdio.h>
#include <stdlib.h>

#include "entrenadores.h"
#include <commons/collections/list.h>

// LIBERACION

// Se pasa una lista de punteros, donde el ultimo elemento es NULL
void liberarListaDePunteros(char** list);
void liberarListaDeInventario(t_list* lista);
void liberarInventario(t_inventario* inventario);

#endif /* UTILSTEAM_H_ */
