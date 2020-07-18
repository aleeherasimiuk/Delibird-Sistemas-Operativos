/*
 * procesamiento_mensajes.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "procesamiento_mensajes.h"


void procesarID(t_paquete* paquete){

 t_id* id = paquete -> buffer -> stream;
 log_debug(logger, "Recibí el ID: %d", *id);
}

void procesarNew(t_paquete* paquete){

	int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");
	int i;

	t_new_pokemon* pok = deserializarNewPokemon(paquete -> buffer);
	log_debug(logger, "despues de deserializar al pokemon");

	char* nombre_pokemon = pok -> pokemon -> name;
	t_coords* coords = pok -> coords;
	uint32_t cantidad = pok -> cantidad;

	t_pokemon* pokemon = pok -> pokemon;
	uint32_t posX = coords -> posX;
	uint32_t posY = coords -> posY;

	char* path_clave;

	char* ruta_pokemon = verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files", nombre_pokemon, 1);
	while(archivo_en_uso(ruta_pokemon)) {

		log_debug(logger, "esperando a que cierren el archivo");
		sleep(tiempo_reintento);
	}


	char* clave = pos_a_clave(posX, posY);
	path_clave = path_para_clave(clave, ruta_pokemon, cantidad, MODIFICAR_CLAVE);

	agregar_posicion_y_cantidad(coords, cantidad, path_clave);

	actualizar_bitmap_pokemon(ruta_pokemon);

	sleep(tiempo_retardo);

	cerrar_archivo(ruta_pokemon);

	free(ruta_pokemon);

	free(path_clave);


	for(i = 0; i < (pok -> cantidad); i++){

		int conexion_con_broker = abrirUnaConexionGameCard(config);

		t_appeared_pokemon* app_pokemon = appeared_pokemon(pokemon, posX, posY);

		uint32_t bytes;
		uint32_t bytes_paquete;


		void* serialized_appeared_pokemon = serializarAppearedPokemon(app_pokemon, &bytes);
		void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_appeared_pokemon, bytes, paquete -> id, &bytes_paquete);
		int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);
		log_info(logger, "envie un APPEARED al broker con status: %d", status);
		close(conexion_con_broker);

		free(app_pokemon -> coords);
		free(app_pokemon);
		free(serialized_appeared_pokemon);
		free(a_enviar);
	}

	free(pok -> pokemon -> name);
	free(pok -> pokemon);
	free(pok -> coords);
	free(pok);

	free(paquete -> buffer);
	free(paquete);

}

void procesarCatch(t_paquete* paquete){

	int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");

	//FILE* archivo = ruta_del_archivo;

	t_catch_pokemon* pok = deserializarCatchPokemon(paquete -> buffer);

	char* nombre_pokemon = pok -> pokemon -> name;
	t_coords* coords = pok -> coords;

	t_pokemon* pokemon = pok -> pokemon;
	uint32_t posX = coords -> posX;
	uint32_t posY = coords -> posY;

	t_caught_pokemon* cau_pokemon;

	char* path_clave;

	char* ruta_pokemon = verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files", nombre_pokemon, 0);

	if(ruta_pokemon != NULL) {
		while(archivo_en_uso(ruta_pokemon)) {

			log_info(logger, "esperando a que cierren el archivo");
			sleep(tiempo_reintento);
		}

		char* clave = pos_a_clave(posX, posY);
		path_clave = path_para_clave(clave, ruta_pokemon, 0, BUSCAR_CLAVE);

		if(path_clave != NULL) {
			cau_pokemon = caught_pokemon(YES);
			disminuir_cantidad(coords, path_clave);
			free(path_clave);
		} else {
			log_error(logger, "No hay un pokemon en esa posicion");
			cau_pokemon = caught_pokemon(NO);
		}

		actualizar_bitmap_pokemon(ruta_pokemon);
		sleep(tiempo_retardo);
		cerrar_archivo(ruta_pokemon);

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
	int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);
	log_info(logger, "envie un CAUGHT al broker con status: %d", status);
	close(conexion_con_broker);
	free(a_enviar);

	free(pok -> pokemon);
	free(pok -> coords);
	free(pok);
}

void procesarGet(t_paquete* paquete){

	t_get_pokemon* pok = deserializarPokemon(&(paquete -> buffer));
	char* nombre_pokemon = pok -> name;

	int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");

	char* ruta_pokemon = verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files", nombre_pokemon, 0);
	t_list* lista_de_coordenadas = NULL;
	uint32_t cantidad_de_coordenadas;

	t_localized_pokemon* loc_pokemon;

	if(ruta_pokemon != NULL) {
		while(archivo_en_uso(ruta_pokemon)) {
			log_error(logger, "el archivo está abierto por otro proceso y no se puede abrir, reintentando en %i segundos", tiempo_reintento);
			sleep(tiempo_reintento);
		}

		lista_de_coordenadas = leer_bloques_pokemon(ruta_pokemon);
		cantidad_de_coordenadas = list_size(lista_de_coordenadas);
		t_coords** coordenadas = malloc(sizeof(t_coords*) * cantidad_de_coordenadas);

		for(int i = 0; i < list_size(lista_de_coordenadas); i++){
			t_coords_con_cant* coordenadas_y_cantidad = list_get(lista_de_coordenadas, i);
			coordenadas[i] = malloc(sizeof(t_coords));
			coordenadas[i] = coordenadas_y_cantidad -> coordenadas;
		}

		loc_pokemon = localized_pokemon(pok, cantidad_de_coordenadas, coordenadas);

		sleep(tiempo_retardo);
		cerrar_archivo(ruta_pokemon);

	} else {
		loc_pokemon = localized_pokemon(pok, 0, NULL);
	}

	int conexion_con_broker = abrirUnaConexionGameCard(config);
	if(conexion_con_broker == CANT_CONNECT){
		log_info(logger, "no se pudo establecer conexión con el broker");
	}else {
		uint32_t bytes;
		uint32_t bytes_paquete;

		void* serialized_localized_pokemon = serializarLocalizedPokemon(loc_pokemon, &bytes);
		void* a_enviar = crear_paquete_con_id_correlativo(LOCALIZED_POKEMON, serialized_localized_pokemon, bytes, paquete -> id, &bytes_paquete);
		int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);
		log_info(logger, "envie un LOCALIZED al broker con status: %d", status);
		close(conexion_con_broker);

		if(lista_de_coordenadas != NULL)
			list_destroy_and_destroy_elements(lista_de_coordenadas, destruir_elementos);

		free(ruta_pokemon);
		free(loc_pokemon);
		free(serialized_localized_pokemon);
		free(a_enviar);
	}

	free(nombre_pokemon);
	free(pok);
}

void destruir_elementos(void* elemento){
	free(elemento);
}
