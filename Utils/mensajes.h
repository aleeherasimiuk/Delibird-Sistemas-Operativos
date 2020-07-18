/*
 * mensajes.h
 *
 *  Created on: 19 abr. 2020
 *      Author: Nico Rickert
 */

#ifndef MENSAJES_H_
#define MENSAJES_H_

#include<stdlib.h>
#include<stdint.h>
#include<stdarg.h> // Para argumentos variables en funciones
#include<string.h>
#include<sys/socket.h>


typedef enum {
	NEW_POKEMON = 1,
	APPEARED_POKEMON,
	CATCH_POKEMON,
	CAUGHT_POKEMON,
	GET_POKEMON,
	LOCALIZED_POKEMON,
	SUBSCRIBE,
	GAMEBOY_SUBSCRIBE, // Borrar
	ID,
	ACK
} message_type;

typedef struct {
	uint32_t name_size;
	char* name;
} t_pokemon;

typedef struct {
	uint32_t posX;
	uint32_t posY;
} t_coords;

// STRUCTS DE MENSAJES


/* Este mensaje tendrá el nombre del Pokemon a enviar, las coordenadas de la posición donde se encuentra y
 * la cantidad de pokémon de esta especie que habra en dicha posicion.
 */

typedef struct {
	t_pokemon* pokemon;
	t_coords* coords;
	uint32_t cantidad; // TODO: ¿Pueden haber más de un pokemon por celda?
} t_new_pokemon;

// Este mensaje tendrá el nombre del pokemon y para indicar la posición en X y en Y.

typedef struct {
	t_pokemon* pokemon;
	t_coords* coords;
} t_appeared_pokemon;

// Este mensaje tendrá el nombre del pokemon y la posición en X y en Y.

typedef struct {
	t_pokemon* pokemon;
	t_coords* coords;
} t_catch_pokemon;

// Este mensaje tendrá un valor para indicar si se pudo o no atrapar al pokemon (0 o 1)

//Acá sacamos las struct ya que de momento los mensajes llevan un solo campo.

typedef uint32_t t_caught_pokemon;
typedef enum {NO, YES} caught_msg;

// Este mensaje tendrá el nombre del pokemon.

typedef t_pokemon t_get_pokemon;

/* Este mensaje tendrá el nombre del pokémon, un entero para la cantidad de pares de coordenadas
 * y los pares de coordenadas donde se encuentra el mismo.
 */

typedef struct {
	t_pokemon* pokemon;
	uint32_t cant_coords;
	t_coords** coords_array;
} t_localized_pokemon;


typedef struct {
	uint32_t process_id; // Se asigna, por ahora en el archivo de configuración
	message_type queue_to_subscribe;
} t_subscribe;

// Gameboy Modo Suscriptor: https://bit.ly/3c1R6Md
typedef struct {
	message_type queue_to_subscribe; // Cola a la que se suscribe el gameboy
	uint32_t seconds; // Tiempo en segundos
} t_gameboy_queue_to_subscribe;



typedef uint32_t t_id;
typedef uint32_t t_process_id;

typedef struct{

	t_id id;
	t_process_id process_id;

} t_ack;


// FIN STRUCTS MENSAJES

// PAQUETE DEL BROKER: Struct que reciben los procesos del broker (tienen las id)
/*
 * type (tipo de mensaje (ENUM)),
 * id: ID del mensaje, cuando se envía hacia el broker estaría vacío, pero cuando el broker te lo envía estaría con el identificador asignado
 * correlative_id : ID del mensaje al cual se está respondiendo.
 * data: un puntero al struct correspondiente del tipo del mensaje
 */
typedef struct {
	uint32_t stream_size;
	void* stream;
}t_buffer;

typedef struct {
	message_type type;
	uint32_t id;
	uint32_t correlative_id;
	t_buffer* buffer;
} t_paquete;

//TODO: Ver si los typedef sin struct deben ser serializados


// Es probable que haya que poder identificar de otra manera a los clientes
typedef struct{
	uint32_t process_id;
	uint32_t socket;
} t_client;

//TODO: Borrar
typedef struct{
	uint32_t client;
	uint32_t id;
	uint32_t received;
}t_message_by_client;

t_buffer* crearBuffer(void* stream, uint32_t bytes);

