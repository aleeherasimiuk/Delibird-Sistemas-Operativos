/*
 * planificador.c
 *
 *  Created on: 1 may. 2020
 *      Author: utnso
 */

#include "planificador.h"

t_cola_planificacion* entrenadores_new; 					// lista de t_tcb*
t_cola_planificacion* entrenadores_ready; 					// lista de t_tcb*
t_cola_planificacion* entrenadores_blocked_idle; 			// lista de t_tcb* que se bloquea sin tareas
t_cola_planificacion* entrenadores_blocked_waiting_caught; 	// acá van los que se bloquean esperando a recibir un caught
t_cola_planificacion* entrenadores_blocked_full; 			// Bloqueados por no poder agarrar mas pokemones, pero no cumplen su objetivo
t_cola_planificacion* entrenadores_blocked_waiting_trade; 	// Bloqueados por esperar a que alguien venga a hacer un intercambio
t_cola_planificacion* entrenadores_exit; 					// lista de t_tcb*
t_tcb* entrenador_exec;

t_list* objetivo_global;  // lista de t_inventario*
t_list* actuales_global; // lista de t_inventario* para contar los pokemones que ya se tienen capturados

t_queue* pokemones_en_el_mapa; // Lista de t_pokemon_en_mapa*
t_list*	pokemones_auxiliares_en_el_mapa; // Lista para guardar los pokemones que tengo por si no se llega a atrapar uno,

int retardo_ciclo_cpu;

sem_t sem_cpu_libre;

sem_t counter_pokemones_libres; // para ver si hay pokemones que no están siendo buscados por algún entrenador
sem_t counter_entrenadores_disponibles; // para ver si hay entrenadores disponibles (new/blocked_idle)
sem_t counter_entrenadores_ready;
sem_t counter_entrenadores_terminados;


sem_t mutex_entrenador_exec;

sem_t mutex_entrenadores_cargando;
sem_t mutex_actuales_global;
sem_t mutex_objetivo_global;
sem_t mutex_pokemones_en_el_mapa;
sem_t mutex_pokemones_auxiliares_en_el_mapa;

int entrenadores_totales = 0;

int entrenadores_cargando = 1; // para que no se pueda ejecutar el algoritmo de deadlock

//////////////////////////////////////
//				STRUCTS				//
//////////////////////////////////////

t_pokemon_en_mapa* crearPokemonEnMapa(t_pokemon* pokemon, t_coords* posicion) {
	t_pokemon_en_mapa* pokemon_en_mapa = malloc(sizeof(t_pokemon_en_mapa));
	pokemon_en_mapa->pokemon = pokemon;
	pokemon_en_mapa->posicion = posicion;

	return pokemon_en_mapa;
}

//////////////////////////////////////
//			INICIALIZACION			//
//////////////////////////////////////

void cargarEntrenadores(void) {
	actuales_global = list_create();
	objetivo_global = list_create();
	sem_init(&counter_entrenadores_disponibles, 0, 0);

	char** posiciones_entrenadores = config_get_array_value(config, "POSICIONES_ENTRENADORES");
	char** pokemon_entrenadores    = config_get_array_value(config, "POKEMON_ENTRENADORES");
	char** objetivos_entrenadores  = config_get_array_value(config, "OBJETIVOS_ENTRENADORES");

	t_tcb* tcb_nuevo;
	pthread_t thread;

	int i = 0;
	int index_actuales = 0;
	while(posiciones_entrenadores[i] != NULL) {

		// CADA i ES UN ENTRENADOR NUEVO

		tcb_nuevo = malloc(sizeof(t_tcb));
		tcb_nuevo->entrenador = malloc(sizeof(t_entrenador));

		tcb_nuevo->entrenador->id_entrenador = i + 1;

		tcb_nuevo->entrenador->posicion = crearCoordenadas(posiciones_entrenadores[i]);

		tcb_nuevo->entrenador->objetivo = NULL;
		sem_wait(&mutex_actuales_global);
		tcb_nuevo->entrenador->pokes_actuales = crearListaDeInventario(pokemon_entrenadores[index_actuales], actuales_global);
		sem_post(&mutex_actuales_global);

		if (pokemon_entrenadores[index_actuales] != NULL) {	// Por si no todos los entrenadores tienen pokemones
			index_actuales++;
		}

		sem_wait(&mutex_objetivo_global);
		tcb_nuevo->entrenador->pokes_objetivos = crearListaDeInventario(objetivos_entrenadores[i], objetivo_global);
		sem_post(&mutex_objetivo_global);

		sem_init(&(tcb_nuevo->sem_ejecucion), 0, 0);

		tcb_nuevo->intercambio = NULL;
		tcb_nuevo->finalizado = 0;

		if (posiciones_entrenadores[i + 1] == NULL)	{ // Si es el ultimo entrenador en cargarse, activo que se pueda ejecutar el deadlock
			sem_wait(&mutex_entrenadores_cargando);
			entrenadores_cargando = 0;
			sem_post(&mutex_entrenadores_cargando);
		}

		if (entrenadorAlMaximoDeCapacidad(tcb_nuevo->entrenador)) {
			agregarALista(tcb_nuevo, entrenadores_blocked_full); // Si ya viene lleno desde el config, lo mando a full
		} else {
			agregarALista(tcb_nuevo, entrenadores_new);
		}

		pthread_create(&thread, NULL, entrenadorMain, tcb_nuevo);
		pthread_detach(thread);
		i++;
	}

	entrenadores_totales = i;

	liberarListaDePunteros(posiciones_entrenadores);
	liberarListaDePunteros(pokemon_entrenadores);
	liberarListaDePunteros(objetivos_entrenadores);
}

