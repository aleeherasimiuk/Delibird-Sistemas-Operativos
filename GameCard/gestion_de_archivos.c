/*
 * gestion_de_archivos.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "gestion_de_archivos.h"

t_list* lista_coordenadas;

/*void unir_paths(char* path1, char* path2, char **ruta) {

	ruta = string_new();
	string_append(&ruta, path1);chequear_bloque_disponible
    string_append(&ruta, path2);

}*/

t_config* leer_metadata(char* ruta) {
	return config_create(ruta);
}

void destruir_metadata(t_config* config) {
	config_destroy(config);
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
		destruir_metadata(metadata);

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

//Me parece que esta funcion va a crear 23432 memory leaks
char* path_para_clave(char* clave, char* path_pokemon, int mode) {

	char** bloques = NULL;
	char* ruta = NULL;
	int i = 0;
	int bloque_disponible = -1;

	bloques = obtener_bloques(path_pokemon);

	while(bloques[i] != NULL) {

		ruta = string_new();
		string_append(&ruta, "/home/utnso/Escritorio/tall-grass/Blocks/");
		string_append(&ruta, bloques[i]);
		string_append(&ruta, ".bin");

		t_config* bloque = config_create(ruta);

		if(mode == 1) {
			if(config_has_property(bloque, clave)) {

				return ruta;
			}
			i++;
			continue;
		}
		else if(config_has_property(bloque, clave) || !chequear_lleno(ruta, 29)) {
			return ruta;
		}


	i++;
	}


	bloque_disponible = agregar_bloque_disponible(path_pokemon);

	char* bloque_ruta;
	ruta = string_new();
	bloque_ruta = string_itoa(bloque_disponible);

	string_append(&ruta, "/home/utnso/Escritorio/tall-grass/Blocks/");
	string_append(&ruta, bloque_ruta);
	string_append(&ruta, ".bin");

	log_debug(logger, "aaaaa");

	free(bloques);

	return ruta;

}


void agregar_posicion_y_cantidad(t_coords* coordenadas, int cant, char* path) {

	//TODO: arreglar logica repetida

	u_int32_t x = coordenadas->posX;
	u_int32_t y = coordenadas->posY;

	char* clave;

	clave = pos_a_clave(x, y);


	t_config* data = config_create(path);

	struct stat statbuf;
	int tamanio;

	stat(path, &statbuf);
	tamanio = statbuf.st_size;


	if((tamanio == 0) || (!config_has_property(data, clave))){

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

		log_debug(logger, "aca llega2");

	}

	int cant_vieja = config_get_int_value(data, clave);

	int cantidad_act = cant_vieja + cant;

	log_debug(logger, "aca llega3");

	char* cantidad_nueva;

	cantidad_nueva = string_itoa(cantidad_act);

	config_set_value(data, clave, cantidad_nueva);

	config_save(data);
	config_destroy(data);

	free(cantidad_nueva);

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

	t_config* metadata = leer_metadata(rutameta);

	config_set_value(metadata, "OPEN", "N");

	config_save(metadata);
	destruir_metadata(metadata);
}

int chequear_lleno(char* path, size_t size) {

	const int tamanio_pos = 5;
	int cantidad_claves;
	int tamanio_total;

	struct stat statbuf;

	stat(path, &statbuf);
	tamanio_total = statbuf.st_size;

	if(tamanio_total < size) {
		return 0;
	}

	else if(tamanio_total >= size) {
		return 1;
	}
	else {
		log_error(logger, "hay un error en el bloque %s", path);
	}
	return -1;
}

int actualizar_bitmap(off_t bloque) {

	char block[2];

	sprintf(block, "%d", bloque);

	log_debug(logger, "checkpoint 1");


	log_debug(logger, "checkpoint 2");

	if(chequear_ocupado(bloque)) {

		log_debug(logger, "checkpoint 3 parte 1");
		bitarray_set_bit(bitarray, bloque);
		return 0;
	}

	else {
		bitarray_clean_bit(bitarray, bloque);
		log_debug(logger, "checkpoint 3 parte 2");
		return 1;
	}

}

// esta función devuleve los bloques en un array de strings
char** obtener_bloques(char* path) {

	char** bloques = NULL;
	int i = 0;

	char* metadataPath = "/Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	/*if(!strcmp(config_get_string_value(metadata, "BLOCKS"), "[]")) {
		bloques[0] = "-1";
		return bloques;
	}*/

	bloques = config_get_array_value(metadata, "BLOCKS");

	destruir_metadata(metadata);

	return bloques;
}

