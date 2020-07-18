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

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1) {
		freeaddrinfo(server_info);
		return CANT_CONNECT;
	}

	freeaddrinfo(server_info);
	return socket_cliente;
}

void crear_servidor_cuando_se_pueda(char* ip, char* puerto, void* serve_client, t_log* logger){

	int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, puerto, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next) {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        int st = bind(socket_servidor, p->ai_addr, p->ai_addrlen);
        if (st == -1) {
            close(socket_servidor);
            log_error(logger, "No se ha podido realizar la conexión. Reintentando en 10 segundos");
            sleep(10);
            crear_servidor_cuando_se_pueda(ip, puerto, serve_client, logger);
            return;
        }
        break;
    }

    log_info(logger, "Servidor inicializado. Escuchando en: %s:%s", ip, puerto);

    //int t = 1;
    //setsockopt(*socket_servidor, SOL_SOCKET, SO_REUSEADDR, &t, sizeof(t));

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);


    while(1)
    	esperar_cliente(socket_servidor, serve_client);

    close(socket_servidor);
    exit(0);
}

void crear_servidor(char* ip, char* puerto, void* serve_client){

	int socket_servidor;


    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, puerto, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next) {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        int st = bind(socket_servidor, p->ai_addr, p->ai_addrlen);
        if (st == -1) {
        	perror("Error binding");
            close(socket_servidor);
            exit(0);
            //continue;
        }
        break;
    }

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);


    while(1)
    	esperar_cliente(socket_servidor, serve_client);

    close(socket_servidor);
    exit(0);
}

void esperar_cliente(int socket_servidor, void* serve_client){
	pthread_t thread;
	struct sockaddr_in dir_cliente;

	socklen_t tam_direccion = sizeof(struct sockaddr_in);
	int* socket_cliente = malloc(sizeof(int));  // Hicimos un malloc porque siempre le pasaba la misma direccion a los hilos
	*socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);
	if(*socket_cliente == -1) {
		close(*socket_cliente);
		free(socket_cliente);
		return;
	}

	pthread_create(&thread,NULL,(void*)serve_client, socket_cliente);
	pthread_detach(thread);

}

int crear_conexion_con_config(t_config* config, char* campo_ip, char* campo_puerto) {
	char* ip = config_get_string_value(config, campo_ip);
	char* puerto = config_get_string_value(config, campo_puerto);
	// Abro conexion
	return crear_conexion(ip, puerto);
}

void liberar_paquete(t_paquete* paquete){
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}


void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

int send_msg(int socket, void* stream, int stream_size){

	int streamed = 0;

	while(streamed < stream_size){
		int st = send(socket, stream, stream_size - streamed, MSG_NOSIGNAL);

		if(st != -1)
			streamed += st;
		else
			return -1;

	}

	return streamed;

}


