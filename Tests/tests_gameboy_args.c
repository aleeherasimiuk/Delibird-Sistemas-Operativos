/*
 * test_gameboy_args.c
 *
 *  Created on: 14 jun. 2020
 *      Author: utnso
 */

#include "tests_gameboy_args.h"

context (TestsGameBoyArgs) {

	describe("Pruebas de funciones auxiliares") {

		it("Compare String") {
			should_int(compare_string("BROKER", "BROKER")) be equal to (1);
			should_int(compare_string("BROKER", "GAMECARD")) be equal to (0);
		} end

		it("Concat String for Config File") {
			should_string(concat_string_config("BROKER", IP)) be equal to ("IP_BROKER");
			should_string(concat_string_config("BROKER", PUERTO)) be equal to ("PUERTO_BROKER");
		} end

		it("String has Numbers"){

			should_int(string_has_numbers("Test")) be equal to (0);
			should_int(string_has_numbers("Test1")) be equal to (1);
			should_int(string_has_numbers("123")) be equal to (1);

		} end

		it("Is a valid message queue") {

			should_int(esColaDeMensaje("NEW_POKEMON")) be equal to (PARAMETERS_OK);
			should_int(esColaDeMensaje("APPEARED_POKEMON")) be equal to (PARAMETERS_OK);
			should_int(esColaDeMensaje("CATCH_POKEMON")) be equal to (PARAMETERS_OK);
			should_int(esColaDeMensaje("CAUGHT_POKEMON")) be equal to (PARAMETERS_OK);
			should_int(esColaDeMensaje("LOCALIZED_POKEMON")) be equal to (PARAMETERS_OK);
			should_int(esColaDeMensaje("GET_POKEMON")) be equal to (PARAMETERS_OK);

			should_int(esColaDeMensaje("BROKER")) be equal to (WRONG_PARAMETERS);
			should_int(esColaDeMensaje("123")) be equal to (WRONG_PARAMETERS);



		} end

		it("String empty") {

			should_int(string_empty("")) be equal to (1);
			should_int(string_empty("Hello World")) be equal to (0);

		} end

		it("isDigit()") {

			should_int(isdigit('1')) be equal to (1);

		} end

		it("Is valid Digit") {

			should_int(isValidDigit("1")) be equal to (PARAMETERS_OK);
			should_int(isValidDigit("10")) be equal to (PARAMETERS_OK);
			should_int(isValidDigit("1000")) be equal to (PARAMETERS_OK);

			should_int(isValidDigit("0")) be equal to (WRONG_PARAMETERS);
			should_int(isValidDigit("-10")) be equal to (WRONG_PARAMETERS);
			should_int(isValidDigit("BROKER")) be equal to (WRONG_PARAMETERS);
		} end

	} end

    describe("Pruebas de argumentos de Gameboy") {

    	it("Handle Process") {
    		char* caso_de_prueba1[] = {"BROKER", "FOO"};
			char* caso_de_prueba2[] = {"TEAM", "FOO"};
			char* caso_de_prueba3[] = {"GAMECARD", "FOO"};
			char* caso_de_prueba4[] = {"GAMEBOY", "FOO"};
			char* caso_de_prueba5[] = {"BANANA", "FOO"};


			int resultado1 = handleProcessPokemon(2, caso_de_prueba1);
			int resultado2 = handleProcessPokemon(2, caso_de_prueba2);
			int resultado3 = handleProcessPokemon(2, caso_de_prueba3);
			int resultado4 = handleProcessPokemon(2, caso_de_prueba4);
			int resultado5 = handleProcessPokemon(2, caso_de_prueba5);

			should_int(resultado1) be equal to (PARAMETERS_OK);
			should_int(resultado2) be equal to (PARAMETERS_OK);
			should_int(resultado3) be equal to (PARAMETERS_OK);
			should_int(resultado4) be equal to (WRONG_PARAMETERS);
			should_int(resultado5) be equal to (WRONG_PARAMETERS);

    	} end

		it("Handle New Pokemon") {

    		char* caso_de_prueba1[]  = {"Pikachu", "10", "20", "30", "10"};
			char* caso_de_prueba2[]  = {"10", "20", "30"};
			char* caso_de_prueba3[]  = {"10", "20", "30", "40"};
			char* caso_de_prueba4[]  = {"Pikachu", "10", "20", "30", "-50"};
			char* caso_de_prueba5[]  = {"Pikachu", "Diez", "20", "30"};
			char* caso_de_prueba6[]  = {"Pikachu", "10", "Veinte", "30"};
			char* caso_de_prueba7[]  = {"Pikachu", "10", "20", "Treinta"};
			char* caso_de_prueba8[]  = {"Pikachu", "10", "20"};
			char* caso_de_prueba9[]  = {"Pikachu"};
			char* caso_de_prueba10[] = {"Pikachu10"};

			int resultado1 = handleNewPokemon("BROKER", 5, caso_de_prueba1);
			int resultado2 = handleNewPokemon("GAMECARD", 5, caso_de_prueba1);
			int resultado3 = handleNewPokemon("TEAM", 5, caso_de_prueba1);
			int resultado4 = handleNewPokemon("BROKER", 3, caso_de_prueba2);
			int resultado5 = handleNewPokemon("BROKER", 4, caso_de_prueba3);
			int resultado6 = handleNewPokemon("BROKER", 5, caso_de_prueba4);
			int resultado7 = handleNewPokemon("BROKER", 4, caso_de_prueba5);
			int resultado8 = handleNewPokemon("BROKER", 4, caso_de_prueba6);
			int resultado9 = handleNewPokemon("BROKER", 4, caso_de_prueba7);
			int resultado10 = handleNewPokemon("BROKER", 3, caso_de_prueba8);
			int resultado11 = handleNewPokemon("BROKER", 1, caso_de_prueba9);
			int resultado12 = handleNewPokemon("BROKER", 1, caso_de_prueba10);

			should_int(resultado1) be equal to (WRONG_PARAMETERS);
			should_int(resultado2) be equal to (PARAMETERS_OK);
			should_int(resultado3) be equal to (WRONG_PARAMETERS);
			should_int(resultado4) be equal to (WRONG_PARAMETERS);
			should_int(resultado5) be equal to (WRONG_PARAMETERS);
			should_int(resultado6) be equal to (WRONG_PARAMETERS);
			should_int(resultado7) be equal to (WRONG_PARAMETERS);
			should_int(resultado8) be equal to (WRONG_PARAMETERS);
			should_int(resultado9) be equal to (WRONG_PARAMETERS);
			should_int(resultado10) be equal to (WRONG_PARAMETERS);
			should_int(resultado11) be equal to (WRONG_PARAMETERS);
			should_int(resultado12) be equal to (WRONG_PARAMETERS);

    	} end


		it("Handle Appeared Pokemon") {

    		char* caso_de_prueba1[]  = {"Pikachu", "10", "20", "30"};
			char* caso_de_prueba2[]  = {"10", "20", "30"};
			char* caso_de_prueba3[]  = {"10", "20", "30", "40"};
			char* caso_de_prueba4[]  = {"Pikachu", "10", "20", "30", "40"};
			char* caso_de_prueba5[]  = {"Pikachu", "Diez", "20", "30"};
			char* caso_de_prueba6[]  = {"Pikachu", "10", "Veinte", "30"};
			char* caso_de_prueba7[]  = {"Pikachu", "10", "-10", "Treinta"};
			char* caso_de_prueba8[]  = {"Pikachu", "10", "20"};
			char* caso_de_prueba9[]  = {"Pikachu"};
			char* caso_de_prueba10[] = {"Pikachu10"};


			int resultado1  = handleAppearedPokemon("BROKER", 4, caso_de_prueba1);
			int resultado2  = handleAppearedPokemon("TEAM", 4, caso_de_prueba1);
			int resultado3  = handleAppearedPokemon("GAMECARD", 4, caso_de_prueba1);
			int resultado4  = handleAppearedPokemon("BROKER", 3, caso_de_prueba2);
			int resultado5  = handleAppearedPokemon("BROKER", 4, caso_de_prueba3);
			int resultado6  = handleAppearedPokemon("BROKER", 5, caso_de_prueba4);
			int resultado7  = handleAppearedPokemon("BROKER", 4, caso_de_prueba5);
			int resultado8  = handleAppearedPokemon("BROKER", 4, caso_de_prueba6);
			int resultado9  = handleAppearedPokemon("BROKER", 4, caso_de_prueba7);
			int resultado10 = handleAppearedPokemon("BROKER", 3, caso_de_prueba8);
			int resultado11 = handleAppearedPokemon("BROKER", 1, caso_de_prueba9);
			int resultado12 = handleAppearedPokemon("BROKER", 1, caso_de_prueba10);

			should_int(resultado1) be equal to  (PARAMETERS_OK);
			should_int(resultado2) be equal to  (WRONG_PARAMETERS);
			should_int(resultado3) be equal to  (WRONG_PARAMETERS);
			should_int(resultado4) be equal to  (WRONG_PARAMETERS);
			should_int(resultado5) be equal to  (WRONG_PARAMETERS);
			should_int(resultado6) be equal to  (WRONG_PARAMETERS);
			should_int(resultado7) be equal to  (WRONG_PARAMETERS);
			should_int(resultado8) be equal to  (WRONG_PARAMETERS);
			should_int(resultado9) be equal to  (WRONG_PARAMETERS);
			should_int(resultado10) be equal to (WRONG_PARAMETERS);
			should_int(resultado11) be equal to (WRONG_PARAMETERS);
			should_int(resultado12) be equal to (WRONG_PARAMETERS);


    	} end


		it ("Handle Catch Pokemon") {

    		char* caso_de_prueba1[]  = {"Pikachu", "10", "20"};
			char* caso_de_prueba2[]  = {"10", "20", "30"};
			char* caso_de_prueba3[]  = {"10", "20", "30", "40"};
			char* caso_de_prueba4[]  = {"Pikachu", "10", "20", "30"};
			char* caso_de_prueba5[]  = {"Pikachu", "Diez", "20"};
			char* caso_de_prueba6[]  = {"Pikachu", "10", "Veinte"};
			char* caso_de_prueba7[]  = {"Pikachu", "-10", "20"};
			char* caso_de_prueba8[]  = {"Pikachu", "10", "-10"};
			char* caso_de_prueba9[]  = {"Pikachu"};
			char* caso_de_prueba10[] = {"Pikachu10"};

			int resultado1  = handleCatchPokemon("BROKER", 3, caso_de_prueba1);
			int resultado2  = handleCatchPokemon("GAMECARD", 3, caso_de_prueba1);
			int resultado3  = handleCatchPokemon("TEAM", 3, caso_de_prueba1);
			int resultado4  = handleCatchPokemon("BROKER", 3, caso_de_prueba2);
			int resultado5  = handleCatchPokemon("BROKER", 4, caso_de_prueba3);
			int resultado6  = handleCatchPokemon("BROKER", 4, caso_de_prueba4);
			int resultado7  = handleCatchPokemon("BROKER", 3, caso_de_prueba5);
			int resultado8  = handleCatchPokemon("BROKER", 3, caso_de_prueba6);
			int resultado9  = handleCatchPokemon("BROKER", 3, caso_de_prueba7);
			int resultado10 = handleCatchPokemon("BROKER", 3, caso_de_prueba8);
			int resultado11 = handleCatchPokemon("BROKER", 1, caso_de_prueba9);
			int resultado12 = handleCatchPokemon("BROKER", 1, caso_de_prueba10);

			should_int(resultado1)  be equal to (PARAMETERS_OK);
			should_int(resultado2)  be equal to (WRONG_PARAMETERS);
			should_int(resultado3)  be equal to (WRONG_PARAMETERS);
			should_int(resultado4)  be equal to (WRONG_PARAMETERS);
			should_int(resultado5)  be equal to (WRONG_PARAMETERS);
			should_int(resultado6)  be equal to (WRONG_PARAMETERS);
			should_int(resultado7)  be equal to (WRONG_PARAMETERS);
			should_int(resultado8)  be equal to (WRONG_PARAMETERS);
			should_int(resultado9)  be equal to (WRONG_PARAMETERS);
			should_int(resultado10) be equal to (WRONG_PARAMETERS);
			should_int(resultado11) be equal to (WRONG_PARAMETERS);
			should_int(resultado12) be equal to (WRONG_PARAMETERS);



    	} end

		it("Handle Caught Pokemon") {

    		char* caso_de_prueba1[]  = {"10", "YES"};
			char* caso_de_prueba2[]  = {"10", "NO"};
			char* caso_de_prueba3[]  = {"-10", "YES"};
			char* caso_de_prueba4[]  = {"10", "YES", "10"};

			int resultado1  = handleCaughtPokemon("BROKER", 2, caso_de_prueba1);
			int resultado2  = handleCaughtPokemon("GAMECARD", 2, caso_de_prueba1);
			int resultado3  = handleCaughtPokemon("TEAM", 2, caso_de_prueba1);
			int resultado4  = handleCaughtPokemon("BROKER", 2, caso_de_prueba2);
			int resultado5  = handleCaughtPokemon("BROKER", 2, caso_de_prueba3);
			int resultado6  = handleCaughtPokemon("BROKER", 3, caso_de_prueba4);


			should_int(resultado1)  be equal to (PARAMETERS_OK);
			should_int(resultado2)  be equal to (PARAMETERS_OK);
			should_int(resultado3)  be equal to (WRONG_PARAMETERS);
			should_int(resultado4)  be equal to (PARAMETERS_OK);
			should_int(resultado5)  be equal to (WRONG_PARAMETERS);
			should_int(resultado6)  be equal to (WRONG_PARAMETERS);

    	} end


		it("Handle Get Pokemon") {

    		char* caso_de_prueba1[]  = {"PIKACHU"};
			char* caso_de_prueba2[]  = {"PIKACHU", "10"};
			char* caso_de_prueba3[]  = {"10"};

			int resultado1  = handleGetPokemon("BROKER", 1, caso_de_prueba1);
			int resultado2  = handleGetPokemon("GAMECARD", 1, caso_de_prueba1);
			int resultado3  = handleGetPokemon("TEAM", 1, caso_de_prueba1);
			int resultado4  = handleGetPokemon("BROKER", 2, caso_de_prueba2);
			int resultado5  = handleGetPokemon("BROKER", 1, caso_de_prueba3);


			should_int(resultado1)  be equal to (PARAMETERS_OK);
			should_int(resultado2)  be equal to (WRONG_PARAMETERS);
			should_int(resultado3)  be equal to (WRONG_PARAMETERS);
			should_int(resultado4)  be equal to (WRONG_PARAMETERS);
			should_int(resultado5)  be equal to (WRONG_PARAMETERS);

    	} end


		it("Handle Subscriber") {

    		char* caso_de_prueba1[]  = {"NEW_POKEMON", "10"};
			char* caso_de_prueba2[]  = {"APPEARED_POKEMON", "10"};
			char* caso_de_prueba3[]  = {"CATCH_POKEMON", "10"};
			char* caso_de_prueba4[]  = {"CAUGHT_POKEMON", "10"};
			char* caso_de_prueba5[]  = {"LOCALIZED_POKEMON", "10"};
			char* caso_de_prueba6[]  = {"GET_POKEMON", "10"};
			char* caso_de_prueba7[]  = {"NEW_POKEMON"};
			char* caso_de_prueba8[]  = {"BROKER", "10"};
			char* caso_de_prueba9[]  = {"CAUGHT_POKEMON", "-5"};

			int resultado1  = handleSuscriptor(2, caso_de_prueba1);
			int resultado2  = handleSuscriptor(2, caso_de_prueba2);
			int resultado3  = handleSuscriptor(2, caso_de_prueba3);
			int resultado4  = handleSuscriptor(2, caso_de_prueba4);
			int resultado5  = handleSuscriptor(2, caso_de_prueba5);
			int resultado6  = handleSuscriptor(2, caso_de_prueba6);
			int resultado7  = handleSuscriptor(1, caso_de_prueba7);
			int resultado8  = handleSuscriptor(2, caso_de_prueba8);
			int resultado9  = handleSuscriptor(2, caso_de_prueba9);


			should_int(resultado1)  be equal to (PARAMETERS_OK);
			should_int(resultado2)  be equal to (PARAMETERS_OK);
			should_int(resultado3)  be equal to (PARAMETERS_OK);
			should_int(resultado4)  be equal to (PARAMETERS_OK);
			should_int(resultado5)  be equal to (PARAMETERS_OK);
			should_int(resultado6)  be equal to (PARAMETERS_OK);
			should_int(resultado7)  be equal to (WRONG_PARAMETERS);
			should_int(resultado8)  be equal to (WRONG_PARAMETERS);
			should_int(resultado9)  be equal to (WRONG_PARAMETERS);


    	} end

    } end

}