//chequea si esta el bloque disponible del array de bloques del metadata
int chequear_bloque_disponible(int bloque) {

	struct stat statbuf;
	char bloque_string[2];
	size_t tamanio;
	sprintf(bloque_string, "%d", bloque);

	char* ruta = string_new();
	string_append(&ruta, "/home/utnso/Escritorio/tall-grass/Blocks/");
	string_append(&ruta, bloque_string);
	string_append(&ruta, ".bin");

	stat(ruta, &statbuf);
	tamanio = statbuf.st_size;

	if(tamanio == 0) {
		return 1;
	}

	return 0;
}

//Busca y retorna un bloque disponible en el bitmap
int buscar_bloque_disponible(void) {
	int pos = 1;
	int max = bitarray_get_max_bit(bitarray);
	int bit_ocupado;

	while(pos <= max) {

		bit_ocupado = bitarray_test_bit(bitarray, pos);
		log_debug(logger, "el bit ocupado vale %i", bit_ocupado);
		log_debug(logger, "El bit de la posición %d, %s", pos, bit_ocupado? "está ocupado": "está libre");
		if(!bit_ocupado) {
			return pos;
		} else {
			pos++;
		}
	}

	return -1;
}


//Agrega un bloque que este disponible al array de bloques en el metadata
int agregar_bloque_disponible(char* path) {

	char* bloques;
	char* bloques_fixed = NULL;
	int bloque_disponible;
	char bloque_add[2];
	char* nuevos_bloques = NULL;

//TODO: arreglar repeticion logica

	char* metadataPath = "/Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	bloques = config_get_string_value(metadata, "BLOCKS");
	bloques_fixed = arreglar_string(bloques, "]");

	bloque_disponible = buscar_bloque_disponible();
	sprintf(bloque_add, "%d", bloque_disponible);

	if(strlen(bloques_fixed) == 1) {
		nuevos_bloques = string_new();
		string_append(&nuevos_bloques, bloques_fixed);
		string_append(&nuevos_bloques, bloque_add);
		string_append(&nuevos_bloques, "]");
	}

	else {
		nuevos_bloques = string_new();
		string_append(&nuevos_bloques, bloques_fixed);
		string_append(&nuevos_bloques, ",");
		string_append(&nuevos_bloques, bloque_add);
		string_append(&nuevos_bloques, "]");
	}

	config_set_value(metadata, "BLOCKS", nuevos_bloques);

	config_save(metadata);
	destruir_metadata(metadata);


	return bloque_disponible;

}