void enviarGetsAlBroker(void) {
	t_inventario* objetivo;
	pthread_t thread;
	sem_wait(&mutex_objetivo_global);
	for(int i = 0; i < objetivo_global->elements_count; i++) {
		t_list* objetivos = objetivo_global;
		objetivo = list_get(objetivos, i);
		pthread_create(&thread, NULL, enviarGetPokemon, (void*) objetivo->pokemon);
		pthread_detach(thread);
	}
	sem_post(&mutex_objetivo_global);
}

void iniciarPlanificador(void) {
	// Listas de estados
	entrenadores_new 					= malloc(sizeof(t_cola_planificacion));
	entrenadores_ready 					= malloc(sizeof(t_cola_planificacion));
	entrenadores_blocked_idle 			= malloc(sizeof(t_cola_planificacion));
	entrenadores_blocked_waiting_caught = malloc(sizeof(t_cola_planificacion));
	entrenadores_blocked_full 			= malloc(sizeof(t_cola_planificacion));
	entrenadores_blocked_waiting_trade 	= malloc(sizeof(t_cola_planificacion));
	entrenadores_exit 					= malloc(sizeof(t_cola_planificacion));

	entrenadores_new->lista 					= list_create();
	entrenadores_ready->lista 					= list_create();
	entrenadores_blocked_idle->lista 			= list_create();
	entrenadores_blocked_waiting_caught->lista 	= list_create();
	entrenadores_blocked_full->lista 			= list_create();
	entrenadores_blocked_waiting_trade->lista 	= list_create();
	entrenadores_exit->lista 					= list_create();

	sem_init(&(entrenadores_new->mutex)						, 0, 1);
	sem_init(&(entrenadores_ready->mutex)					, 0, 1);
	sem_init(&(entrenadores_blocked_idle->mutex)			, 0, 1);
	sem_init(&(entrenadores_blocked_waiting_caught->mutex)	, 0, 1);
	sem_init(&(entrenadores_blocked_full->mutex)			, 0, 1);
	sem_init(&(entrenadores_blocked_waiting_trade->mutex)	, 0, 1);
	sem_init(&(entrenadores_exit->mutex)					, 0, 1);

	pokemones_en_el_mapa = queue_create();
	pokemones_auxiliares_en_el_mapa = list_create();
	retardo_ciclo_cpu = config_get_int_value(config, "RETARDO_CICLO_CPU");

	sem_init(&sem_cpu_libre, 0, 1);

	sem_init(&counter_pokemones_libres, 0, 0);	// inicio el semaforo en 0 ya que todavia no tengo pokemones.
	sem_init(&counter_entrenadores_ready, 0, 0);
	sem_init(&counter_entrenadores_terminados, 0, 0);

	sem_init(&mutex_entrenador_exec, 0, 1);
	sem_init(&mutex_entrenadores_cargando, 0, 1);
	sem_init(&mutex_actuales_global, 0, 1);
	sem_init(&mutex_objetivo_global, 0, 1);
	sem_init(&mutex_pokemones_en_el_mapa, 0, 1);
	sem_init(&mutex_pokemones_auxiliares_en_el_mapa, 0, 1);

	pthread_t thread;

	// plani largo plazo
	pthread_create(&thread, NULL, mandarABuscarPokemones, NULL);
	pthread_detach(thread);

	//plani corto plazo
	pthread_create(&thread, NULL, planificadorCortoPlazo, NULL);
	pthread_detach(thread);
}

