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


void enviar_mensaje(char* mensaje, int socket_cliente)
{

	//creacion del buffer

	int longitud = strlen(mensaje);

	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer->buffer_size = longitud + 1;

	void* stream = malloc(buffer->buffer_size);

	memcpy(stream, mensaje, longitud + 1);

	buffer->stream = stream;

	//creacion del paquete

	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->buffer = buffer;
	paquete->type = CONFIRMATION;

	int tamanio = 0;

	void* serializado = NULL;

	send(socket_cliente, serializado, tamanio, 0);

	free(serializado);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);



}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

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
	pthread_create(&thread, NULL, escucharAlBroker, &conexion);
	pthread_detach(thread);

	free(subscripcion);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);

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

void enviarGetPokemon(t_pokemon* pokemon) {
	char* ip = config_get_string_value(config,"IP_BROKER");
	char* puerto = config_get_string_value(config, "PUERTO_BROKER");
	// Abro conexion
	int conexion = crear_conexion(ip, puerto);

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
	printf("envio pokemon: %s\n", pokemon->name);

	send(conexion, paquete_serializado, paquete_size, 0); // TODO ver si tengo que esperar a que envie todo el mensaje para recien cerrar la conexion

	liberar_conexion(conexion);

	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
	return;
}


