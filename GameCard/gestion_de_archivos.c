/*
 * gestion_de_archivos.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */


#include "gestion_de_archivos.h"

t_list* lista_coordenadas;

pthread_mutex_t mx_open;

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

	char* ruta = concat_string(path, metadataPath);

	pthread_mutex_lock(&mx_open);

	t_config* metadata = leer_metadata(ruta);

	char* open = config_get_string_value(metadata, "OPEN");


	if(!strcmp(open, "Y")) {
		pthread_mutex_unlock(&mx_open);
		destruir_metadata(metadata);
		free(ruta);

		return 1;
	}

	else if(!strcmp(open, "N")) {
		config_set_value(metadata, "OPEN", "Y");
		config_save(metadata);
		config_destroy(metadata);
		pthread_mutex_unlock(&mx_open);
		free(ruta);

		return 0;

	}

	else {
		log_error(logger, "Hay un error en la variable OPEN del metadata");
		config_destroy(metadata);
		pthread_mutex_unlock(&mx_open);
		free(ruta);
		return -1;
	}
}

char* verificar_pokemon(char* path, char* nombre_pokemon, int crear){

		char* ruta = concat_string(path, "/");
		char* ruta_final = concat_string(ruta, nombre_pokemon);

		struct stat st = {0};

		if ((stat(ruta_final, &st) == -1) && crear) {

				mkdir(ruta_final, 0777);

				crear_metadata_archivo(ruta_final);
				log_info(logger, "Se creó la carpeta '%s' en el File System", nombre_pokemon);

		}

		else if((stat(ruta_final, &st) == -1) && !crear) {

			log_error(logger, "No se ha encontrado %s en el File System", nombre_pokemon);

			free(ruta);
			free(ruta_final);

			return NULL;

		}

	free(ruta);
	return ruta_final;
}

//Me parece que esta funcion va a crear 23432 memory leaks
char* path_para_clave(char* clave, char* path_pokemon, uint32_t cantidad, int mode, char* pokemon, int *bloque_asignado) {

	char** bloques = NULL;
	char* ruta = NULL;
	char* ruta_media = NULL;
	char* ruta_final = NULL;
	char* ruta_final_copia = NULL;
	int i = 0;
	int bloque_disponible = -1;
	int block_size = 0;
	int valor_bloque = 0;
	t_config* metadata = NULL;
	uint32_t cantidad_total = 0;
	uint32_t tamanio_clave = sizeof(char) * strlen(clave);
	char* cantidad_string = string_itoa(cantidad);
	uint32_t tamanio_cantidad = sizeof(char) * strlen(cantidad_string);
	int cantidad_caracteres = 0;
	char* cantidad_total_string;

	free(cantidad_string);

	char* ruta_metadata = concat_string(ruta_punto_montaje, "/Metadata/Metadata.bin");

	metadata = config_create(ruta_metadata);

	block_size = config_get_int_value(metadata, "BLOCK_SIZE");

	config_destroy(metadata);

	free(ruta_metadata);

	bloques = obtener_bloques(path_pokemon);

	while (bloques[i] != NULL) {

		ruta = concat_string(ruta_punto_montaje, "/Blocks/");
		ruta_media = concat_string(ruta, bloques[i]);
		ruta_final = concat_string(ruta_media, ".bin");
		ruta_final_copia = malloc(strlen(ruta_final) + 1);
		strcpy(ruta_final_copia, ruta_final);


		t_config* bloque = config_create(ruta_final);

		if (mode == 1) {
			if (config_has_property(bloque, clave)) {

				config_destroy(bloque);
				free(ruta);
				free(ruta_media);
				free(ruta_final_copia);
				valor_bloque = atoi(bloques[i]);
				*bloque_asignado = valor_bloque;
				liberarListaDePunteros(bloques);
				return ruta_final;
			}
			i++;
			continue;
		} else if (config_has_property(bloque, clave)) {

			cantidad_total = config_get_int_value(bloque, clave);
			cantidad_total += cantidad;
			cantidad_total_string = string_itoa(cantidad_total);
			cantidad_caracteres = strlen(cantidad_total_string);
			free(cantidad_total_string);

			if (!chequear_lleno(ruta_final_copia, block_size, cantidad_caracteres)) {
				config_destroy(bloque);
				free(ruta);
				free(ruta_media);
				valor_bloque = atoi(bloques[i]);
				*bloque_asignado = valor_bloque;
				liberarListaDePunteros(bloques);
				return ruta_final;
			}
		} else {
			cantidad_total += cantidad;
			cantidad_total_string = string_itoa(cantidad_total);
			cantidad_caracteres = strlen(cantidad_total_string);
			cantidad_caracteres += tamanio_clave;
			cantidad_caracteres += 2; //Caracter "=" y "\n"
			free(cantidad_total_string);

			if(!chequear_lleno(ruta_final_copia, block_size, cantidad_caracteres)) {
				config_destroy(bloque);
				free(ruta);
				free(ruta_media);
				 valor_bloque = atoi(bloques[i]);
				*bloque_asignado = valor_bloque;
				liberarListaDePunteros(bloques);
				return ruta_final;
			}
		}
		config_destroy(bloque);
		free(ruta);
		free(ruta_media);
		free(ruta_final);
		i++;
	}

	if(mode == 1) {
		return NULL;
	}

	bloque_disponible = agregar_bloque_disponible(path_pokemon);
	log_info(logger, "[Asignación] -> Bloque #%d -> %s", bloque_disponible, pokemon);

	*bloque_asignado = bloque_disponible;
	char* bloque_ruta;
	bloque_ruta = string_itoa(bloque_disponible);

	ruta = concat_string(ruta_punto_montaje, "/Blocks/");
	ruta_media = concat_string(ruta, bloque_ruta);
	ruta_final = concat_string(ruta_media, ".bin");

	free(bloque_ruta);

	if(bloques != NULL) {
		liberar_lista_de_punteros(bloques);
	}

	free(ruta);
	free(ruta_media);
	return ruta_final;

}


