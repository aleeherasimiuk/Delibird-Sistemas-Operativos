#include "../Utils/conexiones.h"

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

int crear_conexion_con_config(t_config* config, char* campo_ip, char* campo_puerto) {
	char* ip = config_get_string_value(config,campo_ip);
	char* puerto = config_get_string_value(config, campo_puerto);
	// Abro conexion
	return crear_conexion(ip, puerto);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

