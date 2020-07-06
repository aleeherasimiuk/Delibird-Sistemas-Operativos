/*
 * gestion_de_archivos.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "gestion_de_archivos.h"
#include <stdint.h>

typedef struct {
	t_coords coordenadas;
	uint32_t cantidad;
}	t_coords_con_cant;

/*void unir_paths(char* path1, char* path2, char **ruta) {

	ruta = string_new();
	string_append(&ruta, path1);
    string_append(&ruta, path2);

}*/

t_config* leer_metadata(char* ruta) {
	return config_create(ruta);
}


int archivo_en_uso(char* path){
	//TODO hacer

	char* metadataPath = "Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadataPath);

	leer_metadata(ruta);



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

				file = fopen(rutameta, "w");

				char datos[50] = "DIRECTORY=N\nSIZE=0\nBLOCKS=[]\nOPEN=N";

				fwrite(&datos, sizeof(char[50]), 1, file);

				fclose(file);
		}
}

void agregar_posicion_y_cantidad(t_coords* posicion, int cantidad, FILE* file){

	log_debug(logger, "llega hasta aggpos");

	t_coords_con_cant coordenadas_y_pos;

	int cant_vieja = 0;

	verificar_posiciones(posicion, file, &cant_vieja);

	coordenadas_y_pos.coordenadas.posX = posicion->posX;
	coordenadas_y_pos.coordenadas.posY = posicion->posY;
	coordenadas_y_pos.cantidad = cant_vieja + cantidad;

	fwrite(&coordenadas_y_pos, sizeof(t_coords_con_cant), 1, file);
	fflush(file);

}

void verificar_posiciones(t_coords* coordenadas, FILE* file, int* cantidad) {

	int i;

	t_coords_con_cant posiciones[16];

	fread(&posiciones, sizeof(t_coords_con_cant), 16, file);

	for(i = 0; i < 16; i++) {
		if(coordenadas->posX == posiciones[i].coordenadas.posX && coordenadas->posY == posiciones[i].coordenadas.posY) {

			fseek(file, i * sizeof(t_coords_con_cant), SEEK_SET);
			*cantidad = posiciones[i].cantidad;

			return;
		}
	}

	fseek(file, 0, SEEK_END);
	cantidad = 0;
}

void leer_archivo(FILE* file) {

	fseek(file, 0, SEEK_SET);

	t_coords_con_cant buffer[16];

	int i = 0;

	while(!feof(file)) {

		fread(&buffer[i++], sizeof(t_coords_con_cant), 1, file);
	}
	for(int i = 0; i < 2; i ++) {
		log_debug(logger, "hay en %d", buffer[i].cantidad);
	}
}


