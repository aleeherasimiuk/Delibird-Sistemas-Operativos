/*
 * var_globales_gamecard.h
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */

#ifndef GAMECARD_VAR_GLOBALES_GAMECARD_H_
#define GAMECARD_VAR_GLOBALES_GAMECARD_H_

#include<commons/config.h>
#include<commons/log.h>
#include<commons/bitarray.h>
#include<pthread.h>
#include<commons/collections/dictionary.h>

extern t_config* config;
extern t_bitarray* bitarray;
extern t_log* logger;
extern uint32_t process_id;
extern char* ruta_punto_montaje;
extern uint32_t tiempo_reconexion;
extern pthread_mutex_t mx_open;
extern pthread_mutex_t mx_bitmap;
extern pthread_mutex_t mx_metadata_blocks;
extern t_dictionary* mx_dict;

/*extern typedef struct {
	extern t_coords coordenadas;
	extern uint32_t cantidad;
}t_coords_con_cant;

*/

#endif /* GAMECARD_VAR_GLOBALES_GAMECARD_H_ */
