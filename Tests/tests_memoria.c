/*
 * tests_memoria.c
 *
 *  Created on: 21 jun. 2020
 *      Author: utnso
 */


#include "tests_memoria.h"

context(memoria){

	describe("Pruebas memoria"){

		int esPotenciaDeDos(int n){
			double x;
			return modf(log2(n), &x) == 0;
		}

		it("Potencia de dos"){

			should_int(esPotenciaDeDos(128)) be equal to (1);
			should_int(esPotenciaDeDos(100)) be equal to (0);
		} end


	} end

}