//Firmas de Serializacion
void* serializarPokemon(t_pokemon* pokemon, uint32_t* bytes);
void* serializarCoordenadas(t_coords* coordenadas, uint32_t* bytes);
void* serializarNewPokemon(t_new_pokemon* new_pokemon, uint32_t* bytes);
void* serializarAppearedPokemon(t_appeared_pokemon* appeared_pokemon, uint32_t * bytes);
void* serializarCatchPokemon(t_catch_pokemon* catch_pokemon, uint32_t * bytes);
void* serializarCaughtPokemon(t_caught_pokemon* caught_pokemon, uint32_t* bytes);
void* serializarLocalizedPokemon(t_localized_pokemon* localized_pokemon, uint32_t * bytes);
void* serializarSubscribe(t_subscribe* subscribe, uint32_t* bytes);
void* serializarSubscribeGameboy(t_gameboy_queue_to_subscribe* subscribe, uint32_t* bytes);
void* serializarBuffer(t_buffer* buffer, uint32_t* bytes);
void* serializarPaquete(t_paquete* paquete, uint32_t* bytes);
void* serializarACK(t_ack*, uint32_t* bytes);

//Test
void* serializarCliente(t_client* cliente);

/*
 * serializarGenerico:
 * bytes: el largo de la cadena serializada
 * se le pasa la cantidad de pares (source,size) a enviar,
 * un argumento siempre tiene que ser de a pares, el primero es un void* (source) y el segundo es un uint32_t (size)
 * para los distintos memcpy, y me devuelve el puntero a la serializacion de todos los elementos
 * EJ: serializarGenerico(serialized_size, 2, &name_size, sizeof(uint32_t), name, name_size);
 */
void* serializarGenerico(uint32_t* bytes, uint32_t num_args, ...);

//Firmas de Deserialización
t_pokemon* deserializarPokemon(t_buffer** buffer);
t_coords* deserializarCoordenadas(t_buffer** buffer);
t_new_pokemon* deserializarNewPokemon(t_buffer* buffer);
t_appeared_pokemon* deserializarAppearedPokemon(t_buffer* buffer);
t_catch_pokemon* deserializarCatchPokemon(t_buffer* buffer);
t_caught_pokemon* deserializarCaughtPokemon(t_buffer* buffer);
t_localized_pokemon* deserializarLocalizedPokemon(t_buffer* buffer);
t_subscribe* deserializarSubscribe(t_buffer* buffer);
t_gameboy_queue_to_subscribe* deserializarSubscribeGameboy(t_buffer* buffer);
t_client* deserializarCliente(void*);
t_ack* deserializarACK(t_buffer*);

message_type recibirCodigoDeOperacion(int socket);
t_paquete* recibirPaquete(int socket);
t_paquete* recibirPaqueteSi(int socket, message_type cod_op);


t_pokemon* crearPokemon(char*);
t_paquete* crearPaquete(void);	// Me crea un paquete con los id = 0 por defecto

// Crear Mensajes
void* crear_paquete(message_type, void*, uint32_t, uint32_t*);
void* crear_paquete_con_id(message_type , void*, uint32_t, uint32_t, uint32_t*);
void* crear_paquete_con_id_correlativo(message_type, void*, uint32_t, uint32_t, uint32_t*); //No se como sobrecargar funciones
void* crear_paquete_con_ids(message_type cod_op, void* serialized_message, uint32_t message_bytes, uint32_t id, uint32_t id_correlativo, uint32_t* paquete_size);
t_coords* crear_coordenadas_from_int(uint32_t, uint32_t);
t_new_pokemon* new_pokemon(t_pokemon*, uint32_t, uint32_t, uint32_t);
t_appeared_pokemon* appeared_pokemon(t_pokemon*, uint32_t, uint32_t);
t_catch_pokemon* catch_pokemon(t_pokemon*, uint32_t, uint32_t);
t_caught_pokemon* caught_pokemon(uint32_t*);
t_get_pokemon* get_pokemon(t_pokemon*);
t_subscribe* subscribe(message_type, uint32_t);
t_gameboy_queue_to_subscribe* gameboy_queue_subscribe(message_type, uint32_t);
t_localized_pokemon* localized_pokemon(t_pokemon*, uint32_t, t_coords**);
t_coords** coords_array(uint32_t, ...);
t_client* cliente(uint32_t, uint32_t);
t_ack* ack(t_process_id, t_id);

char* queue_name(message_type);
void free_coords_array(t_coords** coords, int cantidad_coordenadas);

#endif /* MENSAJES_H_ */
