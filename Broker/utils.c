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
		return;
	}

	log_debug(logger, "Yo soy el servidor y tengo socket: %d", socket_servidor);
	log_debug(logger, "Se ha conectado un cliente al socket %d", *socket_cliente);

	pthread_create(&thread,NULL,(void*)serve_client,socket_cliente);
	pthread_detach(thread);

}

void serve_client(int* socket)
{
	t_paquete* paquete = recibirPaquete(*socket);
	if(paquete != NULL){
		log_debug(logger, "Procesando solicitud");
		process_request(paquete, *socket);
	}else {
		log_debug(logger, "No puedo procesar la solicitud");
	}
	free(socket);
}

void process_request(t_paquete* paquete, uint32_t socket_cliente) {
	uint32_t size;
	t_buffer* buffer = paquete -> buffer;
	message_type cod_op = paquete -> type;
	log_debug(logger, "Código de operacion: %d", cod_op);
	switch (cod_op) {
		case SUBSCRIBE:
			suscribirCliente(buffer, socket_cliente);
			free(buffer);
			break;
		case NEW_POKEMON:
			break;
		case GET_POKEMON:
			break;

		case APPEARED_POKEMON:
			log_debug(logger, "Alguien ha enviado un APPEARED_POKEMON");
			//msg = recibir_mensaje(cliente_fd, &size);

			t_appeared_pokemon* appeared_pokemon_msg = deserializarAppearedPokemon(buffer);
			t_list* app_subscribers = subscribers -> appeared_pokemon;

			log_debug(logger, "Apareció un pokemon: %s", appeared_pokemon_msg -> pokemon -> name);

			for(int i = 0; i < list_size(app_subscribers); i++){
				void* list_element = list_get(app_subscribers, i);
				t_client* client = deserializarCliente(list_element);
				log_debug(logger, "Intentaré enviar APPEARED_POKEMON al cliente %d", *(client -> socket));
//				t_pokemon* pok = crearPokemon("PIKACHU");
//				t_appeared_pokemon* ap_pok = appeared_pokemon(pok, 10, 10);
				int bytes;
				void* ser = serializarAppearedPokemon(appeared_pokemon_msg, &bytes);
				int bytes_p;
				void* a_enviar = crear_paquete_con_id_correlativo(APPEARED_POKEMON, ser, bytes, paquete -> correlative_id, &bytes_p);

				int status = send(*(client -> socket), a_enviar, bytes_p, 0);
				log_debug(logger, "Envié APPEARED_POKEMON al suscriptor %d con status: %d", *(client -> socket) ,status);
			}

			break;

		case CATCH_POKEMON:
			break;

		case CAUGHT_POKEMON:
			break;

		case LOCALIZED_POKEMON:
			break;


		case 0:
			//printf("codigo 0\n");
			//close(cliente_fd); // Ante error cerrar el socket
			//pthread_exit(NULL);
			break;
		case -1:
			//printf("codigo -1\n");
			//close(cliente_fd); // Ante error cerrar el socket
			//pthread_exit(NULL);
			break;
	}
	// Cierro la conexion con ese cliente
	//close(cliente_fd);
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