//////////////////////////////////////
//				ESTADOS				//
//////////////////////////////////////

void esperarAQueFinalicenLosEntrenadores() {
	for (int i = 0; i < entrenadores_totales; i++) {
		sem_wait(&counter_entrenadores_terminados);
	}
}

int indexOf(t_tcb* tcb, t_cola_planificacion* cola) {
	int index;
	sem_wait(&(cola->mutex));
	for (index = 0; index < list_size(cola->lista); index++) {
		if (tcb == (t_tcb*)list_get(cola->lista, index)) {
			sem_post(&(cola->mutex));
			return index;
		}
	}
	sem_post(&(cola->mutex));
	return -1;
}

void sacarDeLista(t_tcb* tcb, t_cola_planificacion* cola) {

	int index = indexOf(tcb, cola); // Busco el indice donde se encuentra el elemento

	sem_wait(&(cola->mutex));
	list_remove(cola->lista, index);
	sem_post(&(cola->mutex));
}

void agregarALista(t_tcb* tcb, t_cola_planificacion* cola) {
	// TODO mandar a finalizado
	sem_wait(&(cola->mutex));
	list_add(cola->lista, tcb);
	sem_post(&(cola->mutex));

	if (tcb != NULL) {
		// no se puede hacer switch en punteros
		if (sonListasIguales(cola, entrenadores_new) || sonListasIguales(cola, entrenadores_blocked_idle)) {
			sem_post(&counter_entrenadores_disponibles);
		} else if (sonListasIguales(cola, entrenadores_ready)) {
			sem_post(&counter_entrenadores_ready);
		} else if (sonListasIguales(cola, entrenadores_blocked_full)) {
			// Verifico si el team ya está lleno, en cuyo caso lanzo algoritmo de deteccion de deadlock
			pthread_t thread;	// Lo ejecuto en un hilo, porque sino nunca se completaria el agregarLista
			pthread_create(&thread, NULL, verificarSiTeamTerminoDeCapturar, NULL);
			pthread_detach(thread);
		}
	}
}

int sonListasIguales(t_cola_planificacion* primero, t_cola_planificacion* segundo) {
	sem_wait(&(primero->mutex));
	t_list* primera_lista = primero->lista;
	sem_post(&(primero->mutex));

	sem_wait(&(segundo->mutex));
	int resultado = primera_lista == segundo->lista;
	sem_post(&(segundo->mutex));

	return resultado;
}

void cambiarDeLista(t_tcb* tcb, t_cola_planificacion* cola_actual, t_cola_planificacion* cola_destino) {

	if (cola_actual != NULL)
		sacarDeLista(tcb, cola_actual);

	agregarALista(tcb, cola_destino);
}

void cambiarListaSegunCapacidad(t_tcb* tcb) {
	if (entrenadorAlMaximoDeCapacidad(tcb->entrenador)) {
		cambiarDeLista(tcb, entrenadores_blocked_waiting_caught, entrenadores_blocked_full);
	} else {
		cambiarDeLista(tcb, entrenadores_blocked_waiting_caught, entrenadores_blocked_idle);
	}
}

void cambiarListaSegunObjetivo(t_tcb* tcb, t_cola_planificacion* cola_actual) {
	if (entrenadorCumpleObjetivo(tcb->entrenador)) {
		log_debug(logger, "Felicidades! El entrenador %d cumplió su objetivo", tcb->entrenador->id_entrenador);
		tcb->finalizado = 1;
		cambiarDeLista(tcb, cola_actual, entrenadores_exit);

		sem_post(&(tcb->sem_ejecucion));	// Activo el semáforo para que se desbloquee y pueda terminar.
		sem_post(&counter_entrenadores_terminados);
	} else {
		cambiarDeLista(tcb, cola_actual, entrenadores_blocked_full);
	}
}

