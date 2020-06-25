/*
 * gestion_de_archivos.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "gestion_de_archivos.h"
#include <stdint.h>

/*void unir_paths(char* path1, char* path2, char **ruta) {

	ruta = string_new();
	string_append(&ruta, path1);
    string_append(&ruta, path2);

}*/


int archivo_en_uso(char* path){
	//TODO hacer

	char* metadata = "Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadata);


	log_debug(logger, "%s",ruta);
	char buffer[50];

	FILE* file = NULL;

	file = fopen(ruta, "rb");

	fread(&buffer, sizeof(METADATA), 1, file);
	fclose(file);

	char open = buffer[sizeof(char)];

	log_debug(logger, "%c", open);

	if(open == 'Y') {
		return 1;
	}

	else if(open == 'N') {

		/*open = 'Y';
		fseek(file, sizeof(char), SEEK_SET);
		fwrite(&open, sizeof(char), 1, file);*/
		return 0;
	}

	else {
		log_error(logger, "hay un error en la variable OPEN del metadata");
		return -1;
	}
}

void verificar_pokemon(char* path, char* nombre_pokemon){

		char* ruta = string_new();
		string_append(&ruta, path);
		string_append(&ruta, nombre_pokemon);

		struct stat st = {0};

		if (stat(ruta, &st) == -1) {

				mkdir(ruta, 0777);

				char* metadata = "/Metadata.bin";

				char* rutameta = string_new();
				string_append(&rutameta, ruta);
				string_append(&rutameta, metadata);

				FILE* file;

				file = fopen(rutameta, "wb");

				METADATA* datos;

				datos->DIRECTORY = 'N';
				datos->OPEN = 'N';

				fwrite(&datos, sizeof(METADATA), 1, file);

				fclose(file);
		}
}

void agregar_posicion_y_cantidad(t_coords* posicion, uint32_t cantidad){
	//TODO hacer
}

void verificar_posiciones(char* path, t_coords* coordenadas) {

	t_coords* posiciones;

	FILE* file = NULL;

	file = fopen(path, "rb");

		log_debug(logger, "el archivo es null");

	fread(&posiciones, sizeof(t_coords), 1, file);

	log_debug(logger, "%lu  %lu", (unsigned long)posiciones->posX, (unsigned long)posiciones->posY);


}


