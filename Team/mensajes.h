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




typedef enum {
	NEW_POKEMON = 1,
	APPEARED_POKEMON,
	CATCH_POKEMON,
	CAUGHT_POKEMON,
	GET_POKEMON,
	LOCALIZED_POKEMON,
	CONFIRMATION		// Para avisar al broker que se recibió el mensaje (el broker actualiza el ACK)
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

// FIN STRUCTS MENSAJES

// PAQUETE DEL BROKER: Struct que reciben los procesos del broker (tienen las id)
/*
 * type (tipo de mensaje (ENUM)),
 * id: ID del mensaje, cuando se envía hacia el broker estaría vacío, pero cuando el broker te lo envía estaría con el identificador asignado
 * correlative_id : ID del mensaje al cual se está respondiendo.
 * data: un puntero al struct correspondiente del tipo del mensaje
 */
typedef struct {
	uint32_t buffer_size;
	void* stream;
}t_buffer;

typedef struct {
	message_type type;
	uint32_t id;
	uint32_t correlative_id;
	t_buffer* buffer;
} t_paquete;

//TODO: Ver si los typedef sin struct deben ser serializados

//Firmas de Serializacion
void* serializarPokemon(t_pokemon* pokemon, uint32_t* bytes);
void* serializarCoordenadas(t_coords* coordenadas, uint32_t* bytes);
void* serializarNewPokemon(t_new_pokemon* new_pokemon, uint32_t* bytes);
void* serializarAppearedPokemon(t_appeared_pokemon* appeared_pokemon, uint32_t * bytes);
void* serializarCatchPokemon(t_catch_pokemon* catch_pokemon, uint32_t * bytes);
void* serializarLocalizedPokemon(t_localized_pokemon* localized_pokemon, uint32_t * bytes);
void* serializarBuffer(t_buffer* buffer, uint32_t* bytes);
void* serializarPaquete(t_paquete* paquete, uint32_t* bytes);

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
t_pokemon* deserializarPokemon(t_buffer* buffer);
t_coords* deserializarCoordenadas(t_buffer* buffer);
t_new_pokemon* deserializarNewPokemon(t_buffer* buffer);
t_appeared_pokemon* deserializarAppearedPokemon(t_buffer* buffer);
t_catch_pokemon* deserializarCatchPokemon(t_buffer* buffer);
t_localized_pokemon* deserializarLocalizedPokemon(t_buffer* buffer);
t_buffer* deserializarBuffer(t_buffer* buffer);
t_paquete* recibirPaquete(int socket);


t_pokemon* crearPokemon(char*);





#endif /* MENSAJES_H_ */
