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

	logfile = "/home/utnso/log_gamecard1.txt";//config_get_string_value(config, "LOG_FILE");
	ruta_punto_montaje = "/home/utnso/Escritorio/tall-grass" ; //config_get_string_value(config, "PUNTO_MONTAJE_TALLGRASS");
	tiempoReconexion = 10;   //config_get_int_value(config, "TIEMPO_DE_REINTENTO_CONEXION");
	process_id = 12780;//config_get_int_value(config, "PROCESS_ID");

	logger = iniciar_logger(logfile);


	bitarray = iniciar_bitarray();
	/*t_coords coords;

	coords.posX = 1;
	coords.posY = 2;

	char* clave = "1-2";
	char* path_clave;

	path_clave = path_para_clave(clave, "/home/utnso/Escritorio/tall-grass/Files/bulbasaur");
	agregar_posicion_y_cantidad(&coords, 2, path_clave);


	//agregar_bloque_disponible("/home/utnso/Escritorio/tall-grass/Files/bulbasaur");

	/*actualizar_bitmap(1);
	actualizar_bitmap(2);

	int disp = 0;

	disp = chequear_bloque_disponible("/home/utnso/Escritorio/tall-grass/Files/bulbasaur");

	log_debug(logger, "%d", disp);

	/*off_t block = 1;

	actualizar_bitmap(block);

	int bit = bitarray_test_bit(bitarray, 1);

	log_debug(logger, "%d", bit);*/

	//verificar_pokemon("/home/utnso/Escritorio/tall-grass/Files","bulbasaur");
	//archivo_en_uso("/home/utnso/Escritorio/tall-grass/Files/bulbasaur");

	/*t_coords coords;

	coords.posX = 2;
	coords.posY = 3;


	disminuir_cantidad(&coords, "/home/utnso/Escritorio/tall-grass/Blocks/1.bin");
*/

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

	log_debug(logger, "%s", buffer);

	array = bitarray_create_with_mode(buffer, bitmap_size, LSB_FIRST);

	return array;
}

