/*
 * dump_cache.c
 *
 *  Created on: 25 jun. 2020
 *      Author: utnso
 */

#include "dump_cache.h"

void dump_cache(int n){

	log_info(logger, "Generando Dump de Caché");

	FILE* file = txt_open_for_append(dump_path);
	char* hora = obtener_hora();
	char* hora_string = string_from_format("Dump: %s\n", hora);
	char* separacion = guiones(120);
	//printf(separacion);
	//printf(hora_string);
	txt_write_in_file(file, separacion);
	txt_write_in_file(file, hora_string);

	memory_block_t* mem_block = memory;
	int i = 0;

	while(mem_block != NULL){

		void* base = mem_block -> data -> base;
		void* fin = base + (mem_block -> data -> size);
		int size = mem_block -> data -> size;
		char* status = obtener_status(mem_block);
		char libre = mem_block -> data -> status == LIBRE? 'L' : 'X';
		char* string = string_from_format("Particion %d: %06p - %06p\t[%c]\tSize: %db %s\n", i++, base, fin, libre ,size, status);
		txt_write_in_file(file, string);
		//printf(string);
		free(status);
		free(string);

		mem_block = mem_block -> next;
	}

	//printf(separacion);
	txt_write_in_file(file, separacion);
	free(hora);
	free(hora_string);
	free(separacion);
	txt_close_file(file);

}

char* guiones(int cantidad){
	char* guiones = malloc(cantidad + 2);

	for(int i = 0; i < cantidad; i++){
		guiones[i] = '-';
	}

	guiones[cantidad] = '\n';
	guiones[cantidad + 1] = '\0';
	return guiones;
}

char* obtener_hora(){
	time_t tiempo = time(NULL);
	struct tm *tm = localtime(&tiempo);
	char* fecha_y_hora = malloc(sizeof(char) * 20);
	strftime(fecha_y_hora, 20, "%d/%m/%Y %H:%M:%S", tm);

	return fecha_y_hora;
}

char* obtener_status(memory_block_t* mem_block){

	clientes_por_mensaje_t* cli = obtenerMensaje(mem_block -> data -> msg_id);

	char* st;

	if(mem_block -> data -> status == LIBRE){
		st = malloc(sizeof(char));
		strcpy(st, "");
		return st;
	}

	int lru = mem_block -> data -> flag;
	int id  = mem_block -> data -> msg_id;
	int cola = cli -> cola;

	char* queue = queue_name(cola);

	st = string_from_format("%s: %d\tCOLA: %s\t\tID: %d", reemplazo == LRU? "LRU" : "FIFO" ,lru , queue, id);
	return st;
}


