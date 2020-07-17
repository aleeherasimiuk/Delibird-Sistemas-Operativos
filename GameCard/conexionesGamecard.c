/*
 * gamecard.c
 *
 *  Created on: 17 jun. 2020
 *      Author: utnso
 */

#include "conexionesGamecard.h"

uint32_t process_id;

t_log* logger_extra = NULL;

void suscribirGameCardAlBroker(void){
		int conexiones[3];

		conexiones[0] = abrirUnaConexionGameCard();
		suscribirAUnaCola(conexiones[0], NEW_POKEMON, process_id);

		conexiones[1] = abrirUnaConexionGameCard();
		suscribirAUnaCola(conexiones[1], CATCH_POKEMON, process_id);

		conexiones[2] = abrirUnaConexionGameCard();
		suscribirAUnaCola(conexiones[2], GET_POKEMON, process_id);

		t_escucha_socket* s1, *s2, *s3;

		s1 = malloc(sizeof(t_escucha_socket));
		s2 = malloc(sizeof(t_escucha_socket));
		s3 = malloc(sizeof(t_escucha_socket));

		s1->socket = conexiones[0];
		s2->socket = conexiones[1];
		s3->socket = conexiones[2];

		s1->cola = NEW_POKEMON;
		s2->cola = CATCH_POKEMON;
		s3->cola = GET_POKEMON;

		pthread_t thread1, thread2, thread3;
		pthread_create(&thread1, NULL, escucharAlSocket, (void*)s1);
		pthread_create(&thread2, NULL, escucharAlSocket, (void*)s2);
		pthread_create(&thread3, NULL, escucharAlSocket, (void*)s3);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		pthread_join(thread3, NULL);


		return;
}

int abrirUnaConexionGameCard(void) {
	int conexion = crear_conexion_con_config(config, "IP_BROKER", "PUERTO_BROKER");
	if(conexion == CANT_CONNECT) {
		log_debug(logger, "No se puede conectar con el broker, intentando nueva conexión en %d segundos", tiempo_reconexion);
		sleep(tiempo_reconexion);
		return abrirUnaConexionGameCard();
	}
	return conexion;
}

void *escucharAlSocket(void* data) {
	int i = 1;
	t_escucha_socket* escucha_socket = (t_escucha_socket*) data;
	log_debug(logger, "Escuchando en el socket: %d", escucha_socket->socket);
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(escucha_socket->socket);

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
		}else {
			close(escucha_socket->socket);

			escucha_socket->socket = abrirUnaConexionGameCard();

			suscribirAUnaCola(escucha_socket->socket, escucha_socket->cola, process_id);
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
	//free(subscripcion);
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
	char* ruta_logger = config_get_string_value(config, "LOG_FILE_EXTRA");
	logger_extra = iniciar_logger(ruta_logger);

	log_debug(logger, "Estoy escuchando al gameboy en %s:%s", ip, puerto);
	crear_servidor_cuando_se_pueda(ip, puerto, serve_client, logger_extra);

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
}

void enviarACK(uint32_t id){

	int conexion = abrirUnaConexionGameCard();

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


