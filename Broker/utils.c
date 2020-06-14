/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"
#include"var_globales.h"


//TODO: Implementación de threads
void iniciar_servidor(char* ip, char* puerto)
{
	int socket_servidor;

    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, puerto, &hints, &servinfo);

    for (p=servinfo; p != NULL; p = p->ai_next)
    {
        if ((socket_servidor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            continue;

        if (bind(socket_servidor, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_servidor);
            continue;
        }
        break;
    }

	listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);

    while(1)
    	esperar_cliente(socket_servidor);
}

void esperar_cliente(int socket_servidor)
{
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

	log_debug(logger, "Yo soy el servidor y tengo socket: %d", socket_servidor);
	log_debug(logger, "Se ha conectado un cliente al socket %d", *socket_cliente);

	pthread_create(&thread,NULL,(void*)serve_client, socket_cliente);
	pthread_detach(thread);

}

void serve_client(int* socket)
{
	//t_paquete* paquete = recibirPaquete(*socket);
	message_type type = recibirCodigoDeOperacion(*socket);
	if(type != NULL){
		log_debug(logger, "Procesando solicitud");
		process_request(type, *socket);
	}else {
		log_debug(logger, "No puedo procesar la solicitud");
	}
	//free(socket);
}

void process_request(message_type type, uint32_t socket_cliente){

	log_debug(logger, "Procesando código de operacion: %d", type);

	if(type == SUBSCRIBE){
		t_paquete* paquete = recibirPaqueteSi(socket_cliente, type);
		suscribirCliente(paquete -> buffer, socket_cliente);
		free(paquete -> buffer);
		return;
	}

	sem_wait(&(sem_sockets[type].c));
	pthread_mutex_lock(&(sem_sockets[type].mx));
	next_socket[type] = socket_cliente;
	pthread_mutex_unlock(&(sem_sockets[type].mx));
	sem_post(&(sem_sockets[type].q));


}




