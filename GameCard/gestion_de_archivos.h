/*
 * gestion_de_archivos.h
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#ifndef GAMECARD_GESTION_DE_ARCHIVOS_H_
#define GAMECARD_GESTION_DE_ARCHIVOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <commons/config.h>
#include <commons/bitarray.h>
#include "../Utils/conexiones.h"
#include "var_globales_gamecard.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <commons/collections/list.h>

#define BUSCAR_CLAVE 1
#define MODIFICAR_CLAVE 0

typedef struct {
	char DIRECTORY;
	char OPEN;
	int SIZE;
	int BLOCKS[];
}METADATA;

t_config* leer_metadata(char*);
void destruir_metadata(t_config*);

//char* obtener_pokemon_del_path(char*);
int cantidad_de_posiciones(char*);

void agregar_coordenadas(char*, void*);

void unir_paths(char*, char*, char**);
int  archivo_en_uso(char*);
char* verificar_pokemon(char*, char*, int);
char* path_para_clave(char*, char*, uint32_t, int, char*);
int agregar_posicion_y_cantidad(t_coords* ,int , char*);
int disminuir_cantidad(t_coords*, char* path);
void obtener_posiciones(char*);
void leer_archivo(FILE* file);
void crear_metadata_archivo(char*);
char* pos_a_clave(u_int32_t, u_int32_t);
void cerrar_archivo(char*);
int chequear_lleno(char*, size_t, uint32_t);
int actualizar_bitmap(off_t);
char** obtener_bloques(char*);
int chequear_bloque_disponible(int);
int buscar_bloque_disponible(void);
int agregar_bloque_disponible(char* path);
void quitar_bloque(char*, int);
char* remove_char(char*);
int chequear_ocupado(int);
void actualizar_bitmap_pokemon(char*, char*);
t_list* leer_bloques_pokemon(char*);
void agregar_coordenadas(char*, void*);
void liberar_lista_de_punteros(char**);
void actualizar_size_metadata(char*);
char* concat_string(char*, char*);

typedef struct {
	t_coords* coordenadas;
	 uint32_t* cantidad;
}t_coords_con_cant;

//void obtener_posiciones(char*);

#endif /* GAMECARD_GESTION_DE_ARCHIVOS_H_ */
