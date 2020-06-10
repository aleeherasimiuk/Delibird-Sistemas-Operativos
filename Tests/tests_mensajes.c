/*
 * test_mensajes.c
 *
 *  Created on: 9 jun. 2020
 *      Author: utnso
 */

#include "tests_mensajes.h"


context (TestsMensajes) {

    describe("Pruebas de Mensajes") {

        it("Pikachu se llama Pikachu") {

        	t_pokemon* pikachu = crearPokemon("Pikachu");
        	should_string("Pikachu") be equal to(pikachu -> name);


        } end

        it("Pikachu tiene 7 letras + 1 y el \\0 ") {
        	t_pokemon* pikachu = crearPokemon("Pikachu");
        	should_int(8) be equal to(pikachu -> name_size);
        } end


        it("Serializar Pokemon") {
        	t_pokemon* pikachu = crearPokemon("Pikachu");
        	uint32_t bytes;
        	void* serialized_pokemon = serializarPokemon(pikachu, &bytes);
        	t_buffer* buffer = malloc(sizeof(uint32_t) + bytes);
        	buffer -> buffer_size = bytes;
        	buffer -> stream = serialized_pokemon;

        	t_pokemon* deserialized_pokemon = deserializarPokemon(buffer);
            should_string("Pikachu") be equal to(deserialized_pokemon -> name);
        } end


        skip("this test will fail because \"Hello\" is not \"Bye\"") {
            should_string("Hello") be equal to("Bye");
        } end

    } end

}




