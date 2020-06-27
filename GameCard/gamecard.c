/*
 * gamecard.c
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#include "gamecard.h"

t_log* logger = NULL;
t_config* config = NULL;
char* ruta_punto_montaje = NULL;

int main() {

	char* logfile;
	uint32_t tiempoReconexion;

	config = leer_config();

	logfile = "/home/utnso/log_gamecard1.txt";//config_get_string_value(config, "LOG_FILE");
	ruta_punto_montaje = "/home/utnso/Escritorio/tall-grass" ; //config_get_string_value(config, "PUNTO_MONTAJE_TALLGRASS");
	tiempoReconexion = 10;   //config_get_int_value(config, "TIEMPO_DE_REINTENTO_CONEXION");
	process_id = 12780;//config_get_int_value(config, "PROCESS_ID");

	logger = iniciar_logger(logfile);

	//archivo_en_uso("/home/utnso/Escritorio/tall-grass/Files/");
//	verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files/", "Charizard");
//	verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files/", "Casdsd");
//	verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files/", "Chfghfgh");
//	verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files/", "sfsdgf");
//	verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files/", "Cdfgwer");
//	verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files/", "Cwerwe");
	t_coords coordenadas;

	coordenadas.posX = 7;
	coordenadas.posY = 4;

	t_coords* coptr = &coordenadas;

	log_debug(logger, "llega hasta aca");

	FILE* file = NULL;

	file = fopen("/home/utnso/Escritorio/tall-grass/Blocks/1.bin", "rb+");

	agregar_posicion_y_cantidad(coptr, 3, file);

	leer_archivo(file);

	fclose(file);

	//verificar_posiciones("/home/utnso/Escritorio/tall-grass/Blocks/1.bin",coordenadas);


	while(1) {
		if(abrirUnaConexionGameCard(config) == CANT_CONNECT)
			intentarReconexionConBroker(logfile, tiempoReconexion,  config);
		else {
			inicializar_gamecard();
			break;
		}
	}
	return 1;
}


void intentarReconexionConBroker(char* logfile, uint32_t tiempo, t_config* config){
	log_debug(logger, "Intentando nueva conexión en %d segundos", tiempo);
	sleep(tiempo);
}

void inicializar_gamecard(void) {
	escucharAlGameboy();
	suscribirGameCardAlBroker();
}

t_log* iniciar_logger(char* logfile) {
	return log_create(logfile, "GameCard", true, LOG_LEVEL_DEBUG);
}

t_config* leer_config(void) {
	return config_create("gamecard.config");
}

