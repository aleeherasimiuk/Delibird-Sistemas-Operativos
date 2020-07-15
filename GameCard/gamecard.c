/*
 * gamecard.c
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#include "gamecard.h"

t_log* logger = NULL;
t_config* config = NULL;
t_bitarray* bitarray = NULL;
char* ruta_punto_montaje = NULL;

int main() {

	char* logfile;

	uint32_t tiempoReconexion;

	config = leer_config();

	logfile = config_get_string_value(config, "LOG_FILE");
	ruta_punto_montaje = config_get_string_value(config, "PUNTO_MONTAJE_TALLGRASS");
	tiempoReconexion = config_get_int_value(config, "TIEMPO_DE_REINTENTO_CONEXION");
	process_id = config_get_int_value(config, "PROCESS_ID");

	logger = iniciar_logger(logfile);

	bitarray = iniciar_bitarray();

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

t_bitarray* iniciar_bitarray(void) {


	char* bitmap_path = NULL;
	t_bitarray* array = NULL;
	struct stat statbuf;
	size_t bitmap_size;
	char* buffer = NULL;

	bitmap_path = "/home/utnso/Escritorio/tall-grass/Metadata/Bitmap.bin";

	stat(bitmap_path, &statbuf);
	bitmap_size = statbuf.st_size;

	FILE* file = open(bitmap_path, O_RDWR);
	//fread(buffer, 1, bitmap_size, file);
	//fclose(file);

	buffer = mmap(NULL, bitmap_size, PROT_WRITE | PROT_READ, MAP_SHARED, file, 0);


	array = bitarray_create_with_mode(buffer, bitmap_size, MSB_FIRST);

	return array;
}

