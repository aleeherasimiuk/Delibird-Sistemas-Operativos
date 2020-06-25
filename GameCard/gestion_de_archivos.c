/*
 * gestion_de_archivos.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "gestion_de_archivos.h"
#include "string.h"

/*void archivo_en_uso(char* path){
	//TODO hacer

	char* buffer[7];

	FILE* file = NULL;

	file = fopen(path, "rb");

	fseek(file, 11, SEEK_SET);

	fread(buffer, 7, 1, file);

	log_debug(logger, "%s", buffer);

	fclose(file);

	if(strcmp(buffer, "OPEN=N")) {
		log_debug(logger, "el archivo ya esta abierto capo");
	}

	else {
		log_debug(logger, "se puede usar master");
	}

}*/

void verificar_pokemon(FILE* file, char* nombre_pokemon){
	//TODO hacer
}

void agregar_posicion_y_cantidad(t_coords* posicion, uint32_t cantidad){
	//TODO hacer
}