void quitar_bloque(char* path ,int bloque) {

	char** bloques;
	char** bloques_nuevos;
	char* bloque_string = string_itoa(bloque);
	int i = 0;
	int j = 0;
	int cantidad_total = 0;
	int tamanio_bloques = 0;
	//TODO: arreglar repeticion logica

	log_debug(logger, "el bloque es %s", bloque_string);

	char* metadataPath = "/Metadata.bin";

	char* ruta = string_new();
	string_append(&ruta, path);
	string_append(&ruta, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	bloques = obtener_bloques(path);

	while(bloques[i] != NULL) {
			tamanio_bloques++;
			i++;
		}

	i = 0;

	bloques_nuevos = malloc(tamanio_bloques * sizeof(char*));

	log_debug(logger, "fuera del while1");

	while(bloques[i] != NULL) {
		if(strcmp(bloques[i], bloque_string) == 0) {


			i++;
		}

		else {
			bloques_nuevos[j] = bloques[i];
			i++;
			j++;
			cantidad_total++;

		}
	}

	i = 0;


	char* array_armado = string_new();
	string_append(&array_armado, "[");

	log_debug(logger, "fuera del while2");

	while(i < cantidad_total) {
		string_append(&array_armado, bloques_nuevos[i]);
		log_debug(logger, "entra en el while");

		if(i + 1 != cantidad_total) {
			string_append(&array_armado, ",");
		}
		i++;
	}

	string_append(&array_armado, "]");

	config_set_value(metadata, "BLOCKS", array_armado);
	log_debug(logger, "estoy quitando el bloque");

	config_save(metadata);
	destruir_metadata(metadata);

	free(bloques);
	free(array_armado);
	free(bloques_nuevos);


}

char* arreglar_string(char* a_arreglar, char* caracts) {

	char * nuevo_string = malloc(strlen(a_arreglar) + 1);
	int i = 0;

	 for ( ; *a_arreglar; a_arreglar++) {
	   if (!strchr(caracts, *a_arreglar)) {
	     nuevo_string[ i ] = *a_arreglar;
	     ++ i;
	   }
	 }

	 nuevo_string[i] = 0;

	 return nuevo_string;
}

int chequear_ocupado(int bloque) {

	char bloque_string[2];
	sprintf(bloque_string, "%d", bloque);

	char* ruta = string_new();
	string_append(&ruta, "/home/utnso/Escritorio/tall-grass/Blocks/");
	string_append(&ruta, bloque_string);
	string_append(&ruta, ".bin");

	return chequear_lleno(ruta, 1);
}

void actualizar_bitmap_pokemon(char* path) {

	char** bloques;
	int posicion_array = 0;
	int maximo_array = 0;



	bloques = obtener_bloques(path);

	int bloques_ent[50];


	while(bloques[posicion_array] != NULL) {
		bloques_ent[posicion_array] = atoi(bloques[posicion_array]);
		posicion_array++;
		maximo_array++;
	}

	posicion_array = 0;

	while (posicion_array < maximo_array) {
		if(actualizar_bitmap(bloques_ent[posicion_array])){

			quitar_bloque(path, bloques_ent[posicion_array]);
		}

		posicion_array++;
	}

	free(bloques);
}

t_list* leer_bloques_pokemon(char* path) {
	char* path_bloques = "/home/utnso/Escritorio/tall-grass/Blocks/";

	char** bloques = obtener_bloques(path);

	lista_coordenadas = list_create();

	for(int i = 0; bloques[i] != NULL; i++){
		char* ruta = string_new();
		string_append(&ruta, path_bloques);
		string_append(&ruta, bloques[i]);
		string_append(&ruta, ".bin");

		log_debug(logger, "la ruta es: %s", ruta);

		t_config* bloque = config_create(ruta);
		t_dictionary* dict = bloque -> properties;
		dictionary_iterator(dict, agregar_coordenadas);
	}

	return lista_coordenadas;

}

void agregar_coordenadas(char* key, void* value){
	char** coords_separated = string_split(key, "-");
	int posX = atoi(coords_separated[0]);
	int posY = atoi(coords_separated[1]);
	t_coords* coords = crear_coordenadas_from_int(posX, posY);
	t_coords_con_cant* coords_con_cant = malloc(sizeof(t_coords_con_cant));
	coords_con_cant -> coordenadas = coords;
	coords_con_cant -> cantidad = value;
	list_add(lista_coordenadas, coords_con_cant);
}


//int cantidad_de_posiciones(char* bloque){
//	return (sizeof(bloque) / sizeof(t_coords_con_cant));
//}
