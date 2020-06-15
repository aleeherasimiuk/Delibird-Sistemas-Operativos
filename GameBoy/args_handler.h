/*
 * args_handler.h
 *
 *  Created on: 14 jun. 2020
 *      Author: utnso
 */

#ifndef GAMEBOY_ARGS_HANDLER_H_
#define GAMEBOY_ARGS_HANDLER_H_

#define WRONG_PARAMETERS 0
#define PARAMETERS_OK 1
#define convert_to_int atoi

#include <stdlib.h>
#include <stdio.h>

int handleProcessPokemon(int argc, char* args[]);
int handleNewPokemon(char* process, int argc, char* args[]);
int handleAppearedPokemon(char* process, int argc, char* args[]);
int handleCatchPokemon(char* process, int argc, char* args[]);
int handleCaughtPokemon(char* process, int argc, char* args[]);
int handleGetPokemon(char* process, int argc, char* args[]);
int handleSuscriptor(int argc, char* args[]);

int compare_string(char*, char*);
char* concat_string_config(char*, char*);
int string_has_numbers(char*);
int esColaDeMensaje(char*);
int string_empty(char*);
int isValidDigit(char*);






#endif /* GAMEBOY_ARGS_HANDLER_H_ */