int agregar_posicion_y_cantidad(t_coords* coordenadas, int cant, char* path) {

	//TODO: arreglar logica repetida

	u_int32_t x = coordenadas->posX;
	u_int32_t y = coordenadas->posY;

	char* clave;

	clave = pos_a_clave(x, y);


	t_config* data = config_create(path);

	struct stat statbuf;
	int tamanio;
	int tamanio_final;
	int nuevo;

	stat(path, &statbuf);
	tamanio = statbuf.st_size;


	if((tamanio == 0) || (!config_has_property(data, clave))){

		config_destroy(data);

		FILE* file;
		file = fopen(path, "r+");

		char* a_escribir = concat_string("\n", clave);
		char* a_escribir_final = concat_string(a_escribir, "=0");

		fseek(file, 0, SEEK_END);

		fprintf(file, a_escribir_final);

		fflush(file);
		fclose(file);

		data = config_create(path);

		free(a_escribir);
		free(a_escribir_final);


	}

	log_debug(logger, "%s", clave);


	int cant_vieja = config_get_int_value(data, clave);

	int cantidad_act = cant_vieja + cant;

	char* cantidad_nueva;

	cantidad_nueva = string_itoa(cantidad_act);

	config_set_value(data, clave, cantidad_nueva);

	config_save(data);

	config_destroy(data);

	free(clave);

	free(cantidad_nueva);

	return tamanio_final;

}

int disminuir_cantidad(t_coords* coordenadas, char* path) {

	u_int32_t x = coordenadas->posX;
	u_int32_t y = coordenadas->posY;

	char* clave;
	char* cantidad_nueva = NULL;

	clave = pos_a_clave(x, y);


	t_config* datos = config_create(path);

	if(!config_has_property(datos, clave)){

		log_error(logger, "No se han encontrado pokemones en esta posicion");
		config_destroy(datos);

		return 0;
	}

	int cant_vieja = config_get_int_value(datos, clave);

	int cantidad_act = cant_vieja - 1;

	if(cantidad_act == 0) {

		 config_remove_key(datos, clave);

	} else {

		char* cantidad_nueva = string_itoa(cantidad_act);

		config_set_value(datos, clave, cantidad_nueva);

	}

	config_save(datos);


	config_destroy(datos);

	if(cantidad_nueva != NULL) {
		free(cantidad_nueva);
	}

	return 0;

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

	char* rutameta = concat_string(path, "/Metadata.bin");

	FILE* file;

	file = fopen(rutameta, "w");

	char datos[40] = "DIRECTORY=N\nSIZE=0\nBLOCKS=[]\nOPEN=N";

	fwrite(&datos, sizeof(char), 40, file);
	fflush(file);
	fclose(file);

	free(rutameta);

}

