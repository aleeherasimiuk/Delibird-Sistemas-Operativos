/*
 * gestion_de_archivos.h
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#ifndef GAMECARD_GESTION_DE_ARCHIVOS_H_
#define GAMECARD_GESTION_DE_ARCHIVOS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<stdint.h>
#include<unistd.h>
#include <sys/socket.h>
#include<netdb.h>
#include<string.h>
#include <pthread.h>
#include<commons/config.h>
#include "../Utils/conexiones.h"
#include "var_globales_gamecard.h"
#include <sys/types.h>
#include <sys/stat.h>



typedef struct {
	char DIRECTORY;
	char OPEN;
	int SIZE;
	int BLOCKS[];
}METADATA;

t_config* leer_metadata(char*);

void unir_paths(char*, char*, char**);

int archivo_en_uso(char*);
void verificar_pokemon(char*, char*);
void agregar_posicion_y_cantidad(t_coords* ,int , FILE*);
void verificar_posiciones(t_coords*, FILE* file, int*);
void leer_archivo(FILE* file);



#endif /* GAMECARD_GESTION_DE_ARCHIVOS_H_ */
