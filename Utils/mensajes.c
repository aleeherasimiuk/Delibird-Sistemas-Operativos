#include "conexiones.h"

t_buffer* crearBuffer(void* algoSerializado, uint32_t bytes){
	t_buffer* buffer = malloc(sizeof(uint32_t) + bytes);
	buffer -> stream_size = bytes;
	buffer -> stream = algoSerializado;
	return buffer;
}

//Firmas de Serializacion
void* serializarPokemon(t_pokemon* pokemon, uint32_t* bytes) {

	/*Se elimina el \0*/
	void* serialized_pokemon = serializarGenerico(bytes, 2, &(pokemon -> name_size), sizeof(uint32_t), pokemon -> name, pokemon -> name_size - 1);

	return serialized_pokemon;
}

void* serializarCoordenadas(t_coords* coordenadas, uint32_t* bytes) {
	void* serialized_coords = serializarGenerico(bytes, 2, &(coordenadas -> posX), sizeof(uint32_t), &(coordenadas -> posY), sizeof(uint32_t));

	return serialized_coords;
}

//TODO: deserializarGenérico

void* serializarNewPokemon(t_new_pokemon* new_pokemon, uint32_t* bytes) {

		t_pokemon* pokemon = new_pokemon -> pokemon;
		t_coords* coordenadas = new_pokemon -> coords;

		uint32_t pokemon_size;
		void* serialized_pokemon = serializarPokemon(pokemon, &pokemon_size);

		uint32_t coords_size;
		void* serialized_coords = serializarCoordenadas(coordenadas, &coords_size);

		uint32_t pokemon_count = new_pokemon -> cantidad;

		void* serialized_new_pokemon = serializarGenerico(bytes, 3, serialized_pokemon, pokemon_size, serialized_coords, coords_size, &pokemon_count, sizeof(uint32_t));

		//free(pokemon -> name);
		free(serialized_pokemon);
		free(serialized_coords);
		free(coordenadas);

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

		free(serialized_pokemon);
		free(serialized_coords);

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

	free(serialized_pokemon);
	free(serialized_coords);

	return serialized_catch_pokemon;
}

void* serializarCaughtPokemon(t_caught_pokemon* caught_pokemon, uint32_t* bytes){

	*bytes = sizeof(uint32_t);
	return (void*) caught_pokemon;
}

