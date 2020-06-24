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

	log_debug(logger, "llegue hasta las deserializacion");

	char* nombre_pokemon = pok -> pokemon -> name;
	t_coords* coords = pok -> coords;
	uint32_t cantidad = pok -> cantidad;

	t_pokemon* pokemon = pok -> pokemon;
	uint32_t posX = pok -> coords -> posX;
	uint32_t posY = pok -> coords -> posY;







	while(1){
		//if(!archivo_en_uso(archivo)){
			//verificar_pokemon(archivo, nombre_pokemon);
			//agregar_posicion_y_cantidad(coords,cantidad);
			//sleep(tiempo_retardo);
			//fclose(archivo);

			for(i = 0; i < (pok -> cantidad); i++){

				int conexion_con_broker = abrirUnaConexionGameCard(config);

				t_appeared_pokemon* app_pokemon = appeared_pokemon(pokemon, posX, posY);

				log_debug(logger, "llegue hasta luego de armar el appeared");
				uint32_t* bytes;
				uint32_t bytes_paquete;

				log_debug(logger, "llegue hasta antes de serializar");

				void* serialized_appeared_pokemon = serializarAppearedPokemon(app_pokemon, &bytes);

				log_debug(logger, "llegue hasta antes de crear paquete con id correlativo");

				void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, serialized_appeared_pokemon, bytes, paquete -> id, &bytes_paquete);

				log_debug(logger, "llegue hasta antes del send");

				int status = send(conexion_con_broker, a_enviar , bytes_paquete , 0);

				log_debug(logger, "status: %i", status);

				close(conexion_con_broker);


			}

			break;

	}




	free(pok -> pokemon -> name);
	free(pok -> pokemon);
	free(paquete-> buffer);
	log_debug(logger, "pude deserializar el New Pokemon");
}

void procesarCatch(t_paquete* paquete){

	t_catch_pokemon* pok = deserializarCatchPokemon(paquete -> buffer);
	log_debug(logger, "pude deserializar el Catch Pokemon");
}

/*void procesarGet(t_paquete* paquete){
	t_appeared_pokemon* pok = deserializarGetPokemon(paquete -> buffer);
	log_debug(logger, "pude deserializar el Get Pokemon");
}*/