char* pos_a_clave(uint32_t x, uint32_t y) {


	char* posX = string_itoa(x);
	char* posY = string_itoa(y);

	char* clave = concat_string(posX, "-");
	char* clave_final = concat_string(clave, posY);

	log_debug(logger, "%s", clave_final);

	free(posX);
	free(posY);
	free(clave);

	return clave_final;

}

void cerrar_archivo(char* path) {

	char* rutameta = concat_string(path, "/Metadata.bin");

	t_config* metadata = leer_metadata(rutameta);

	config_set_value(metadata, "OPEN", "N");

	config_save(metadata);
	destruir_metadata(metadata);

	free(rutameta);
}

int chequear_lleno(char* path, size_t size, uint32_t cantidad_caracteres_a_sumar) {

	const int tamanio_pos = 5;
	int cantidad_claves = 0;
	int tamanio_total;

	struct stat statbuf;

	stat(path, &statbuf);
	tamanio_total = statbuf.st_size;

	tamanio_total += cantidad_caracteres_a_sumar;

	if(tamanio_total <= size) {
		free(path);
		return 0;
	}

	if(tamanio_total > size) {
		free(path);
		return 1;
	}

	log_error(logger, "Hay un error en el bloque %s", path);
	free(path);
	return -1;
}

int actualizar_bitmap(off_t bloque) {

	char block[2];

	sprintf(block, "%d", bloque);

	if(chequear_ocupado(bloque)) {

		bitarray_set_bit(bitarray, bloque);
		return 0;
	}

	else {
		bitarray_clean_bit(bitarray, bloque);
		return 1;
	}

}

