/*
 * conexiones.c
 *
 *  Created on: 3 mar. 2019
 *      Author: utnso
 */

#include"utils.h"


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
	struct sockaddr_in dir_cliente;

	socklen_t tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

	pthread_create(&thread,NULL,(void*)serve_client,&socket_cliente);
	pthread_detach(thread);

}

void serve_client(int* socket)
{
	message_type msg_type;
	if(recv(*socket, &msg_type, sizeof(message_type), MSG_WAITALL) == -1) // TODO ver porque recibe un -1 del team, excepto por el ultimo pokemon
		msg_type = -1;
	process_request(msg_type, *socket);
}

void process_request(int cod_op, int cliente_fd) {
	uint32_t size;
	t_buffer* msg;
		switch (cod_op) {
			case SUBSCRIBE:
				msg = recibir_mensaje(cliente_fd, &size);
				suscribirCliente(msg, cliente_fd);
				free(msg);
				break;
			case NEW_POKEMON:
				//msg = recibir_mensaje(cliente_fd, &size);
				//devolver_mensaje(msg, size, cliente_fd);
				//free(msg);
				break;
			case GET_POKEMON:
				msg = recibir_mensaje(cliente_fd, &size);
				t_pokemon* pokemon = deserializarPokemon(msg);
				printf("slap Like now %d \n", pokemon->name_size);
				break;
			case 0:
				printf("codigo -1\n");
				pthread_exit(NULL);
			case -1:
				printf("codigo -1\n");
				pthread_exit(NULL);
		}
}

//TODO: Controlar los recv
// Todos los mensajes vienen empaquetados en t_paquete
t_buffer* recibir_mensaje(int socket_cliente,uint32_t* size){
	uint32_t id;
	uint32_t correlative_id;
	t_buffer* buffer = malloc(sizeof(t_buffer));

	recv(socket_cliente, &id, sizeof(uint32_t), MSG_WAITALL);
	recv(socket_cliente, &correlative_id, sizeof(uint32_t), MSG_WAITALL);

	//buffer -> buffer_size = malloc(sizeof(uint32_t));
	recv(socket_cliente, &(buffer -> buffer_size), sizeof(uint32_t), MSG_WAITALL);
	buffer -> stream = malloc((buffer -> buffer_size));
	recv(socket_cliente, buffer -> stream, (buffer -> buffer_size), MSG_WAITALL);

	return buffer;
}


void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->type), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->buffer_size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->buffer_size);
	desplazamiento+= paquete->buffer->buffer_size;

	return magic;
}

void devolver_mensaje(void* payload, int size, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->type = NEW_POKEMON;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->buffer_size = size;
	paquete->buffer->stream = malloc(paquete->buffer->buffer_size);
	memcpy(paquete->buffer->stream, payload, paquete->buffer->buffer_size);

	int bytes = paquete->buffer->buffer_size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

