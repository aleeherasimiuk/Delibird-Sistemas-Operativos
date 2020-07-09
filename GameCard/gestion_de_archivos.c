/*
 * gestion_de_archivos.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "gestion_de_archivos.h"

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

	char* metadataPath = "/Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	log_debug(logger, "llega hasta aca");

	char* open = config_get_string_value(metadata, "OPEN");

	log_debug(logger, "%s\n", open);


	if(!strcmp(open, "Y")) {
		log_debug(logger, "entra por yes");
		config_destroy(metadata);

		return 1;
	}

	else if(!strcmp(open, "N")) {
		config_set_value(metadata, "OPEN", "Y");
		config_save(metadata);
		config_destroy(metadata);
		log_debug(logger, "entra por no");

		return 0;

	}

	else {
		log_error(logger, "hay un error en la variable OPEN del metadata");
		config_destroy(metadata);
		return -1;
	}
}

char* verificar_pokemon(char* path, char* nombre_pokemon, int crear){

		char* ruta = string_new();
		string_append(&ruta, path);
		string_append(&ruta, "/");
		string_append(&ruta, nombre_pokemon);

		struct stat st = {0};

		if ((stat(ruta, &st) == -1) && crear) {

				mkdir(ruta, 0777);

				crear_metadata_archivo(ruta);

		}

		else if((stat(ruta, &st) == -1) && !crear) {

			log_error(logger, "No existe ese pokemon");

			return "NULL";

		}

	return ruta;
}


void agregar_posicion_y_cantidad(t_coords* coordenadas, int cant, char* path) {

	//TODO: arreglar logica repetida

	u_int32_t x = coordenadas->posX;
	u_int32_t y = coordenadas->posY;

	char* clave;

	clave = pos_a_clave(x, y);


	t_config* data = config_create(path);

	if(!config_has_property(data, clave)){

		config_destroy(data);

		FILE* file;
		file = fopen(path, "r+");

		char* a_escribir = string_new();
		string_append(&a_escribir, "\n");
		string_append(&a_escribir, clave);
		string_append(&a_escribir, "=0");


		log_debug(logger, "aca llega");

		fseek(file, 0, SEEK_END);

		fprintf(file, a_escribir);

		fclose(file);

		data = config_create(path);

	}

	int cant_vieja = config_get_int_value(data, clave);

	int cantidad_act = cant_vieja + cant;

	char* cantidad_nueva;

	sprintf(cantidad_nueva, "%d", cantidad_act);

	config_set_value(data, clave, cantidad_nueva);

	config_save(data);
	config_destroy(data);

}

void disminuir_cantidad(t_coords* coordenadas, char* path) {

	//TODO: arreglar logica repetida

	u_int32_t x = coordenadas->posX;
	u_int32_t y = coordenadas->posY;

	char* clave;

	clave = pos_a_clave(x, y);

	char cantidad_nueva[2];

	log_debug(logger, "hasta aca voy");

	t_config* datos = config_create(path);

	if(!config_has_property(datos, clave)){

		log_error(logger, "no hay pokemones en esta posicion");
		config_destroy(datos);

		return;
	}

	int cant_vieja = config_get_int_value(datos, clave);

	int cantidad_act = cant_vieja - 1;

	if(cantidad_act == 0) {
		 config_remove_key(datos, clave);

	}

	else {

		log_debug(logger, "%d", cantidad_act);

		sprintf(cantidad_nueva, "%d", cantidad_act);

		config_set_value(datos, clave, cantidad_nueva);

		log_debug(logger, "hasta aca estoy");

	}

	config_save(datos);

	config_destroy(datos);


}

void obtener_posiciones(char* path){

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

void crear_metadata_archivo(char* path) {

	char* rutameta = string_new();
	string_append(&rutameta, path);
	string_append(&rutameta, "/Metadata.bin");

	FILE* file;

	file = fopen(rutameta, "w");

	char datos[50] = "DIRECTORY=N\nSIZE=0\nBLOCKS=[]\nOPEN=N";

	fwrite(&datos, sizeof(char[50]), 1, file);

	fclose(file);

}

char* pos_a_clave(u_int32_t x, u_int32_t y) {

	char posX[2];
	char posY[2];

	sprintf(posX, "%d", x);
	sprintf(posY, "%d", y);


	char* clave = string_new();
	string_append(&clave, posX);
	string_append(&clave, "-");
	string_append(&clave, posY);

	log_debug(logger, "%s", clave);

	return clave;

}

void cerrar_archivo(char* path) {

	char* rutameta = string_new();
	string_append(&rutameta, path);
	string_append(&rutameta, "/Metadata.bin");

	t_config* metadata = config_create(rutameta);

	config_set_value(metadata, "OPEN", "N");

	config_save(metadata);
	config_destroy(metadata);
}

int chequear_lleno(char* path, size_t size) {

	const int tamanio_pos = 5;
	int cantidad_claves;
	int tamanio_total;

	t_config* datos = config_create(path);
	cantidad_claves = config_keys_amount(datos);

	tamanio_total = (cantidad_claves * tamanio_pos) + cantidad_claves;

	config_destroy(datos);

	if(tamanio_total < size) {
		return 0;
	}

	else if(tamanio_total == size) {
		return 1;
	}
	else {
		log_error(logger, "hay un error en el bloque %s", path);
	}
	return -1;
}

void actualizar_bitmap(off_t bloque) {

	char block[2];

	sprintf(block, "%d", bloque);

	log_debug(logger, "checkpoint 1");

	char* ruta = string_new();
	string_append(&ruta, "/home/utnso/Escritorio/tall-grass/Blocks");
	string_append(&ruta, "/");
	string_append(&ruta, block);
	string_append(&ruta, ".bin");

	log_debug(logger, "checkpoint 2");

	if(chequear_lleno(ruta, 30)) {

		log_debug(logger, "checkpoint 3 parte 1");
		bitarray_set_bit(bitarray, bloque);
	}

	else {

		bitarray_clean_bit(bitarray, bloque);
		log_debug(logger, "checkpoint 3 parte 2");
	}

}

char** obtener_bloques(char* path) {

	char** bloques = NULL;
	int i = 0;

	char* metadataPath = "/Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	bloques = config_get_array_value(metadata, "BLOCKS");

	config_destroy(metadata);

	return bloques;
}

int chequear_bloque_disponible(char* path) {

	int i = 0;
	int buffer;
	char** bloques = obtener_bloques(path);

	while(bloques[i] != NULL) {

		buffer = atoi(bloques[i]);

		if(!bitarray_test_bit(bitarray, buffer)) {
			return buffer;
		}
		else {
			i++;
		}
	}

	return -1;
}