void ponerAEjecutarEntrenador(t_tcb* tcb) {
	sem_wait(&mutex_entrenador_exec);
	entrenador_exec = tcb;
	sem_post(&mutex_entrenador_exec);

	sem_post(&(entrenador_exec->sem_ejecucion));
}

//Solo lo saca de ejecucion, otro metodo tiene que cambiarlo de lista
void terminarDeEjecutar(void) {
	sem_wait(&mutex_entrenador_exec);
	entrenador_exec = NULL;
	sem_post(&mutex_entrenador_exec);

	sem_post(&sem_cpu_libre);
}

// Bloquear por idle
void bloquearPorIdle(t_tcb* tcb) {
	agregarALista(tcb, entrenadores_blocked_idle);
}

// Bloquear por caught
void bloquearPorEsperarCaught(t_tcb* tcb) {
	agregarALista(tcb, entrenadores_blocked_waiting_caught);
}

//////////////////////////////////////
//			PLANI LARGO PLAZO		//
//////////////////////////////////////

t_tcb* entrenadorMasCercanoA(t_pokemon_en_mapa* pokemon, t_cola_planificacion** cola) {

	t_tcb* entrenador_temp = NULL;
	int distancia_temp;
	int menor_distancia;
	t_tcb* entrenador_mas_cercano;
	int index;

	log_debug(logger, "Tamaño de entrenadores_blocked_idle: %d", entrenadores_blocked_idle->lista->elements_count);

	// busco en blocked_idle
	sem_wait(&(entrenadores_blocked_idle->mutex));
	int blocked_idle_vacio = list_is_empty(entrenadores_blocked_idle->lista);
	sem_post(&(entrenadores_blocked_idle->mutex));

	if (!blocked_idle_vacio) {

		sem_wait(&(entrenadores_blocked_idle->mutex));
		entrenador_mas_cercano = list_get(entrenadores_blocked_idle->lista, 0);
		menor_distancia = distanciaA(entrenador_mas_cercano->entrenador->posicion, pokemon->posicion);
		*cola = entrenadores_blocked_idle;

		for (index = 1; index < list_size(entrenadores_blocked_idle->lista); index++) {
			if (menor_distancia == 0) break;	// corto porque sería la distancia minima, entonces dejo de recorrer

			entrenador_temp = list_get(entrenadores_blocked_idle->lista, index);
			distancia_temp = distanciaA(entrenador_temp->entrenador->posicion, pokemon->posicion);

			if (distancia_temp < menor_distancia) {

				entrenador_mas_cercano = entrenador_temp;
				menor_distancia = distancia_temp;
			}
		}
		sem_post(&(entrenadores_blocked_idle->mutex));

		// Si ya tengo al minimo, directamente salgo
		if (menor_distancia == 0) {
			return entrenador_mas_cercano;
		}
	}


	// Busco en new
	sem_wait(&(entrenadores_new->mutex));
	int new_vacio = list_is_empty(entrenadores_new->lista);
	sem_post(&(entrenadores_new->mutex));

	if (!new_vacio) {

		index = 0;

		sem_wait(&(entrenadores_blocked_idle->mutex));
		int blocked_idle_vacio = list_is_empty(entrenadores_blocked_idle->lista);
		sem_post(&(entrenadores_blocked_idle->mutex));

		if (blocked_idle_vacio) { // Si no se busco en los bloqueados
			sem_wait(&(entrenadores_new->mutex));
			entrenador_mas_cercano = list_get(entrenadores_new->lista, index++);
			menor_distancia = distanciaA(entrenador_mas_cercano->entrenador->posicion, pokemon->posicion);
			*cola = entrenadores_new;
			sem_post(&(entrenadores_new->mutex));
		}


		// Recorro en los de estado new
		sem_wait(&(entrenadores_new->mutex));
		for (; index < list_size(entrenadores_new->lista); index++) {
			if (menor_distancia == 0) break;	// corto porque sería la distancia minima, entonces dejo de recorrer

			entrenador_temp = list_get(entrenadores_new->lista, index);
			distancia_temp = distanciaA(entrenador_temp->entrenador->posicion, pokemon->posicion);

			if (distancia_temp < menor_distancia) {
				*cola = entrenadores_new;
				entrenador_mas_cercano = entrenador_temp;
				menor_distancia = distancia_temp;
			}
		}
		sem_post(&(entrenadores_new->mutex));
	}

	return entrenador_mas_cercano;
}

