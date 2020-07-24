/*
 * procesamiento_mensajes.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "procesamiento_mensajes.h"

pthread_mutex_t mx_bitmap;


void procesarID(t_paquete* paquete){

	t_id* id = paquete -> buffer -> stream;
	log_debug(logger, "Recibí el ID: %d", *id);
	free(id);
	free(paquete->buffer);
	free(paquete);
}

void procesarNew(t_paquete* paquete){

	int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");
	void* ptr_stream = paquete->buffer->stream;

	t_new_pokemon* pok = deserializarNewPokemon(paquete -> buffer);
	log_debug(logger, "despues de deserializar al pokemon");

	char* nombre_pokemon = pok -> pokemon -> name;
	t_coords* coords = pok -> coords;
	uint32_t cantidad = pok -> cantidad;

	t_pokemon* pokemon = pok -> pokemon;
	uint32_t posX = coords -> posX;
	uint32_t posY = coords -> posY;

	log_info(logger, "[NEW_POKEMON] -> %d %s en (%d,%d)", cantidad, pok -> pokemon -> name, posX, posY);

	char* path_clave;

	char* path_files = concat_string(ruta_punto_montaje, "/Files");

	char* ruta_pokemon = verificar_pokemon(path_files, nombre_pokemon, 1);

	free(path_files);
	while(archivo_en_uso(ruta_pokemon)) {

		log_error(logger, "El archivo ya esta abierto por otro proceso y no se puede abrir, reintentando en %d segundos", tiempo_reintento);
		sleep(tiempo_reintento);
	}

	int bloque;

	char* clave = pos_a_clave(posX, posY);

	pthread_mutex_lock(&mx_bitmap);

	path_clave = path_para_clave(clave, ruta_pokemon, cantidad, MODIFICAR_CLAVE, nombre_pokemon, &bloque);

	agregar_posicion_y_cantidad(coords, cantidad, path_clave);

	actualizar_bitmap_pokemon(ruta_pokemon, nombre_pokemon);


	pthread_mutex_unlock(&mx_bitmap);

	sleep(tiempo_retardo);

	char* ruta_mx = concat_string(ruta_pokemon, "/Metadata.bin");
	pthread_mutex_t* mx = (pthread_mutex_t*) dictionary_get(mx_dict, ruta_mx);
	pthread_mutex_lock(mx);

	cerrar_archivo(ruta_pokemon);


	actualizar_size_metadata(ruta_pokemon);

	free(ruta_mx);
	pthread_mutex_unlock(mx);

	free(ruta_pokemon);
	free(path_clave);

	int conexion_con_broker = abrirUnaConexionGameCard(config);

	t_appeared_pokemon* app_pokemon = appeared_pokemon(pokemon, posX, posY);
	uint32_t bytes;
	uint32_t bytes_paquete;

	void* serialized_appeared_pokemon = serializarAppearedPokemon(app_pokemon, &bytes);
	void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_appeared_pokemon, bytes, paquete -> id, &bytes_paquete);
	int status = send_msg(conexion_con_broker, a_enviar , bytes_paquete);
	log_info(logger, "Se enviará un [CID:%d][APPEARED_POKEMON] -> %s en (%d, %d)", paquete -> id ,app_pokemon -> pokemon -> name, app_pokemon -> coords -> posX, app_pokemon -> coords -> posY);
	close(conexion_con_broker);

	free(clave);

	free(app_pokemon -> coords);
	free(app_pokemon);
	free(serialized_appeared_pokemon);
	free(a_enviar);

	free(pok -> pokemon -> name);
	free(pok -> pokemon);
	free(pok -> coords);
	free(pok);

	free(ptr_stream);
	free(paquete->buffer);
	free(paquete);
}

void procesarCatch(t_paquete* paquete){

	int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");
	void* ptr_stream = paquete->buffer->stream;

	//FILE* archivo = ruta_del_archivo;

	t_catch_pokemon* pok = deserializarCatchPokemon(paquete -> buffer);

	char* nombre_pokemon = pok -> pokemon -> name;
	t_coords* coords = pok -> coords;

	t_pokemon* pokemon = pok -> pokemon;
	uint32_t posX = coords -> posX;
	uint32_t posY = coords -> posY;

	log_info(logger, "[CATCH_POKEMON] -> %s en (%d, %d)", nombre_pokemon, posX, posY);

	t_caught_pokemon* cau_pokemon;

	char* path_clave;

	char* path_files = concat_string(ruta_punto_montaje, "/Files");

	char* ruta_pokemon = verificar_pokemon(path_files, nombre_pokemon, 0);

	free(path_files);


	if(ruta_pokemon != NULL) {
		while(archivo_en_uso(ruta_pokemon)) {

			log_error(logger, "El archivo ya esta abierto por otro proceso y no se puede abrir, reintentando en %d segundos", tiempo_reintento);
			sleep(tiempo_reintento);
		}

		int bloque = 0;
		int* bloque_p = &bloque;
		char* clave = pos_a_clave(posX, posY);

		pthread_mutex_lock(&mx_bitmap);

		path_clave = path_para_clave(clave, ruta_pokemon, 0, BUSCAR_CLAVE, nombre_pokemon, bloque_p);
		free(clave);

		if(path_clave != NULL) {
			cau_pokemon = caught_pokemon(YES);
			disminuir_cantidad(coords, path_clave);
			char* mx_path = concat_string(ruta_pokemon, "/Metadata.bin");
			pthread_mutex_t* mx = (pthread_mutex_t*) dictionary_get(mx_dict, mx_path);
			pthread_mutex_lock(mx);
			desfragmentar_bloques(ruta_pokemon, bloque);
			actualizar_size_metadata(ruta_pokemon);
			pthread_mutex_unlock(mx);
			free(path_clave);
			free(mx_path);
		} else {
			log_error(logger, "No hay un pokemon en esa posicion");
			cau_pokemon = caught_pokemon(NO);
		}

		actualizar_bitmap_pokemon(ruta_pokemon, nombre_pokemon);
		pthread_mutex_unlock(&mx_bitmap);
		sleep(tiempo_retardo);

		char* ruta_mx = concat_string(ruta_pokemon, "/Metadata.bin");
		pthread_mutex_t* mx = (pthread_mutex_t*) dictionary_get(mx_dict, ruta_mx);

		pthread_mutex_lock(mx);
		cerrar_archivo(ruta_pokemon);
		free(ruta_mx);
		pthread_mutex_unlock(mx);

		free(ruta_pokemon);

	} else {
		cau_pokemon = caught_pokemon(NO);
		sleep(tiempo_retardo);
	}
	int conexion_con_broker = abrirUnaConexionGameCard(config);

	uint32_t bytes;
	uint32_t bytes_paquete;

	void* serialized_caught_pokemon = serializarCaughtPokemon(&cau_pokemon, &bytes);
	void* a_enviar = crear_paquete_con_id_correlativo(CAUGHT_POKEMON, serialized_caught_pokemon, bytes, paquete -> id, &bytes_paquete);
	int status = send_msg(conexion_con_broker, a_enviar , bytes_paquete);
	log_info(logger, "Se enviará [CID:%d][CAUGHT_POKEMON] -> %s", paquete -> id ,cau_pokemon == YES? "Ok": "Fail");

	close(conexion_con_broker);
	free(a_enviar);

	free(pok -> pokemon -> name);
	free(pok -> pokemon);
	free(pok -> coords);
	free(pok);

	free(ptr_stream);
	free(paquete->buffer);
	free(paquete);

}

void procesarGet(t_paquete* paquete){

	void* ptr_stream = paquete->buffer->stream;
	t_get_pokemon* pok = deserializarPokemon(&(paquete -> buffer));
	char* nombre_pokemon = pok -> name;

	int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");


	char* path_files = concat_string(ruta_punto_montaje, "/Files");

	char* ruta_pokemon = verificar_pokemon(path_files, nombre_pokemon, 0);

	free(path_files);
	t_list* lista_de_coordenadas = NULL;
	uint32_t cantidad_de_coordenadas = 0;

	log_info(logger, "[GET POKEMON] -> %s", nombre_pokemon);

	t_localized_pokemon* loc_pokemon = NULL;

	if(ruta_pokemon != NULL) {
		while(archivo_en_uso(ruta_pokemon)) {
			log_error(logger, "El archivo ya se encuientra abierto, reintentando en %i segundos", tiempo_reintento);
			sleep(tiempo_reintento);
		}

		lista_de_coordenadas = leer_bloques_pokemon(ruta_pokemon);

		if(lista_de_coordenadas != NULL && !list_is_empty(lista_de_coordenadas)) {
			cantidad_de_coordenadas = list_size(lista_de_coordenadas);
			t_coords** coordenadas = malloc(sizeof(t_coords*) * cantidad_de_coordenadas);

			for(int i = 0; i < list_size(lista_de_coordenadas); i++){
				t_coords_con_cant* coordenadas_y_cantidad = list_get(lista_de_coordenadas, i);
				coordenadas[i] = malloc(sizeof(t_coords));
				memcpy(coordenadas[i], coordenadas_y_cantidad -> coordenadas, sizeof(t_coords));
			}

			list_destroy_and_destroy_elements(lista_de_coordenadas, liberar_coords_con_cantidad);

			loc_pokemon = localized_pokemon(pok, cantidad_de_coordenadas, coordenadas);
			sleep(tiempo_retardo);

			char* ruta_mx = concat_string(ruta_pokemon, "/Metadata.bin");
			pthread_mutex_t* mx = (pthread_mutex_t*) dictionary_get(mx_dict, ruta_mx);
			pthread_mutex_lock(mx);
			cerrar_archivo(ruta_pokemon);
			free(ruta_mx);
			pthread_mutex_unlock(mx);

		} else {
			loc_pokemon = localized_pokemon(pok, 0, NULL);
			sleep(tiempo_retardo);

			char* ruta_mx = concat_string(ruta_pokemon, "/Metadata.bin");
			pthread_mutex_t* mx = (pthread_mutex_t*) dictionary_get(mx_dict, ruta_mx);
			pthread_mutex_lock(mx);
			cerrar_archivo(ruta_pokemon);
			free(ruta_mx);
			pthread_mutex_unlock(mx);
		}
	} else {
		loc_pokemon = localized_pokemon(pok, 0, NULL);
		sleep(tiempo_retardo);
	}

	int conexion_con_broker = abrirUnaConexionGameCard(config);

	if(conexion_con_broker == CANT_CONNECT){
		log_error(logger, "No se pudo establecer conexión con el broker");
	} else {
		uint32_t bytes;
		uint32_t bytes_paquete;

		void* serialized_localized_pokemon = serializarLocalizedPokemon(loc_pokemon, &bytes);
		void* a_enviar = crear_paquete_con_id_correlativo(LOCALIZED_POKEMON, serialized_localized_pokemon, bytes, paquete -> id, &bytes_paquete);
		int status = send_msg(conexion_con_broker, a_enviar , bytes_paquete);
		log_info(logger, "Se enviará [CID:%d][LOCALIZED_POKEMON] -> %s", paquete -> id, loc_pokemon -> pokemon -> name);
		close(conexion_con_broker);

		free(ruta_pokemon);
		free(loc_pokemon);
		free(serialized_localized_pokemon);
		free(a_enviar);
	}

	free(nombre_pokemon);
	free(pok);

	free(ptr_stream);
	free(paquete->buffer);
	free(paquete);
}

void liberar_coords_con_cantidad(t_coords_con_cant* coords_con_cant){
	free(coords_con_cant -> coordenadas);
	free(coords_con_cant);
}