// esta función devuleve los bloques en un array de strings
char** obtener_bloques(char* path) {

	char** bloques = NULL;
	int i = 0;

	char* metadataPath = "/Metadata.bin";

	char* ruta = concat_string(path, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	bloques = config_get_array_value(metadata, "BLOCKS");

	destruir_metadata(metadata);

	free(ruta);

	return bloques;
}

//chequea si esta el bloque disponible del array de bloques del metadata
int chequear_bloque_disponible(int bloque) {

	struct stat statbuf;
	char bloque_string[2];
	size_t tamanio;
	sprintf(bloque_string, "%d", bloque);

	char* ruta = concat_string(ruta_punto_montaje, "/Blocks/");
	char* ruta_medio = concat_string(ruta, bloque_string);
	char* ruta_final = concat_string(ruta_medio, ".bin");

	stat(ruta_final, &statbuf);
	tamanio = statbuf.st_size;

	if(tamanio == 0) {
		free(ruta);
		free(ruta_medio);
		free(ruta_final);
		return 1;
	}

	free(ruta);
	free(ruta_medio);
	free(ruta_final);
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
	char* nuevos_bloques_final = NULL;
	char* nuevos_bloques_medio = NULL;

//TODO: arreglar repeticion logica

	char* metadataPath = "/Metadata.bin";

	char* ruta = concat_string(path, metadataPath);

	t_config* metadata = leer_metadata(ruta);

	bloques = config_get_string_value(metadata, "BLOCKS");
	bloques_fixed = remove_char(bloques);

	bloque_disponible = buscar_bloque_disponible();
	sprintf(bloque_add, "%d", bloque_disponible);

	if(strlen(bloques_fixed) == 1) {
		nuevos_bloques = concat_string(bloques_fixed, bloque_add);
		nuevos_bloques_final = concat_string(nuevos_bloques, "]");

	}

	else {
		nuevos_bloques = concat_string(bloques_fixed, ",");
		nuevos_bloques_medio = concat_string(nuevos_bloques, bloque_add);
		nuevos_bloques_final = concat_string(nuevos_bloques_medio, "]");
	}

	config_set_value(metadata, "BLOCKS", nuevos_bloques_final);

	config_save(metadata);
	destruir_metadata(metadata);

	free(nuevos_bloques);
	free(nuevos_bloques_medio);
	free(nuevos_bloques_final);
	free(ruta);

	return bloque_disponible;

}

void quitar_bloque(char* path, int bloque) {

	char** bloques;
	char** bloques_nuevos;
	char* bloque_string = string_itoa(bloque);
	int i = 0;
	int j = 0;
	int cantidad_total = 0;
	int tamanio_bloques = 0;
	//TODO: arreglar repeticion logica


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


	while(i < cantidad_total) {
		string_append(&array_armado, bloques_nuevos[i]);

		if(i + 1 != cantidad_total) {
			string_append(&array_armado, ",");
		}
		i++;
	}

	string_append(&array_armado, "]");

	config_set_value(metadata, "BLOCKS", array_armado);

	config_save(metadata);
	destruir_metadata(metadata);

	free(bloques);
	free(array_armado);
	free(bloques_nuevos);


}

char* remove_char(char* string) {
	char* nuevo_string = malloc(strlen(string));
	int i = 0;
	while (string[i] != ']') {
		nuevo_string[i] = string[i];
		i++;
	}

	nuevo_string[i] = '\0';
	return nuevo_string;
}


int chequear_ocupado(int bloque) {

	char bloque_string[2];
	sprintf(bloque_string, "%d", bloque);

	char* ruta = concat_string(ruta_punto_montaje, "/Blocks/");
	char* ruta_media = concat_string(ruta, bloque_string);
	char* ruta_bloque = concat_string(ruta_media, ".bin");

	free(ruta);
	free(ruta_media);

	return chequear_lleno(ruta_bloque, 1, 1);
}

void actualizar_bitmap_pokemon(char* path, char* nombre_pokemon) {

	char** bloques;
	int posicion_array = 0;
	int maximo_array = 0;
	int bloques_maximos = 0;
	t_config* metadata = NULL;

	char* path_metadata = concat_string(ruta_punto_montaje, "/Metadata/Metadata.bin");

	pthread_mutex_lock(&mx_open);

	metadata = config_create(path_metadata);

	bloques_maximos = config_get_int_value(metadata, "BLOCKS");

	bloques = obtener_bloques(path);

	int bloques_ent[bloques_maximos];

	config_destroy(metadata);

	pthread_mutex_unlock(&mx_open);

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

	liberar_lista_de_punteros(bloques);

	free(path_metadata);
}

t_list* leer_bloques_pokemon(char* path) {
	char* path_bloques = concat_string(ruta_punto_montaje, "/Blocks/");

	char** bloques = obtener_bloques(path);
	t_config* bloque;

	lista_coordenadas = list_create();

	for(int i = 0; bloques[i] != NULL; i++){

		char* ruta = concat_string(path_bloques, bloques[i]);
		char* ruta_final = concat_string(ruta, ".bin");

		bloque = config_create(ruta_final);
		t_dictionary* dict = bloque -> properties;
		dictionary_iterator(dict, agregar_coordenadas);

		free(ruta);
		free(ruta_final);
	}
	config_destroy(bloque);
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

	liberar_lista_de_punteros(coords_separated);
}

char* concat_string(char* string, char* otro_string) {
	char* str = (char *) malloc(1 + strlen(otro_string)+ strlen(string));
	strcpy(str, string);
	strcat(str, otro_string);

	return str;
}

void liberarListaDePunteros(char** list) {
	int i = 0;
	while(list[i] != NULL) {
		free(list[i]);
		i++;
	}
	free(list);
}

//int cantidad_de_posiciones(char* bloque){
//	return (sizeof(bloque) / sizeof(t_coords_con_cant));
//}

void liberar_lista_de_punteros(char** list){
	int i = 0;
	while(list[i] != NULL) {
		free(list[i]);
		i++;
	}
	free(list);
}

void actualizar_size_metadata(char* path) {

	char* metadataPath = "/Metadata.bin";

	char* ruta = concat_string(path, metadataPath);

	struct stat statbuf;
	int valor_nuevo = 0;
	int tamanio_total = 0;
	char* ruta_bloque_inicial = NULL;
	char* ruta_bloque_mid = NULL;
	char* ruta_bloque_final = NULL;

	t_config* metadata = config_create(ruta);

	int i = 0;
	int tamanio_bloques = 0;
	char** bloques = obtener_bloques(path);

	while(bloques[i] != NULL) {
			tamanio_bloques++;
			i++;
		}

	for( i = 0; i < tamanio_bloques; i++) {
		ruta_bloque_inicial = concat_string(ruta_punto_montaje, "/Blocks/");
		ruta_bloque_mid = concat_string(ruta_bloque_inicial, bloques[i]);
		ruta_bloque_final = concat_string(ruta_bloque_mid, ".bin");


		stat(ruta_bloque_final, &statbuf);
		tamanio_total += statbuf.st_size;

		free(ruta_bloque_inicial);
		free(ruta_bloque_mid);
		free(ruta_bloque_final);
	}

	char* valor_string = string_itoa(tamanio_total);

	config_set_value(metadata, "SIZE", valor_string);

	config_save(metadata);
	config_destroy(metadata);

	if(bloques != NULL) {
		liberar_lista_de_punteros(bloques);
	}

	free(valor_string);
	free(ruta);

}


void desfragmentar_bloques(char* ruta_pokemon, int bloque) {

	char** bloques_pok = obtener_bloques(ruta_pokemon);
	int ultimo = ultimo_bloque(bloques_pok);
	char* linea_a_reacomodar = NULL;
	char* bloque_string = string_itoa(bloque);
	int tamanio = 0;
	int tamanio_linea = 0;
	t_config* metadata;
	int block_size = 0;

	char* ruta_metadata = concat_string(ruta_punto_montaje, "/Metadata/Metadata.bin");
	metadata = config_create(ruta_metadata);
	block_size = config_get_int_value(metadata, "BLOCK_SIZE");
	config_destroy(metadata);

	char* ruta;
	char* ruta_media;
	char* ruta_final;

	struct stat statbuf;

	ruta = concat_string(ruta_punto_montaje, "/Blocks/");
	ruta_media = concat_string(ruta, bloque_string);
	ruta_final = concat_string(ruta_media, ".bin");


	char* ruta_final_cpy = malloc(strlen(ruta_final) + 1);
	strcpy(ruta_final_cpy,ruta_final);

	stat(ruta_final, &statbuf);
	tamanio = statbuf.st_size;

	if(ultimo != bloque && ultimo != -1) {

		linea_a_reacomodar = obtener_primera_linea(ultimo);
		tamanio_linea = strlen(linea_a_reacomodar);
		int esta_lleno = chequear_lleno(ruta_final, block_size, tamanio_linea);

		if(!esta_lleno) {

			agregar_linea(ruta_final_cpy, linea_a_reacomodar);
		}

		free(linea_a_reacomodar);
		free(bloques_pok);
	}

	free(ruta);
	free(ruta_media);
	free(ruta_final_cpy);
	free(ruta_metadata);

}

int ultimo_bloque(char** bloques) {
	int i = 0;
	int bloque_int;

	while(bloques[i] != NULL) {
		i++;
	}
	i--;

	if(i == -1) {

		return i;

	} else {

		bloque_int = atoi(bloques[i]);
		return bloque_int;
	}
}

int obtener_primera_linea(int bloque) {

	char* ruta;
	char* ruta_media;
	char* ruta_final;
	t_config* metadata;
	int block_size = 0;
	char* clave;

	char* ruta_metadata = concat_string(ruta_punto_montaje, "/Metadata/Metadata.bin");
	metadata = config_create(ruta_metadata);
	block_size = config_get_int_value(metadata, "BLOCK_SIZE");
	config_destroy(metadata);

	char* bloque_string = string_itoa(bloque);

	ruta = concat_string(ruta_punto_montaje, "/Blocks/");
	ruta_media = concat_string(ruta, bloque_string);
	ruta_final = concat_string(ruta_media, ".bin");

	char* buffer = malloc(sizeof(char) * block_size);

	FILE* file = fopen(ruta_final, "r+");

	fseek(file, 0, SEEK_SET);
	fgets(buffer, sizeof(char) * block_size, file);

	fclose(file);

	clave = get_clave(buffer);

	t_config* bloque_config = config_create(ruta_final);

	config_remove_key(bloque_config, clave);

	config_save(bloque_config);
	config_destroy(bloque_config);

	free(ruta);
	free(ruta_media);
	free(ruta_final);
	free(ruta_metadata);
	free(clave);

	return buffer;
}

void agregar_linea(char* path, char* linea) {

	FILE* file = fopen(path, "r+");

	fseek(file, 0, SEEK_END);
	fputs(linea, file);
	fclose(file);

}

char* get_clave(char* linea) {

	int i = 0;
	char* clave = malloc(strlen(linea));

	while(linea[i] != '=') {
		clave[i] = linea[i];
		i++;
	}

	clave[i] = '\0';

	return clave;
}




