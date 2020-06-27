/*
 * gamecard.c
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#include "conexionesGamecard.h"

uint32_t process_id;

void suscribirGameCardAlBroker(void){
		int conexiones[3];

		conexiones[0] = abrirUnaConexionGameCard(config);
		suscribirAUnaCola(conexiones[0], NEW_POKEMON, process_id);

		conexiones[1] = abrirUnaConexionGameCard(config);
		suscribirAUnaCola(conexiones[1], CATCH_POKEMON, process_id);

		conexiones[2] = abrirUnaConexionGameCard(config);
		suscribirAUnaCola(conexiones[2], GET_POKEMON, process_id);


		pthread_t thread1, thread2, thread3;
		pthread_create(&thread1, NULL, escucharAlSocket, &conexiones[0]);
		pthread_create(&thread2, NULL, escucharAlSocket, &conexiones[1]);
		pthread_create(&thread3, NULL, escucharAlSocket, &conexiones[2]);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);

		return;
}

int abrirUnaConexionGameCard(t_config* config) {
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");
	return conexion;
}

void *escucharAlSocket(void* socket) {
	int i = 1;
	log_debug(logger, "Escuchando en el socket: %d", *((int*)socket));
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(*((int*)socket));
		void* ptr_a_stream = paquete -> buffer -> stream;

		if(paquete != NULL){ //TODO Revisar Memory Leak
			enviarACK(paquete -> id);
			pthread_t thread;

			switch(paquete->type) {
				case ID:
					pthread_create(&thread, NULL, procesarID, paquete);
					pthread_detach(&thread);
					break;
				case NEW_POKEMON:
					pthread_create(&thread, NULL, procesarNew, paquete);
					pthread_detach(thread);
					break;
				case CATCH_POKEMON:
					pthread_create(&thread, NULL, procesarCatch, paquete);
					pthread_detach(thread);
					break;
				case GET_POKEMON:
					pthread_create(&thread, NULL, procesarGet, paquete);
					pthread_detach(thread);
					break;
				default:
					log_debug(logger, "No entiendo el mensaje, debe ser NEW_POKEMON, CATCH_POKEMON o GET_POKEMON");
					break;
			}
			free(ptr_a_stream);
			free(paquete -> buffer);
			free(paquete);
		}else {
			// Políticas de reconexión
			close(*((int*)socket));
			i = 0;
		}
	}
	// TODO DESTRUIR EL HILO?
	return NULL;
}

void suscribirAUnaCola(int conexion, message_type cola, uint32_t process_id){

	// Creo el mensaje de subscripcion
	t_subscribe* subscripcion = subscribe(cola, process_id);

	uint32_t subscripcion_size;
	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);

	uint32_t paquete_size;
	void* paquete_serializado = crear_paquete(SUBSCRIBE, serialized_subscribe, subscripcion_size, &paquete_size);

	//TODO: Handlear error
	send(conexion, paquete_serializado, paquete_size, 0);
	free(subscripcion);
	free(serialized_subscribe);
	free(paquete_serializado);
	log_debug(logger, "Me suscribí a %d", cola);
}

void escucharAlGameboy(){

	pthread_t thread;
	pthread_create(&thread, NULL ,abrirSocketParaGameboy, NULL);
	pthread_detach(thread);
}

void* abrirSocketParaGameboy(){

	char* ip = config_get_string_value(config, "IP");
	char* puerto = config_get_string_value(config, "PUERTO");
	log_debug(logger, "Estoy escuchando al gameboy en %s:%s", ip, puerto);
	crear_servidor(ip, puerto, serve_client);

}

void serve_client(int* socket){
	message_type type = recibirCodigoDeOperacion(*socket);
	if(type != NULL){
		log_debug(logger, "Procesando solicitud");
		process_request(type, *socket);
	}else {
		log_debug(logger, "No puedo procesar la solicitud");
	}
}

void process_request(message_type type, int socket){

	t_paquete* paquete = recibirPaqueteSi(socket, type);
	void* ptr_a_stream = paquete -> buffer -> stream;

	switch(type){

		case NEW_POKEMON:
			procesarNew(paquete);
			break;

		case CATCH_POKEMON:
			procesarCatch(paquete);
			break;

		case GET_POKEMON:
			procesarGet(paquete);
			break;

		default:
			log_error(logger, "Código de operación inválido");

	}
	free(ptr_a_stream);
	free(paquete -> buffer);
	free(paquete);
}

void enviarACK(uint32_t id){

	int conexion = abrirUnaConexionGameCard(config);

	log_debug(logger,"Enviaré un ACK por el id: %d",id);
	t_ack* _ack = ack(process_id, id);

	uint32_t bytes_ack;
	void* serialized_ack = serializarACK(_ack, &bytes_ack);

	uint32_t bytes;
	void* a_enviar = crear_paquete(ACK, serialized_ack, bytes_ack, &bytes);

	int status = send(conexion, a_enviar, bytes, 0);
	log_debug(logger, "Envié un ACK al ID: %d, con status: %d", id, status);
	free(_ack);
	free(serialized_ack);
	free(a_enviar);
	close(conexion);


}