void *mandarABuscarPokemones(void* _) { //Pasar de new/blocked_idle a ready (Planificador a largo plazo)
	t_tcb* tcb_entrenador; // entrenador a pasar a ready - desde new o blocked_idle
	t_pokemon_en_mapa* pokemon;
	t_cola_planificacion* cola_actual = NULL; // Lista en la que se encuentra el entrenador mas cercano

	while(1)  { // TODO no esté en exit el team
		log_debug(logger, "Voy a esperar a que haya pokemones libres");

		sem_wait(&counter_pokemones_libres);

		sem_wait(&mutex_pokemones_en_el_mapa);
		pokemon = queue_pop(pokemones_en_el_mapa);
		sem_post(&mutex_pokemones_en_el_mapa);

		// Verifico si el pokemon es necesario.si no lo es, lo devuelvo a la lista.
		sem_wait(&mutex_actuales_global);
		t_list* actuales = actuales_global;
		sem_wait(&mutex_objetivo_global);
		t_list* objetivos = objetivo_global;
		int objetivo_cumplido = objetivoCumplidoSegunPokemon(pokemon->pokemon, actuales, objetivos);
		sem_post(&mutex_objetivo_global);
		sem_post(&mutex_actuales_global);

		if (objetivo_cumplido) {
			// Lo añado a la lista auxiliar, que en caso de que no se atrape a un pokemon, se busca si hay uno de esos en esta lista
			log_debug(logger, "Se pasa el %s de la posicion x:%d y:%d a la lista de auxiliares", pokemon->pokemon->name, pokemon->posicion->posX, pokemon->posicion->posY);

			sem_wait(&mutex_pokemones_auxiliares_en_el_mapa);
			list_add(pokemones_auxiliares_en_el_mapa, pokemon);
			sem_post(&mutex_pokemones_auxiliares_en_el_mapa);
		} else {
			log_debug(logger, "Voy a esperar a que haya entrenadores disponibles");
			sem_wait(&counter_entrenadores_disponibles);

			log_debug(logger, "Hay un pokemon disponible para buscarlo");

			// Cargo en el global, lo cargo aca para que en caso de haber mas de este,
			// Pero necesitar menos instancias, que se queden esperando.
			sem_wait(&mutex_actuales_global);
			cargarPokemonEnListaDeInventario(actuales_global, pokemon->pokemon->name);
			sem_post(&mutex_actuales_global);


			tcb_entrenador = entrenadorMasCercanoA(pokemon, &cola_actual);

			log_debug(logger, "El entrenador %d va a ir a buscarlo", tcb_entrenador->entrenador->id_entrenador);

			tcb_entrenador->entrenador->objetivo = pokemon;

			log_debug(logger, "cantidad de lista actual = %d", cola_actual->lista->elements_count);

			cambiarDeLista(tcb_entrenador, cola_actual, entrenadores_ready);
		}
	}
}

//////////////////////////////////////////
//			PLANI CORTO PLAZO			//
//////////////////////////////////////////

void *planificadorCortoPlazo(void* _) {
	char* algoritmo_planificacion = config_get_string_value(config, "ALGORITMO_PLANIFICACION");

	while (1) {	// TODO proceso no en exit
		log_debug(logger, "Planificador de corto plazo esperando a que haya entrenadores en ready");
		sem_wait(&counter_entrenadores_ready);	// Espero a que haya algun entrenador para planificar

		if (strcmp(algoritmo_planificacion, "FIFO") == 0)
			planificarSegunFifo();

		/*
		if (strcmp(algoritmo_planificacion, "RR") == 0)
				//planificarSegunRR();

		if (strcmp(algoritmo_planificacion, "SJF-CD") == 0)
			//planificarSegunSJFCD();

		if (strcmp(algoritmo_planificacion, "SJF-SD") == 0)
			//planificarSegunSJFSD();
		*/
	}
}

void planificarSegunFifo(void) {
	// tecnicamente si o si hay un entrenador en ready
	sem_wait(&(entrenadores_ready->mutex));
	t_tcb* entrenador_a_ejecutar = (t_tcb*)list_remove(entrenadores_ready->lista, 0); // Saco el primero
	sem_post(&(entrenadores_ready->mutex));

	log_debug(logger, "Entrenador %s sacado de ready", entrenador_a_ejecutar == NULL ? "NULL" : "Not null");

	// como es sin desalojo, tengo que esperar a que este la "cpu" libre
	log_debug(logger, "Planificador FIFO esperando a que la cpu libere");
	esperarCpuLibre();
	log_debug(logger, "Planificador FIFO pone a ejecutar al entrenador %d", entrenador_a_ejecutar->entrenador->id_entrenador);
	ponerAEjecutarEntrenador(entrenador_a_ejecutar);
}

