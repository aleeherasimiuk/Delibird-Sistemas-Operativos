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

		it("Crear Coordenadas") {
        	should_int(posicion_x) be equal to (coords -> posX);
        	should_int(posicion_y) be equal to (coords -> posY);
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

		it("Subscribing") {

			t_subscribe* sub = subscribe(NEW_POKEMON, 10);

			should_int(sub -> process_id) be equal to(10);
			should_int(sub -> queue_to_subscribe) be equal to (NEW_POKEMON);

			free(sub);

		} end

		it("GameBoy Subscribing") {

			t_gameboy_queue_to_subscribe* sub = gameboy_queue_subscribe(NEW_POKEMON, 10);

			should_int(sub -> queue_to_subscribe) be equal to (NEW_POKEMON);
			should_int(sub -> seconds) be equal to (10);
			free(sub);

		} end

		it ("Lista de Coordenadas") {

			t_coords* cord1 = malloc(sizeof(t_coords));
			t_coords* cord2 = malloc(sizeof(t_coords));
			t_coords* cord3 = malloc(sizeof(t_coords));
			t_coords* cord4 = malloc(sizeof(t_coords));
			t_coords* cord5 = malloc(sizeof(t_coords));

			cord1 -> posX = 10;
			cord1 -> posY = 20;

			cord2 -> posX = 30;
			cord2 -> posY = 40;

			cord3 -> posX = 50;
			cord3 -> posY = 60;

			cord4 -> posX = 70;
			cord4 -> posY = 80;

			cord5 -> posX = 90;
			cord5 -> posY = 100;

			t_coords** coords = coords_array(5, cord1, cord2, cord3, cord4, cord5);

			t_coords* coord1_test = coords[0];
			t_coords* coord2_test = coords[1];
			t_coords* coord3_test = coords[2];
			t_coords* coord4_test = coords[3];
			t_coords* coord5_test = coords[4];

			should_int(coord1_test -> posX) be equal to (10);
			should_int(coord1_test -> posY) be equal to (20);

			should_int(coord2_test -> posX) be equal to (30);
			should_int(coord2_test -> posY) be equal to (40);

			should_int(coord3_test -> posX) be equal to (50);
			should_int(coord3_test -> posY) be equal to (60);

			should_int(coord4_test -> posX) be equal to (70);
			should_int(coord4_test -> posY) be equal to (80);

			should_int(coord5_test -> posX) be equal to (90);
			should_int(coord5_test -> posY) be equal to (100);

			free(cord1);
			free(cord2);
			free(cord3);
			free(cord4);
			free(cord5);

			free(coords);


		} end

		it("Localized Pokemon") {

			t_coords* cord1 = malloc(sizeof(t_coords));
			t_coords* cord2 = malloc(sizeof(t_coords));
			t_coords* cord3 = malloc(sizeof(t_coords));
			t_coords* cord4 = malloc(sizeof(t_coords));
			t_coords* cord5 = malloc(sizeof(t_coords));

			cord1 -> posX = 10;
			cord1 -> posY = 20;

			cord2 -> posX = 30;
			cord2 -> posY = 40;

			cord3 -> posX = 50;
			cord3 -> posY = 60;

			cord4 -> posX = 70;
			cord4 -> posY = 80;

			cord5 -> posX = 90;
			cord5 -> posY = 100;

			t_coords** coords = coords_array(5, cord1, cord2, cord3, cord4, cord5);


        	t_localized_pokemon* loc_pok = localized_pokemon(pikachu, 5, coords);
        	should_string(loc_pok -> pokemon -> name) be equal to ("Pikachu");
			should_int(loc_pok -> cant_coords) be equal to (5);
			should_int(loc_pok -> coords_array[0] -> posX) be equal to (10);
			should_int(loc_pok -> coords_array[0] -> posY) be equal to (20);
			should_int(loc_pok -> coords_array[1] -> posX) be equal to (30);
			should_int(loc_pok -> coords_array[1] -> posY) be equal to (40);
			should_int(loc_pok -> coords_array[2] -> posX) be equal to (50);
			should_int(loc_pok -> coords_array[2] -> posY) be equal to (60);
			should_int(loc_pok -> coords_array[3] -> posX) be equal to (70);
			should_int(loc_pok -> coords_array[3] -> posY) be equal to (80);
			should_int(loc_pok -> coords_array[4] -> posX) be equal to (90);
			should_int(loc_pok -> coords_array[4] -> posY) be equal to (100);

			free(cord1);
			free(cord2);
			free(cord3);
			free(cord4);
			free(cord5);

			free(loc_pok -> coords_array);
			free(loc_pok);

		} end

    } end

	 describe("Pruebas de Serializacion") {

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

		it("Serializar Pokemon") {

			uint32_t bytes;
			void* serialized_pokemon = serializarPokemon(pikachu, &bytes);
			t_buffer* buffer = crearBuffer(serialized_pokemon, bytes);

			t_pokemon* deserialized_pokemon = deserializarPokemon(&buffer);
			should_string("Pikachu") be equal to(deserialized_pokemon -> name);
			free(serialized_pokemon);
			free(deserialized_pokemon -> name);
			free(deserialized_pokemon);
			//free(buffer -> stream);
			free(buffer);
			//should_ptr(buffer) be equal to (NULL);
		} end

		it("Serializar Coordenadas") {

			uint32_t bytes;
			void* serialized_coords = serializarCoordenadas(coords, &bytes);

			t_buffer* buffer = crearBuffer(serialized_coords, bytes);

			t_coords* deserialized_coords = deserializarCoordenadas(&buffer);
			should_int(posicion_x) be equal to (deserialized_coords -> posX);
			should_int(posicion_y) be equal to (deserialized_coords -> posY);
			free(serialized_coords);
			free(deserialized_coords);
			free(buffer);

		} end

		it("Serializar New Pokemon"){

			t_new_pokemon* new_pok = new_pokemon(pikachu, posicion_x, posicion_y, una_cantidad);

			uint32_t bytes;
			void* serialized_new_pokemon = serializarNewPokemon(new_pok, &bytes);

//			should_int(sizeof(serialized_new_pokemon)) be equal to(sizeof(t_new_pokemon));

			t_buffer* buffer = crearBuffer(serialized_new_pokemon, bytes);

			t_new_pokemon* deserialized_new_pokemon = deserializarNewPokemon(buffer);
			should_string(deserialized_new_pokemon -> pokemon -> name) be equal to ("Pikachu");
			should_int(deserialized_new_pokemon -> pokemon -> name_size) be equal to (8);
			should_int(deserialized_new_pokemon -> coords -> posX) be equal to (posicion_x);
			should_int(deserialized_new_pokemon -> coords -> posY) be equal to (posicion_y);
			should_int(deserialized_new_pokemon -> cantidad) be equal to (una_cantidad);


			free(new_pok);
			free(serialized_new_pokemon);
			free(deserialized_new_pokemon -> pokemon -> name);
			free(deserialized_new_pokemon -> pokemon);
			free(deserialized_new_pokemon -> coords);
			free(deserialized_new_pokemon);
			free(buffer);

		} end

		it("Serializar Appeared Pokemon"){

			t_appeared_pokemon* app_pok = appeared_pokemon(pikachu, posicion_x, posicion_y);

			uint32_t bytes;
			void* serialized_appeared_pokemon = serializarAppearedPokemon(app_pok, &bytes);
			t_buffer* buffer = crearBuffer(serialized_appeared_pokemon, bytes);

			t_appeared_pokemon* deserialized_appeared_pokemon = deserializarAppearedPokemon(buffer);
			should_string(deserialized_appeared_pokemon -> pokemon -> name) be equal to ("Pikachu");
			should_int(deserialized_appeared_pokemon -> coords -> posX) be equal to (posicion_x);
			should_int(deserialized_appeared_pokemon -> coords -> posY) be equal to (posicion_y);

			free(app_pok -> coords);
			free(app_pok);
			free(serialized_appeared_pokemon);
			free(deserialized_appeared_pokemon -> pokemon -> name);
			free(deserialized_appeared_pokemon -> pokemon);
			free(deserialized_appeared_pokemon -> coords);
			free(deserialized_appeared_pokemon);
			free(buffer);

		} end

		it("Serializar Catch Pokemon") {

			t_catch_pokemon* cat_pok = catch_pokemon(pikachu, posicion_x, posicion_y);

			uint32_t bytes;
			void* serialized_catch_pokemon = serializarCatchPokemon(cat_pok, &bytes);
			t_buffer* buffer = crearBuffer(serialized_catch_pokemon, bytes);

			t_catch_pokemon* deserialized_catch_pokemon = deserializarCatchPokemon(buffer);
			should_string(deserialized_catch_pokemon -> pokemon -> name) be equal to ("Pikachu");
			should_int(deserialized_catch_pokemon -> coords -> posX) be equal to (posicion_x);
			should_int(deserialized_catch_pokemon -> coords -> posY) be equal to (posicion_y);


			free(cat_pok -> coords);
			free(cat_pok);
			free(serialized_catch_pokemon);
			free(deserialized_catch_pokemon -> pokemon -> name);
			free(deserialized_catch_pokemon -> pokemon);
			free(deserialized_catch_pokemon -> coords);
			free(deserialized_catch_pokemon);
			free(buffer);

		} end

		skip("Serializar Caught Pokemon") {

			t_caught_pokemon* cau_pok = caught_pokemon(YES);
			free(cau_pok);

		} end



		skip("Serializar Localized Pokemon") {

			t_coords* cord1 = malloc(sizeof(t_coords));
			t_coords* cord2 = malloc(sizeof(t_coords));
			t_coords* cord3 = malloc(sizeof(t_coords));
			t_coords* cord4 = malloc(sizeof(t_coords));
			t_coords* cord5 = malloc(sizeof(t_coords));

			cord1 -> posX = 10;
			cord1 -> posY = 20;

			cord2 -> posX = 30;
			cord2 -> posY = 40;

			cord3 -> posX = 50;
			cord3 -> posY = 60;

			cord4 -> posX = 70;
			cord4 -> posY = 80;

			cord5 -> posX = 90;
			cord5 -> posY = 100;

			t_coords** coords = coords_array(5, cord1, cord2, cord3, cord4, cord5);


			t_localized_pokemon* loc_pok = localized_pokemon(pikachu, 5, coords);

			uint32_t bytes;
			void* serialized_localized = serializarLocalizedPokemon(loc_pok, &bytes);
			t_buffer* buffer = crearBuffer(serialized_localized, bytes);

			t_localized_pokemon* deserialized_loc_pokemon = deserializarLocalizedPokemon(buffer);

//			should_string(deserialized_loc_pokemon -> pokemon -> name) be equal to ("Pikachu");
//			should_int(deserialized_loc_pokemon -> cant_coords) be equal to (5);
//
//			should_string(deserialized_loc_pokemon -> pokemon -> name) be equal to ("Pikachu");
//			should_int(deserialized_loc_pokemon -> cant_coords) be equal to (5);
//			should_int(deserialized_loc_pokemon -> coords_array[0] -> posX) be equal to (10);
//			should_int(deserialized_loc_pokemon -> coords_array[0] -> posY) be equal to (20);
//			should_int(deserialized_loc_pokemon -> coords_array[1] -> posX) be equal to (30);
//			should_int(deserialized_loc_pokemon -> coords_array[1] -> posY) be equal to (40);
//			should_int(deserialized_loc_pokemon -> coords_array[2] -> posX) be equal to (50);
//			should_int(deserialized_loc_pokemon -> coords_array[2] -> posY) be equal to (60);
//			should_int(deserialized_loc_pokemon -> coords_array[3] -> posX) be equal to (70);
//			should_int(deserialized_loc_pokemon -> coords_array[3] -> posY) be equal to (80);
//			should_int(deserialized_loc_pokemon -> coords_array[4] -> posX) be equal to (90);
//			should_int(deserialized_loc_pokemon -> coords_array[4] -> posY) be equal to (100);


		} end

		it("Serializar Subscribe") {

			t_subscribe* sub = subscribe(NEW_POKEMON, 10);

			uint32_t bytes;
			void* serialized_subscribe = serializarSubscribe(sub, &bytes);

			t_buffer* buffer = crearBuffer(serialized_subscribe, bytes);

			t_subscribe* deserialized_subscribe = deserializarSubscribe(buffer);

			should_int(deserialized_subscribe -> process_id) be equal to (10);
			should_int(deserialized_subscribe -> queue_to_subscribe) be equal to (NEW_POKEMON);

			free(sub);
			free(serialized_subscribe);
			free(deserialized_subscribe);
			free(buffer);


		} end

		it("Serializar Gameboy Subscribing") {

			t_gameboy_queue_to_subscribe* sub = gameboy_queue_subscribe(NEW_POKEMON, 10);

			uint32_t bytes;
			void* serialized_subscribe = serializarSubscribeGameboy(sub, &bytes);

			t_buffer* buffer = crearBuffer(serialized_subscribe, bytes);

			t_gameboy_queue_to_subscribe* deserialized_subscribe = deserializarSubscribe(buffer);


			should_int(deserialized_subscribe -> seconds) be equal to (10);
			should_int(deserialized_subscribe -> queue_to_subscribe) be equal to (NEW_POKEMON);

			free(sub);
			free(serialized_subscribe);
			free(deserialized_subscribe);
			free(buffer);


		} end

		// Se usa?????
		skip("Serializar Buffer") {



		} end





    } end

}




