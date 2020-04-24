#include "mensajes.h"

//Firmas de Serializacion
void* serializarPokemon(t_pokemon* pokemon, uint32_t* bytes) {

	void* serialized_pokemon = serializarGenerico(bytes, 2, &(pokemon -> name_size), sizeof(uint32_t), pokemon -> name, pokemon -> name_size);

	return serialized_pokemon;
}

void* serializarCoordenadas(t_coords* coordenadas, uint32_t* bytes) {

	void* serialized_coords = serializarGenerico(bytes, 2, &(coordenadas -> posX), sizeof(uint32_t), &(coordenadas -> posY), sizeof(uint32_t));

	return serialized_coords;
}

void* serializarNewPokemon(t_new_pokemon* new_pokemon, uint32_t* bytes) {

		t_pokemon* pokemon = new_pokemon -> pokemon;
		t_coords* coordenadas = new_pokemon -> coords;

		uint32_t pokemon_size;
		void* serialized_pokemon = serializarPokemon(pokemon, &pokemon_size);

		uint32_t coords_size;
		void* serialized_coords = serializarCoordenadas(coordenadas, &coords_size);

		uint32_t pokemon_count = new_pokemon -> cantidad;

		void* serialized_new_pokemon = serializarGenerico(bytes, 3, serialized_pokemon, pokemon_size, serialized_coords, coords_size, &pokemon_count, sizeof(uint32_t));

		return serialized_new_pokemon;
}

void* serializarAppearedPokemon(t_appeared_pokemon* appeared_pokemon, uint32_t * bytes) {

		t_pokemon* pokemon = appeared_pokemon -> pokemon;
		t_coords* coordenadas = appeared_pokemon -> coords;

		uint32_t pokemon_size;
		void* serialized_pokemon = serializarPokemon(pokemon, &pokemon_size);

		uint32_t coords_size;
		void* serialized_coords = serializarCoordenadas(coordenadas, &coords_size);

		void* serialized_appeared_pokemon = serializarGenerico(bytes, 2, serialized_pokemon, pokemon_size, serialized_coords, coords_size);

		return serialized_appeared_pokemon;
}

void* serializarCatchPokemon(t_catch_pokemon* catch_pokemon, uint32_t * bytes) {
	t_pokemon* pokemon = catch_pokemon -> pokemon;
	t_coords* coordenadas = catch_pokemon -> coords;

	uint32_t pokemon_size;
	void* serialized_pokemon = serializarPokemon(pokemon, &pokemon_size);

	uint32_t coords_size;
	void* serialized_coords = serializarCoordenadas(coordenadas, &coords_size);


	void* serialized_catch_pokemon = serializarGenerico(bytes, 2, serialized_pokemon, pokemon_size, serialized_coords, coords_size);

	return serialized_catch_pokemon;
}

void* serializarLocalizedPokemon(t_localized_pokemon* localized_pokemon, uint32_t * bytes) {
	t_pokemon* pokemon = localized_pokemon -> pokemon;
	uint32_t cant_coordenadas = localized_pokemon -> cant_coords;
	t_coords* coords_array = localized_pokemon -> coords_array;

	uint32_t pokemon_size;
	void* serialized_pokemon = serializarPokemon(pokemon, &pokemon_size);

	*bytes = pokemon_size + sizeof(uint32_t) + cant_coordenadas * sizeof(t_coords);

	void* serialized_localized_pokemon;

	uint32_t offset = 0;
	memcpy(serialized_localized_pokemon + offset, pokemon, pokemon_size);
	offset += pokemon_size;

	memcpy(serialized_localized_pokemon + offset, &cant_coordenadas, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	for(int i = 0; i < cant_coordenadas; i++){

		uint32_t coords_size;
		void* coords_serialized = serializarCoordenadas(coords_array[i], &coords_size);

		memcpy(serialized_localized_pokemon + offset, coords_serialized, coords_size);
		offset += sizeof(t_coords);
	}

	return serialized_localized_pokemon;
}

void* serializarBuffer(t_buffer* buffer, uint32_t* bytes) {

	void* stream = buffer -> stream;
	uint32_t buffer_size = buffer -> buffer_size;

	void* serialized_buffer = serializarGenerico(bytes, 2, buffer_size, sizeof(uint32_t), stream, buffer-> buffer_size);

	return serialized_buffer;
}

void* serializarPaquete(t_paquete* paquete, uint32_t* bytes){

	message_type type = paquete -> type;
	uint32_t id = paquete -> id;
	uint32_t correlative_id = paquete -> correlative_id;
	t_buffer* buffer = paquete -> buffer;

	uint32_t buffer_size;
	void* serialized_buffer = serializarBuffer(buffer, &buffer_size);

	void* serialized_paquete = serializarGenerico(bytes, 4, &type, sizeof(message_type), &id, sizeof(uint32_t), &correlative_id, sizeof(uint32_t), serialized_buffer, buffer_size);

	return serialized_paquete;

}

void* serializarGenerico(uint32_t* bytes, uint32_t num_args, ...) {

	// va_list es la lista para guardar los argumentos variables
	va_list args;
	// cargo los argumentos en args
	va_start(args, num_args);

	// variables para el memcpy
	void* serialized; // falta el malloc
	void* sources[num_args];
	uint32_t sizes[num_args];
	uint32_t offset = 0;
	*bytes = 0;

	// primero tengo que conseguir el tamaño (bytes) para poder hacer el malloc del serialized
	for (int i = 0; i < num_args; i++) { // num_args = pares source,size
 		// consigo el valor del argumento
		sources[i] = va_arg(args, void*);
		sizes[i]   = va_arg(args, uint32_t);
		*bytes += sizes[i];
	}

	// malloc
	serialized = malloc(*bytes);

	// Hago todos los memcpy
	for (int i = 0; i < num_args; i++) {
		memcpy(serialized + offset, sources[i], sizes[i]);
		offset += sizes[i];
	}

	// libero la memoria del va_list
	va_end(args);

	return serialized;
}

//Firmas de Deserialización
/*t_pokemon* deserializarPokemon(void* buffer) {}
t_coords* deserializarCoordenadas(void* buffer);
t_new_pokemon* deserializarNewPokemon(void* buffer);
t_appeared_pokemon* deserializarAppearedPokemon(void* buffer);
t_catch_pokemon* deserializarCatchPokemon(void* buffer);
t_localized_pokemon* deserializarLocalizedPokemon(void* buffer);
t_paquete* deserializarPaquete(void* buffer);*/

t_pokemon* crearPokemon(char* name) {
	t_pokemon* pokemon = malloc(sizeof(t_pokemon));
	pokemon->name_size = strlen(name) + 1;
	pokemon->name = malloc(pokemon->name_size);
	memcpy(pokemon->name, name, pokemon->name_size);

	return pokemon;
}

/*
 	switch(type){

		case NEW_POKEMON:
			break;

		case APPEARED_POKEMON:
			break;

		case CATCH_POKEMON:
			break;

		case CAUGHT_POKEMON:
			break;

		case GET_POKEMON:
			break;

		case LOCALIZED_POKEMON:
			break;

		case CONFIRMATION:
			break;

	}
*/

