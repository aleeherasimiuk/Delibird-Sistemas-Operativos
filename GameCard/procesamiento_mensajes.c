/*
 * procesamiento_mensajes.c
 *
 *  Created on: 23 jun. 2020
 *      Author: utnso
 */

#include "procesamiento_mensajes.h"


void procesarID(t_paquete* paquete){

 t_id* id = paquete -> buffer -> stream;
 log_debug(logger, "Recibí el ID: %d", id);
}

void procesarNew(t_paquete* paquete){
	 //char* ruta_del_archivo = strcat(ruta_punto_montaje,"/Files");
	 int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	 int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");
	 int i;

	 //FILE* archivo = ruta_del_archivo;

	 t_new_pokemon* pok = deserializarNewPokemon(paquete -> buffer);

	 char* nombre_pokemon = pok -> pokemon -> name;
	 t_coords* coords = pok -> coords;
	 uint32_t cantidad = pok -> cantidad;

	 t_pokemon* pokemon = pok -> pokemon;
	 uint32_t posX = coords -> posX;
	 uint32_t posY = coords -> posY;

	 while(1){
	  //if(!archivo_en_uso(path)){
	   //verificar_pokemon(path, nombre_pokemon);
	   //agregar_posicion_y_cantidad(coords,cantidad);
	   //sleep(tiempo_retardo);
		 //fclose(archivo);

	   for(i = 0; i < (pok -> cantidad); i++){

		int conexion_con_broker = abrirUnaConexionGameCard(config);

		t_appeared_pokemon* app_pokemon = appeared_pokemon(pokemon, posX, posY);

		uint32_t bytes;
		uint32_t bytes_paquete;


		void* serialized_appeared_pokemon = serializarAppearedPokemon(app_pokemon, &bytes);
		void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_appeared_pokemon, bytes, paquete -> id, &bytes_paquete);
		int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);
		log_debug(logger, "envie un mensaje al broker con status: %d", status);
		close(conexion_con_broker);

		free(app_pokemon -> coords);
		free(app_pokemon);
		free(serialized_appeared_pokemon);
		free(a_enviar);
		sleep(2);
	   }

	   break;
	 }
	 free(pok -> pokemon -> name);
	 free(pok -> pokemon);
	 free(pok);

}

void procesarCatch(t_paquete* paquete){
	 //char* ruta_del_archivo = strcat(ruta_punto_montaje,"/Files");
	 int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
	 int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");

	 //FILE* archivo = ruta_del_archivo;

	 t_catch_pokemon* pok = deserializarCatchPokemon(paquete -> buffer);

	 char* nombre_pokemon = pok -> pokemon -> name;
	 t_coords* coords = pok -> coords;

	 t_pokemon* pokemon = pok -> pokemon;
	 uint32_t posX = coords -> posX;
	 uint32_t posY = coords -> posY;

	 while(1){
	  //if(!archivo_en_uso(archivo)){
	   //verificar_pokemon(archivo, nombre_pokemon);
	   //agregar_posicion_y_cantidad(coords,cantidad);
	   //sleep(tiempo_retardo);
	   //fclose(archivo);


	   int conexion_con_broker = abrirUnaConexionGameCard(config);

	   t_caught_pokemon* cau_pokemon = caught_pokemon(YES);

	   uint32_t bytes;
	   uint32_t bytes_paquete;

	   void* serialized_caught_pokemon = serializarCaughtPokemon(&cau_pokemon, &bytes);
	   void* a_enviar = crear_paquete_con_id_correlativo(CAUGHT_POKEMON, serialized_caught_pokemon, bytes, paquete -> id, &bytes_paquete);
	   int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);
	   log_debug(logger, "envie un mensaje al broker con status: %d", status);
	   close(conexion_con_broker);
	   free(serialized_caught_pokemon);
	   free(a_enviar);
	   break;
	 }
	 free(pok -> pokemon -> name);
	 free(pok -> pokemon);
	 free(pok);
}

void procesarGet(t_paquete* paquete){

	t_get_pokemon* pok = deserializarPokemon(&(paquete -> buffer));
	char* nombre_pokemon = pok -> name;

	while(1){
		int tiempo_reintento = config_get_int_value(config,"TIEMPO_REINTENTO_OPERACION");
		int tiempo_retardo = config_get_int_value(config,"TIEMPO_RETARDO_OPERACION");
		//int contador_coordenadas; se va a usar cuando se traigan las coordenadas del archivo, ahora estamos poniendo coords al azar para probar mensajes
		//if(!archivo_en_uso(archivo)){
		//verificar_pokemon(archivo, nombre_pokemon);
		//agregar_posicion_y_cantidad(coords,cantidad);
		//sleep(tiempo_retardo);
		//fclose(archivo);
		int conexion_con_broker = abrirUnaConexionGameCard(config);


		t_coords* coords1 = crear_coordenadas_from_int(2,5);

		t_coords* coords2 = crear_coordenadas_from_int(3,5);

		t_coords** array = coords_array(2, coords1, coords2);

		t_localized_pokemon* loc_pokemon = localized_pokemon(pok, 2, array);

		uint32_t bytes;
		uint32_t bytes_paquete;

		void* serialized_localized_pokemon = serializarLocalizedPokemon(loc_pokemon, &bytes);
		void* a_enviar = crear_paquete_con_id_correlativo(LOCALIZED_POKEMON, serialized_localized_pokemon, bytes, paquete -> id, &bytes_paquete);
		int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);
		log_debug(logger, "envie un mensaje al broker con status: %d", status);
		close(conexion_con_broker);
		free(coords1);//
		free(coords2);//	Estos free son de las coordenadas inventadas al azar, cuando las traigamos de los archivos estos free se van a plantear distinto
		free(array);//
		free(loc_pokemon);
		free(serialized_localized_pokemon);
		free(a_enviar);

		break;
	}
	free(pok -> name);
	free(pok);
}
