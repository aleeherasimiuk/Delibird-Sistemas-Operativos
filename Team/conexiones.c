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

void* recibir_mensaje(int socket_cliente)
{

	message_type tipo_mensaje;
	int buffer_size;
	recv(socket_cliente, &tipo_mensaje, sizeof(tipo_mensaje), 0);
	recv(socket_cliente, &buffer_size, sizeof(buffer_size), 0);

	char* buffer = malloc(buffer_size);

	recv(socket_cliente, buffer, buffer_size, 0);

	if(tipo_mensaje == LOCALIZED_POKEMON) {

		t_localized_pokemon* pokemonesLocalizados;

		pokemonesLocalizados = deserializarLocalizedPokemon(buffer);

		free(buffer);

		return pokemonesLocalizados;
	}

	return NULL;
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}