void* serializarLocalizedPokemon(t_localized_pokemon* localized_pokemon, uint32_t * bytes) {
	t_pokemon* pokemon = localized_pokemon -> pokemon;
	uint32_t cant_coordenadas = localized_pokemon -> cant_coords;
	t_coords** coords_array = localized_pokemon -> coords_array;

	uint32_t pokemon_size;
	void* serialized_pokemon = serializarPokemon(pokemon, &pokemon_size);

	*bytes = pokemon_size + sizeof(uint32_t) + cant_coordenadas * sizeof(t_coords);

	void* serialized_localized_pokemon = malloc(*bytes);

	uint32_t offset = 0;
	memcpy(serialized_localized_pokemon + offset, serialized_pokemon, pokemon_size);
	offset += pokemon_size;

	memcpy(serialized_localized_pokemon + offset, &cant_coordenadas, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	for(int i = 0; i < cant_coordenadas; i++){

		uint32_t coords_size;
		void* coords_serialized = serializarCoordenadas(coords_array[i], &coords_size);

		memcpy(serialized_localized_pokemon + offset, coords_serialized, coords_size);
		offset += sizeof(t_coords);

		free(coords_serialized);
	}

	free(serialized_pokemon);
	liberar_lista_punteros_coordenadas(coords_array);

	return serialized_localized_pokemon;
}

void* serializarSubscribe(t_subscribe* subscribe, uint32_t* bytes) {

	uint32_t process_id = subscribe -> process_id;
	message_type message = subscribe -> queue_to_subscribe;
	void* serializedSubscribe = serializarGenerico(bytes, 2, &process_id, sizeof(uint32_t), &message, sizeof(message_type));
	return serializedSubscribe;

}

void* serializarSubscribeGameboy(t_gameboy_queue_to_subscribe* subscribe, uint32_t* bytes) {

	message_type queue_to_subscribe = subscribe -> queue_to_subscribe;
	uint32_t seconds = subscribe -> seconds;
	void* serializedSubscribe = serializarGenerico(bytes, 2, &queue_to_subscribe, sizeof(message_type), &seconds, sizeof(uint32_t));
	return serializedSubscribe;
}

void* serializarACK(t_ack* ack, uint32_t* bytes){

	uint32_t pid = ack -> process_id;
	uint32_t mid = ack -> id;

	void* serializedACK = serializarGenerico(bytes, 2, &pid, sizeof(uint32_t), &mid, sizeof(uint32_t));
	return serializedACK;

}



void* serializarBuffer(t_buffer* buffer, uint32_t* bytes) {

	void* stream = buffer -> stream;
	uint32_t buffer_size = buffer -> stream_size;

	void* serialized_buffer = serializarGenerico(bytes, 2, &buffer_size, sizeof(uint32_t), stream, buffer-> stream_size);

	*bytes = buffer -> stream_size + sizeof(uint32_t);

	return serialized_buffer;
}

void* serializarPaquete(t_paquete* paquete, uint32_t* bytes){

	message_type type = paquete -> type;
	uint32_t id = paquete -> id;
	uint32_t correlative_id = paquete -> correlative_id;
	t_buffer* buffer = paquete -> buffer;

	uint32_t buffer_size;
	void* serialized_buffer = serializarBuffer(buffer, &buffer_size);

	free(buffer -> stream);
	free(buffer);

	void* serialized_paquete = serializarGenerico(bytes, 4, &type, sizeof(message_type), &id, sizeof(uint32_t), &correlative_id, sizeof(uint32_t), serialized_buffer, buffer_size);
	free(serialized_buffer);
	return serialized_paquete;

}

void* serializarCliente(t_client* cliente){

	uint32_t bytes;
	void* serialized_client = serializarGenerico(&bytes, 2, &(cliente -> process_id), sizeof(uint32_t), &(cliente -> socket), sizeof(uint32_t));

	return serialized_client;
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

t_ack* deserializarACK(t_buffer* buffer){

	t_ack* ack = malloc(sizeof(t_ack));
	void* stream = buffer -> stream;

	memcpy(&(ack -> process_id), stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	memcpy(&(ack -> id), stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);

	free(buffer -> stream);
	free(buffer);
	return ack;

}

//Firmas de Deserialización

/// ESTO MUEVE EL PUNTERO DEL STREAM
t_pokemon* deserializarPokemon(t_buffer** buffer) {

	t_pokemon* pokemon = malloc(sizeof(t_pokemon));

	memcpy(&(pokemon -> name_size), (*buffer) -> stream, sizeof(uint32_t));
	(*buffer) -> stream += sizeof(uint32_t);

	pokemon -> name = malloc(pokemon -> name_size);
	memcpy(pokemon -> name, (*buffer) -> stream, pokemon -> name_size);
	(*buffer) -> stream += (pokemon -> name_size - 1) * sizeof(char);

	char* name = pokemon -> name;
	name[pokemon -> name_size - 1] = '\0';

	return pokemon;
}

/// ESTO MUEVE EL PUNTERO DEL STREAM
t_coords* deserializarCoordenadas(t_buffer** buffer) {

	t_coords* coords = malloc(sizeof(t_coords));

	memcpy(&(coords -> posX), (*buffer) -> stream, sizeof(uint32_t));
	(*buffer) -> stream += sizeof(uint32_t);

	memcpy(&(coords -> posY), (*buffer) -> stream, sizeof(uint32_t));
	(*buffer) -> stream += sizeof(uint32_t);

	return coords;
}


t_new_pokemon* deserializarNewPokemon(t_buffer* buffer) {


	t_new_pokemon* new_pokemon = malloc(sizeof(t_new_pokemon));

	t_pokemon* deserialized_pokemon = deserializarPokemon(&buffer);


	t_coords* coords = deserializarCoordenadas(&buffer);


	uint32_t count;
	memcpy(&count, buffer -> stream, sizeof(uint32_t));

	new_pokemon -> pokemon = deserialized_pokemon;
	new_pokemon -> coords = coords;
	new_pokemon -> cantidad = count;

	return new_pokemon;

}

t_appeared_pokemon* deserializarAppearedPokemon(t_buffer* buffer) {

	t_appeared_pokemon* appeared_pokemon = malloc(sizeof(t_appeared_pokemon));

	t_pokemon* pokemon = deserializarPokemon(&buffer);

	t_coords* coords = deserializarCoordenadas(&buffer);

	appeared_pokemon -> pokemon = pokemon;
	appeared_pokemon -> coords = coords;

	return appeared_pokemon;

}


t_catch_pokemon* deserializarCatchPokemon(t_buffer* buffer) {

	t_catch_pokemon* catch_pokemon = malloc(sizeof(t_catch_pokemon));

	t_pokemon* deserialized_pokemon = deserializarPokemon(&buffer);

	t_coords* deserialized_coords = deserializarCoordenadas(&buffer);

	//uint32_t count;
	//memcpy(&count, buffer -> stream, sizeof(uint32_t));

	catch_pokemon -> pokemon = deserialized_pokemon;
	catch_pokemon -> coords = deserialized_coords;

	return catch_pokemon;
}

t_caught_pokemon* deserializarCaughtPokemon(t_buffer* buffer){

	t_caught_pokemon* caught_pok = (uint32_t*) buffer -> stream;

	return caught_pok;

}


t_localized_pokemon* deserializarLocalizedPokemon(t_buffer* buffer) {

	t_localized_pokemon* localized_pokemon = malloc(sizeof(t_localized_pokemon));

	t_pokemon* pokemon = deserializarPokemon(&buffer);

	uint32_t count = 0;
	memcpy(&count, buffer -> stream, sizeof(uint32_t));
	buffer -> stream += sizeof(uint32_t);


	localized_pokemon -> pokemon = pokemon;
	localized_pokemon -> cant_coords = count;

	t_coords** coordenadas = malloc(count * sizeof(t_coords));

	for(int i = 0; i < count; i++){
		coordenadas[i] = deserializarCoordenadas(&buffer);
	}

	localized_pokemon -> coords_array = coordenadas;


	return localized_pokemon;
}

t_subscribe* deserializarSubscribe(t_buffer* buffer) {
	t_subscribe* subscribe = malloc(sizeof(t_subscribe));
	void* stream = buffer -> stream;

	uint32_t process_id;
	message_type message;
	uint32_t offset = 0;

	memcpy(&process_id, stream + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(&message, stream + offset, sizeof(message_type));
	offset += sizeof(message_type);

	subscribe -> queue_to_subscribe = message;
	subscribe -> process_id = process_id;

	//free(stream);
	//free(buffer);

	return subscribe;
}

t_gameboy_queue_to_subscribe* deserializarSubscribeGameboy(t_buffer* buffer) {
	t_gameboy_queue_to_subscribe* subscribe = malloc(sizeof(t_gameboy_queue_to_subscribe));
	void* stream = buffer -> stream;

	message_type type;
	uint32_t seconds;

	uint32_t offset = 0;
	memcpy(&type, stream + offset, sizeof(message_type));
	offset += sizeof(message_type);

	memcpy(&seconds, stream + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	subscribe -> queue_to_subscribe = type;
	subscribe -> seconds = seconds;

	free(stream);
	free(buffer);

	return subscribe;
}

t_client* deserializarCliente(void* stream){

	uint32_t pid;
	uint32_t sock;

	uint32_t offset = 0;

	memcpy(&pid, stream + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	memcpy(&sock, stream + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);

	t_client* cli = cliente(pid, sock);

	//NOTA: No liberar el stream, se necesita para poder enviar cada vez que se necesite
	//free(stream);

	return cli;

}

t_paquete* recibirPaquete(int socket) {
	t_paquete* paquete = malloc(sizeof(t_paquete));

	// Recibo tipo de mensaje
	int status = recv(socket, &(paquete -> type), sizeof(paquete -> type), MSG_WAITALL);
	//printf("Status: %d\n", status);
	if(status > 0){
		// Recibo IDs
		recv(socket, &(paquete -> id), sizeof(paquete->id), MSG_WAITALL);
		recv(socket, &(paquete -> correlative_id), sizeof(paquete -> correlative_id), MSG_WAITALL);

		paquete->buffer = malloc(sizeof(t_buffer));
		recv(socket, &(paquete -> buffer -> stream_size), sizeof(paquete -> buffer -> stream_size), MSG_WAITALL);

		paquete -> buffer-> stream = malloc(paquete -> buffer -> stream_size);
		recv(socket, paquete -> buffer -> stream, paquete -> buffer -> stream_size, MSG_WAITALL);
		return paquete;
	} else {
		free(paquete);
		return NULL;
	}

}

message_type recibirCodigoDeOperacion(int socket){
	message_type type;
	// Recibo tipo de mensaje
	int status = recv(socket, &(type), sizeof(message_type), MSG_WAITALL);
	if(status > 0){
		return type;
	} else {
		return -1;
	}
}


t_paquete* recibirPaqueteSi(int socket, message_type type) {

	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete -> type = type;

	// Recibo IDs
	recv(socket, &(paquete -> id), sizeof(paquete->id), MSG_WAITALL);
	recv(socket, &(paquete -> correlative_id), sizeof(paquete -> correlative_id), MSG_WAITALL);

	paquete->buffer = malloc(sizeof(t_buffer));
	recv(socket, &(paquete -> buffer -> stream_size), sizeof(paquete -> buffer -> stream_size), MSG_WAITALL);

	paquete -> buffer-> stream = malloc(paquete -> buffer -> stream_size);
	recv(socket, paquete -> buffer -> stream, paquete -> buffer -> stream_size, MSG_WAITALL);
	return paquete;


}

t_pokemon* crearPokemon(char* name) {
	t_pokemon* pokemon = malloc(sizeof(t_pokemon));
	pokemon->name_size = strlen(name) + 1;
	//strcpy(pokemon->name, name);
	pokemon->name = malloc(pokemon->name_size);
	memcpy(pokemon->name, name, pokemon->name_size);

	return pokemon;
}

t_paquete* crearPaquete(void) { //TODO: Pasar a notación con _
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->id = 0;
	paquete->correlative_id = 0;
	return paquete;
}

void* crear_paquete_con_id(message_type cod_op, void* serialized_message, uint32_t message_bytes, uint32_t id, uint32_t* paquete_size){

	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer -> stream_size = message_bytes;
	buffer -> stream = malloc(message_bytes);
	memcpy(buffer -> stream, serialized_message, message_bytes);

	t_paquete* paquete = crearPaquete();
	paquete -> type = cod_op;
	paquete -> id = id;
	paquete -> buffer = buffer;

	void* serialized_paquete = serializarPaquete(paquete, paquete_size);
	//free(paquete -> buffer -> stream);
	//free(paquete -> buffer);
	free(paquete);
	return serialized_paquete;
}

void* crear_paquete_con_ids(message_type cod_op, void* serialized_message, uint32_t message_bytes, uint32_t id, uint32_t id_correlativo, uint32_t* paquete_size){
	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer -> stream_size = message_bytes;
	buffer -> stream = malloc(message_bytes);
	memcpy(buffer -> stream, serialized_message, message_bytes);

	t_paquete* paquete = crearPaquete();
	paquete -> type = cod_op;
	paquete -> id = id;
	paquete -> correlative_id = id_correlativo;
	paquete -> buffer = buffer;

	void* serialized_paquete = serializarPaquete(paquete, paquete_size);

	//free(buffer);
	free(paquete);

	return serialized_paquete;
}

void* crear_paquete(message_type cod_op, void* serialized_message, uint32_t message_bytes, uint32_t* paquete_size){

	return crear_paquete_con_id_correlativo(cod_op, serialized_message, message_bytes, 0, paquete_size);
}

void* crear_paquete_con_id_correlativo(message_type cod_op, void* serialized_message, uint32_t message_bytes, uint32_t id_correlativo, uint32_t* paquete_size) {
	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer -> stream_size = message_bytes;
	buffer -> stream = malloc(message_bytes);
	memcpy(buffer -> stream, serialized_message, message_bytes);

	t_paquete* paquete = crearPaquete();
	paquete -> type = cod_op;
	paquete -> correlative_id = id_correlativo;
	paquete -> buffer = buffer;

	void* serialized_paquete = serializarPaquete(paquete, paquete_size);

	//free(buffer);
	free(paquete);

	return serialized_paquete;
	//TODO: liberar_paquete(paquete);
}

t_coords* crear_coordenadas_from_int(uint32_t posX, uint32_t posY){
	t_coords* coords = malloc(sizeof(t_coords));
	coords -> posX = posX;
	coords -> posY = posY;


	return coords;
}

t_new_pokemon* new_pokemon(t_pokemon* pokemon, uint32_t posX, uint32_t posY, uint32_t cantidad){

	t_new_pokemon* new_pokemon = malloc(sizeof(t_new_pokemon));
	t_coords* coords = crear_coordenadas_from_int(posX, posY);

	new_pokemon -> pokemon = pokemon;
	new_pokemon -> coords = coords;
	new_pokemon -> cantidad = cantidad;

	return new_pokemon;
}

t_appeared_pokemon* appeared_pokemon(t_pokemon* pokemon, uint32_t posX, uint32_t posY){

	t_appeared_pokemon* appeared_pokemon = malloc(sizeof(t_appeared_pokemon));
	t_coords* coords = crear_coordenadas_from_int(posX, posY);

	appeared_pokemon -> pokemon = pokemon;
	appeared_pokemon -> coords = coords;


	return appeared_pokemon;
}

t_catch_pokemon* catch_pokemon(t_pokemon* pokemon, uint32_t posX, uint32_t posY){

	t_catch_pokemon* catch_pokemon = malloc(sizeof(t_catch_pokemon));
	t_coords* coords = crear_coordenadas_from_int(posX, posY);

	catch_pokemon -> pokemon = pokemon;
	catch_pokemon -> coords = coords;

	return catch_pokemon;

}

t_caught_pokemon* caught_pokemon(uint32_t* caught) {
	return caught; // Solo por mantener coherencia
}

t_get_pokemon* get_pokemon(t_pokemon* pokemon) {
	return pokemon; // Solo por mantener coherencia
}

t_subscribe* subscribe(message_type queue, uint32_t process_id) {

	t_subscribe* suscripcion = malloc(sizeof(t_subscribe));
	suscripcion -> queue_to_subscribe = queue;
	suscripcion -> process_id = process_id;
	return suscripcion;

}

t_localized_pokemon* localized_pokemon(t_pokemon* pokemon, uint32_t cant_coords, t_coords** coords_array) {

	t_localized_pokemon* loc_pok = malloc(sizeof(t_localized_pokemon));

	loc_pok -> pokemon = pokemon;
	loc_pok -> cant_coords = cant_coords;
	loc_pok -> coords_array = coords_array;

	return loc_pok;
}

t_coords** coords_array(uint32_t cant_coords, ...){
	// va_list es la lista para guardar los argumentos variables
	va_list args;

	// cargo los argumentos en args
	va_start(args, cant_coords);

	t_coords** array = malloc(cant_coords * sizeof(t_coords*));

	for(int i = 0; i < cant_coords; i++){
		array[i] = va_arg(args, t_coords*);
	}

	va_end(args);

	return array;

}

t_client* cliente(uint32_t process_id, uint32_t socket){

	t_client* client = malloc(sizeof(t_client));

	client -> process_id = process_id;
	client -> socket = socket;

	return client;
}

t_ack* ack(t_process_id pid, t_id mid){

	t_ack* ack = malloc(sizeof(t_ack));

	ack -> process_id = pid;
	ack -> id = mid;

	return ack;
}



// TODO: Localized pokemon, el gameboy no lo usa.

t_gameboy_queue_to_subscribe* gameboy_queue_subscribe(message_type queue, uint32_t seconds) {

	t_gameboy_queue_to_subscribe* gameboy_queue_subscribe = malloc(sizeof(t_gameboy_queue_to_subscribe));
	gameboy_queue_subscribe -> queue_to_subscribe = queue;
	gameboy_queue_subscribe -> seconds = seconds;

	return gameboy_queue_subscribe;

}

char* queue_name(message_type queue){

	switch(queue){

	case NEW_POKEMON:
		return "NEW POKEMON";

	case APPEARED_POKEMON:
		return "APPEARED POKEMON";

	case CATCH_POKEMON:
		return "CATCH POKEMON";

	case CAUGHT_POKEMON:
		return "CAUGHT POKEMON";

	case LOCALIZED_POKEMON:
		return "LOCALIZED POKEMON";

	case GET_POKEMON:
		return "GET POKEMON";

	default:
		return "INVALID QUEUE";

	}

}

void liberar_lista_punteros_coordenadas(t_coords** list){
	int i = 0;
	while(list[i] != NULL) {
		free(list[i]);
		i++;
	}
	free(list);
}


