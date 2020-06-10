/*
 * test_mensajes.c
 *
 *  Created on: 9 jun. 2020
 *      Author: utnso
 */

#include "tests_mensajes.h"


context (TestsMensajes) {


    describe("Pruebas de Mensajes") {

    	t_pokemon* pikachu;
    	t_coords* coords;

    	uint32_t posicion_x = 150;
    	uint32_t posicion_y = 320;
    	uint32_t una_cantidad = 2;

    	before{

    		pikachu = crearPokemon("Pikachu");
    		coords = crear_coordenadas_from_int(posicion_x, posicion_y);


    	} end

		after{

    		free(pikachu);
        	free(coords);

    	} end

        it("Pikachu se llama Pikachu") {

        	should_string("Pikachu") be equal to(pikachu -> name);

        } end

        it("Pikachu tiene 7 letras + 1 y el \\0 ") {
        	should_int(8) be equal to(pikachu -> name_size);
        } end


        it("Serializar Pokemon") {

        	uint32_t bytes;
        	void* serialized_pokemon = serializarPokemon(pikachu, &bytes);
        	t_buffer* buffer = crearBuffer(serialized_pokemon, bytes);

        	t_pokemon* deserialized_pokemon = deserializarPokemon(buffer);
            should_string("Pikachu") be equal to(deserialized_pokemon -> name);
            free(deserialized_pokemon);
        } end

		it("Crear Coordenadas") {
        	should_int(posicion_x) be equal to (coords -> posX);
        	should_int(posicion_y) be equal to (coords -> posY);
        } end

		it("Serializar Coordenadas") {

			uint32_t bytes;
			void* serialized_coords = serializarCoordenadas(coords, &bytes);

			t_buffer* buffer = crearBuffer(serialized_coords, bytes);

			t_coords* deserialized_coords = deserializarCoordenadas(buffer);
			should_int(posicion_x) be equal to (deserialized_coords -> posX);
			should_int(posicion_y) be equal to (deserialized_coords -> posY);
			free(deserialized_coords);

        } end

		it("New Pokemon") {

        	t_new_pokemon* new_pok = new_pokemon(pikachu, posicion_x, posicion_y, una_cantidad);

        	should_string(new_pok -> pokemon -> name) be equal to ("Pikachu");
        	should_int(new_pok -> coords -> posX) be equal to (posicion_x);
			should_int(new_pok -> coords -> posY) be equal to (posicion_y);
			should_int(new_pok -> cantidad) be equal to (una_cantidad);

			free(new_pok -> coords);
			free(new_pok);

        } end

		it("Appeared Pokemon") {

        	t_appeared_pokemon* ap_pok = appeared_pokemon(pikachu, posicion_x, posicion_y);

        	should_string(ap_pok -> pokemon -> name) be equal to ("Pikachu");
			should_int(ap_pok -> coords -> posX) be equal to (posicion_x);
			should_int(ap_pok -> coords -> posY) be equal to (posicion_y);

			free(ap_pok -> coords);
			free(ap_pok);

        } end


		it("Catch Pokemon") {

        	t_catch_pokemon* catch_pok = catch_pokemon(pikachu, posicion_x, posicion_y);
        	should_string(catch_pok -> pokemon -> name) be equal to ("Pikachu");
			should_int(catch_pok -> coords -> posX) be equal to (posicion_x);
			should_int(catch_pok -> coords -> posY) be equal to (posicion_y);

			free(catch_pok -> coords);
			free(catch_pok);
        } end

		it("Caught Pokemon: Yes") {

        	t_caught_pokemon* caught_pok = caught_pokemon(YES);
        	should_int(caught_pok) be equal to (YES);
        	//free(caught_pok);

        } end

		it("Caught Pokemon: No") {

			t_caught_pokemon* caught_pok = caught_pokemon(NO);
			should_int(caught_pok) be equal to (NO);
			//free(caught_pok);

		} end

		it("Get Pokemon") {

			t_get_pokemon* get_pok = get_pokemon(pikachu);
			should_string(get_pok -> name) be equal to ("Pikachu");
			//free(get_pok);

		} end

		it("GameBoy Subscribing") {

			t_gameboy_queue_to_subscribe* sub = gameboy_queue_subscribe(NEW_POKEMON, 10);

			should_int(sub -> queue_to_subscribe) be equal to (NEW_POKEMON);
			should_int(sub -> seconds) be equal to (10);
			free(sub);

		} end


        skip("this test will fail because \"Hello\" is not \"Bye\"") {
            should_string("Hello") be equal to("Bye");
        } end

    } end

}




