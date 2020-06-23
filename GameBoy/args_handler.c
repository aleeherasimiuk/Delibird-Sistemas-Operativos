/*
 * args_handler.c
 *
 *  Created on: 14 jun. 2020
 *      Author: utnso
 */

#include "args_handler.h"


int handleProcessPokemon(int argc, char* args[]){

	if(argc > 0){
		char* process = args[0];
		return compare_string(process, "BROKER") || compare_string(process, "TEAM") || compare_string(process, "GAMECARD") || compare_string(process, "SUSCRIPTOR");
	}

	return WRONG_PARAMETERS;

}
int handleNewPokemon(char* process, int argc, char* args[]){

	if(argc != 4)
		return WRONG_PARAMETERS;

	if(!compare_string(process, "BROKER") && !compare_string(process, "GAMECARD"))
		return WRONG_PARAMETERS;

	if(string_empty(args[0]) || string_has_numbers(args[0]))
		return WRONG_PARAMETERS;

	if(!isValidDigit(args[1]) || !isValidDigit(args[2]))
		return WRONG_PARAMETERS;

	if(!isValidDigit(args[3]))
		return WRONG_PARAMETERS;

	return PARAMETERS_OK;

}
int handleAppearedPokemon(char* process, int argc, char* args[]){

	if(argc != 4)
		return WRONG_PARAMETERS;

	if(!compare_string(process, "BROKER") && !compare_string(process, "TEAM"))
		return WRONG_PARAMETERS;

	if(string_has_numbers(args[0]))
		return WRONG_PARAMETERS;

	if(!isValidDigit(args[1]) || !isValidDigit(args[2]))
		return WRONG_PARAMETERS;

	if(!isValidDigit(args[3]))
		return WRONG_PARAMETERS;


	return PARAMETERS_OK;

}
int handleCatchPokemon(char* process, int argc, char* args[]){

	if(argc != 3)
		return WRONG_PARAMETERS;

	if(!compare_string(process, "BROKER") && !compare_string(process, "GAMECARD"))
		return WRONG_PARAMETERS;

	if(string_empty(args[0]) || string_has_numbers(args[0]))
		return WRONG_PARAMETERS;

	if(!isValidDigit(args[1]) || !isValidDigit(args[2]))
		return WRONG_PARAMETERS;


	return PARAMETERS_OK;
}

int handleCaughtPokemon(char* process, int argc, char* args[]){

	if(argc != 2)
		return WRONG_PARAMETERS;

	if(!compare_string(process, "BROKER") && !compare_string(process, "GAMECARD"))
		return WRONG_PARAMETERS;

	if(!isValidDigit(args[0]))
		return WRONG_PARAMETERS;

	if(!compare_string(args[1], "YES") && !compare_string(args[1], "NO"))
		return WRONG_PARAMETERS;

	return PARAMETERS_OK;

}
int handleGetPokemon(char* process, int argc, char* args[]){

	if(argc != 1)
		return WRONG_PARAMETERS;

	if(!compare_string(process, "BROKER") && !compare_string(process, "GAMECARD"))
		return WRONG_PARAMETERS;

	if(string_empty(args[0]) || string_has_numbers(args[0]))
		return WRONG_PARAMETERS;

	return PARAMETERS_OK;

}

int handleSuscriptor(int argc, char* args[]){

	if(argc != 2)
		return WRONG_PARAMETERS;

	if(!esColaDeMensaje(args[0]))
		return WRONG_PARAMETERS;


	if(!isValidDigit(args[1]))
		return WRONG_PARAMETERS;

	return PARAMETERS_OK;
}

// compara si el mensaje recibido es igual a: BROKER, GAMECARD o TEAM.
int compare_string(char* mensaje_recv, char* mensaje) {
	return !strcmp(mensaje_recv, mensaje);
}

// retorna un string donde es la combinación del campo(IP o PUERTO) y el proceso(TEAM, BROKER o GAMECARD)
char* concat_string_config(char* proceso, char* campo) {
	char* str = (char *) malloc(1 + strlen(campo)+ strlen(proceso));
	strcpy(str, campo);
	strcat(str, proceso);

	return str;
}

int string_has_numbers(char* string){
	for(int i = 0; i < 10; i++){
		int j = 0;
		while(string[j] != '\0'){
			if(string[j] == i + '0'){
				return 1;
			}
			j++;
		}
	}
	return 0;
		//string_contains(string, string_itoa(i));
}

int esColaDeMensaje(char* cola){
	return compare_string(cola, "NEW_POKEMON")    ||
		compare_string(cola, "APPEARED_POKEMON")  ||
		compare_string(cola, "CATCH_POKEMON")     ||
		compare_string(cola, "CAUGHT_POKEMON")    ||
		compare_string(cola, "LOCALIZED_POKEMON") ||
		compare_string(cola, "GET_POKEMON");
}

// Intenté usar commons/string.h pero no me funcionó así que hago mi propia implementación
int string_empty(char* str){
	return strlen(str) == 0;
}

int isValidDigit(char* digit){

	if(string_empty(digit))
		return WRONG_PARAMETERS;

	int i = 0;
	while(digit[i] != '\0'){

		if(digit[i] == '-')
			return WRONG_PARAMETERS;

		if(!isdigit(digit[i]))
			return WRONG_PARAMETERS;
		i++;

	}
	return convert_to_int(digit) != 0;
}