void esperarCpuLibre(void) {
	sem_wait(&sem_cpu_libre);
}


//////////////////////////////////////
//				EJECUCION			//
//////////////////////////////////////

void realizarCicloDeCPU(void) {
	realizarXCiclosDeCPU(1);
}

void realizarXCiclosDeCPU(int cant_ciclos) {
	sleep(retardo_ciclo_cpu* cant_ciclos);
	log_debug(logger, "Se realizaron %d ciclos de CPU", cant_ciclos);
}



//////////////////////////////////////
//			OBJETIVOS + MAPA		//
//////////////////////////////////////

int pokemonNecesario(t_pokemon* pokemon) {
	sem_wait(&mutex_objetivo_global);
	t_inventario* inventario = buscarInventarioPorPokemonName(objetivo_global, pokemon->name, NULL);
	sem_post(&mutex_objetivo_global);


	// Solo aceptar si existe en el objetivo, y si no lo recibí
	return inventario != NULL && !pokemonYaRecibido(pokemon->name);
}

void agregarPokemonAlMapa(t_pokemon* pokemon, t_coords* posicion) {
	t_pokemon_en_mapa* pok_mapa = malloc(sizeof(t_pokemon_en_mapa));
	pok_mapa->pokemon = pokemon;
	pok_mapa->posicion = posicion;

	sem_wait(&mutex_pokemones_en_el_mapa);
	queue_push(pokemones_en_el_mapa, pok_mapa);
	sem_post(&mutex_pokemones_en_el_mapa);

	sem_post(&counter_pokemones_libres);
}

void buscarPokemonAuxiliarYPasarAlMapa(char* pokemon_name) {
	int pos = 0;
	t_pokemon_en_mapa* actual;
	sem_wait(&mutex_pokemones_auxiliares_en_el_mapa);
	actual = list_get(pokemones_auxiliares_en_el_mapa, pos);
	sem_post(&mutex_pokemones_auxiliares_en_el_mapa);

	while (actual != NULL && strcmp(actual->pokemon->name, pokemon_name) != 0) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		pos++;
		sem_wait(&mutex_pokemones_auxiliares_en_el_mapa);
		actual = list_get(pokemones_auxiliares_en_el_mapa, pos);
		sem_post(&mutex_pokemones_auxiliares_en_el_mapa);
	}

	if (actual != NULL) {
		sem_wait(&mutex_pokemones_auxiliares_en_el_mapa);
		list_remove(pokemones_auxiliares_en_el_mapa, pos);
		sem_post(&mutex_pokemones_auxiliares_en_el_mapa);

		log_debug(logger, "Se pasa el pokemon %s de la lista de auxiliares al mapa", actual->pokemon->name);

		sem_wait(&mutex_pokemones_en_el_mapa);
		queue_push(pokemones_en_el_mapa, actual);
		sem_post(&mutex_pokemones_en_el_mapa);

		sem_post(&counter_pokemones_libres);
	}
}

int teamAlMaximoDeCapacidad(void) {

	sem_wait(&mutex_actuales_global);
	t_list* actuales = actuales_global;
	int cant_actuales = cantidadDePokemonesEnInventario(actuales);
	sem_post(&mutex_actuales_global);

	sem_wait(&mutex_objetivo_global);
	t_list* objetivos = objetivo_global;
	int cant_objetivo = cantidadDePokemonesEnInventario(objetivos);
	sem_post(&mutex_objetivo_global);

	return cant_actuales >= cant_objetivo;
}

void* verificarSiTeamTerminoDeCapturar(void* _) {
	sem_wait(&mutex_entrenadores_cargando);
	int cargando = entrenadores_cargando;
	sem_post(&mutex_entrenadores_cargando);

	log_debug(logger, "Entrenadores cargando = %d", cargando);
	if (cargando)
		return NULL;

	if (teamAlMaximoDeCapacidad()) {

		deteccionYCorreccionDeadlock();	// Sigo verificando hasta terminar todos los dea
	}
	return NULL;
}
