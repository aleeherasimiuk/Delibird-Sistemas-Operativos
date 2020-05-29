/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "conexiones.h"

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

int crear_conexion_con_config(void) {
	char* ip = config_get_string_value(config,"IP_BROKER");
	char* puerto = config_get_string_value(config, "PUERTO_BROKER");
	// Abro conexion
	return crear_conexion(ip, puerto);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

void liberar_paquete(t_paquete* paquete) {
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

//////////////////////////////////////////////
//				SUSCRIPCIONES				//
//////////////////////////////////////////////

void suscribirseAlBroker(void) {
	char* ip = config_get_string_value(config,"IP_BROKER");
	char* puerto = config_get_string_value(config, "PUERTO_BROKER");
	// Abro conexion
	int conexion = crear_conexion(ip, puerto);

	// Creo el mensaje de subscripcion
	t_subscribe* subscripcion = malloc(sizeof(t_subscribe));
	subscripcion->module = TEAM;

	uint32_t subscripcion_size;

	void* serialized_subscribe = serializarSubscribe(subscripcion, &subscripcion_size);

	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer->buffer_size = subscripcion_size;
	buffer->stream = serialized_subscribe;

	t_paquete* paquete = crearPaquete();	// ESTO HACE MALLOC
	paquete->type = SUBSCRIBE;
	paquete->buffer = buffer;

	uint32_t paquete_size;
	void* paquete_serializado = serializarPaquete(paquete, &paquete_size);

	send(conexion, paquete_serializado, paquete_size, 0);

	pthread_t thread;
	pthread_create(&thread, NULL, escucharAlBroker, &conexion); // Hilo para escuchar al broker
	pthread_detach(thread);

	free(subscripcion);
	liberar_paquete(paquete);

	return;
}

void *escucharAlBroker(void* socket) {
	int i = 1;
	while(i) {	// TODO: PONER QUE EL WHILE SEA MIENTRAS NO ESTA EN EXIT
		t_paquete* paquete = recibirPaquete(*((int*)socket));

		switch(paquete->type) {
			case APPEARED_POKEMON:
				// procesarAppeared(paquete); TODO
			case LOCALIZED_POKEMON:
				// procesarLocalized(paquete); TODO
			case CAUGHT_POKEMON:
				// procesarCaught(paquete); TODO
			default:
				printf("Codigo no valido: %d \n", paquete->type);
				i = 0;
		}
	}
	// TODO DESTRUIR EL HILO?
	return NULL;
}


//////////////////////////////////////////////
//					GET						//
//////////////////////////////////////////////

void enviarGetPokemon(t_pokemon* pokemon) {
	int conexion = crear_conexion_con_config();

	uint32_t get_pokemon_size;

	void* serialized_get_pokemon = serializarPokemon(pokemon, &get_pokemon_size);

	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer->buffer_size = get_pokemon_size;
	buffer->stream = serialized_get_pokemon;

	t_paquete* paquete = crearPaquete();	// ESTO HACE MALLOC
	paquete->type = GET_POKEMON;
	paquete->buffer = buffer;

	uint32_t paquete_size;
	void* paquete_serializado = serializarPaquete(paquete, &paquete_size);

	int status = send(conexion, paquete_serializado, paquete_size, 0); // TODO ver si tengo que esperar a que envie todo el mensaje para recien cerrar la conexion

	liberar_conexion(conexion);

	free(paquete_serializado);
	liberar_paquete(paquete);
	return;
}


