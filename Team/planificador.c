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


pthread_mutex_t mutex_cpu_libre;
pthread_cond_t cond_cpu_libre;
int cpu_libre = 1;

sem_t counter_pokemones_libres; // para ver si hay pokemones que no están siendo buscados por algún entrenador
sem_t counter_entrenadores_disponibles; // para ver si hay entrenadores disponibles (new/blocked_idle)
sem_t counter_entrenadores_ready;
sem_t counter_entrenadores_terminados;

pthread_cond_t cond_entrenador_exec;
pthread_mutex_t mutex_entrenador_exec;
pthread_mutex_t mutex_entrenadores_cargando;
pthread_mutex_t mutex_actuales_global;
pthread_mutex_t mutex_objetivo_global;
pthread_mutex_t mutex_pokemones_en_el_mapa;
pthread_mutex_t mutex_pokemones_auxiliares_en_el_mapa;

int entrenadores_totales = 0;

int entrenadores_cargando = 1; // para que no se pueda ejecutar el algoritmo de deadlock

// Configs
int retardo_ciclo_cpu;
char* algoritmo_planificacion;

int quantum_max;
int quantum_actual;
pthread_mutex_t mutex_quantum;
pthread_cond_t cond_quantum;

double estimacion_inicial;
double alpha;
t_tcb* ultimo_desalojado = NULL;

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

	pthread_mutex_init(&(entrenadores_new->mutex)					, NULL);
	pthread_mutex_init(&(entrenadores_ready->mutex)					, NULL);
	pthread_mutex_init(&(entrenadores_blocked_idle->mutex)			, NULL);
	pthread_mutex_init(&(entrenadores_blocked_waiting_caught->mutex), NULL);
	pthread_mutex_init(&(entrenadores_blocked_full->mutex)			, NULL);
	pthread_mutex_init(&(entrenadores_blocked_waiting_trade->mutex)	, NULL);
	pthread_mutex_init(&(entrenadores_exit->mutex)					, NULL);

	pokemones_en_el_mapa = queue_create();
	pokemones_auxiliares_en_el_mapa = list_create();
	retardo_ciclo_cpu = config_get_int_value(config, "RETARDO_CICLO_CPU");

	quantum_max = config_get_int_value(config, "QUANTUM");
	pthread_mutex_init(&mutex_quantum, NULL);
	pthread_cond_init(&cond_quantum, NULL);

	alpha = config_get_double_value(config, "ALPHA");
	estimacion_inicial = config_get_double_value(config, "ESTIMACION_INICIAL");

	pthread_mutex_init(&mutex_cpu_libre, NULL);
	pthread_cond_init(&cond_cpu_libre, NULL);

	sem_init(&counter_pokemones_libres, 0, 0);	// inicio el semaforo en 0 ya que todavia no tengo pokemones.
	sem_init(&counter_entrenadores_ready, 0, 0);
	sem_init(&counter_entrenadores_terminados, 0, 0);

	pthread_cond_init(&cond_entrenador_exec, NULL);
	pthread_mutex_init(&mutex_entrenador_exec					, NULL);
	pthread_mutex_init(&mutex_entrenadores_cargando				, NULL);
	pthread_mutex_init(&mutex_actuales_global					, NULL);
	pthread_mutex_init(&mutex_objetivo_global					, NULL);
	pthread_mutex_init(&mutex_pokemones_en_el_mapa				, NULL);
	pthread_mutex_init(&mutex_pokemones_auxiliares_en_el_mapa	, NULL);

	pthread_t thread;

	// plani largo plazo
	pthread_create(&thread, NULL, mandarABuscarPokemones, NULL);
	pthread_detach(thread);

	//plani corto plazo
	pthread_create(&thread, NULL, planificadorCortoPlazo, NULL);
	pthread_detach(thread);
}

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
		pthread_mutex_lock(&mutex_actuales_global);
		tcb_nuevo->entrenador->pokes_actuales = crearListaDeInventario(pokemon_entrenadores[index_actuales], actuales_global);
		pthread_mutex_unlock(&mutex_actuales_global);

		if (pokemon_entrenadores[index_actuales] != NULL) {	// Por si no todos los entrenadores tienen pokemones
			index_actuales++;
		}

		pthread_mutex_lock(&mutex_objetivo_global);
		tcb_nuevo->entrenador->pokes_objetivos = crearListaDeInventario(objetivos_entrenadores[i], objetivo_global);
		pthread_mutex_unlock(&mutex_objetivo_global);

		pthread_mutex_init(&(tcb_nuevo->exec_mutex), NULL);
		pthread_cond_init(&(tcb_nuevo->exec_cond), NULL);
		tcb_nuevo->ejecucion = 0;

		tcb_nuevo->intercambio = NULL;
		tcb_nuevo->finalizado = 0;

		tcb_nuevo->estim_actual = estimacion_inicial;
		tcb_nuevo->estim_restante = 0;
		tcb_nuevo->real_actual = 0;


		if (entrenadorAlMaximoDeCapacidad(tcb_nuevo->entrenador)) {
			cambiarColaSegunObjetivo(tcb_nuevo, NULL); // Si ya viene lleno desde el config, lo mando a full
		} else {
			log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a NEW porque todavía le falta conseguir pokemones para cumplir su objetivo, y recién se cargó", tcb_nuevo->entrenador->id_entrenador);
			agregarACola(tcb_nuevo, entrenadores_new);
		}

		pthread_create(&thread, NULL, entrenadorMain, tcb_nuevo);
		pthread_detach(thread);
		if (posiciones_entrenadores[i + 1] == NULL)	{ // Si es el ultimo entrenador en cargarse, activo que se pueda ejecutar el deadlock
			pthread_mutex_lock(&mutex_entrenadores_cargando);
			entrenadores_cargando = 0;
			pthread_mutex_unlock(&mutex_entrenadores_cargando);
		}
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
	pthread_mutex_lock(&mutex_objetivo_global);
	for(int i = 0; i < objetivo_global->elements_count; i++) {
		t_list* objetivos = objetivo_global;
		objetivo = list_get(objetivos, i);
		pthread_create(&thread, NULL, enviarGetPokemon, (void*) objetivo->pokemon);
		pthread_detach(thread);
	}
	pthread_mutex_unlock(&mutex_objetivo_global);
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
	for (index = 0; index < list_size(cola->lista); index++) {
		if (tcb == (t_tcb*)list_get(cola->lista, index)) {
			pthread_mutex_unlock(&(cola->mutex));
			return index;
		}
	}
	return -1;
}

void sacarDeCola(t_tcb* tcb, t_cola_planificacion* cola) {
	pthread_mutex_lock(&(cola->mutex));

	int index = indexOf(tcb, cola); // Busco el indice donde se encuentra el elemento

	list_remove(cola->lista, index);
	pthread_mutex_unlock(&(cola->mutex));
}

void agregarACola(t_tcb* tcb, t_cola_planificacion* cola) {
	if (tcb != NULL) {
		pthread_mutex_lock(&(cola->mutex));
		list_add(cola->lista, tcb);
		pthread_mutex_unlock(&(cola->mutex));

		// no se puede hacer switch en punteros
		if (cola == entrenadores_new || cola == entrenadores_blocked_idle) {
			sem_post(&counter_entrenadores_disponibles);
		} else if (cola == entrenadores_ready) {
			sem_post(&counter_entrenadores_ready);
		} else if (cola == entrenadores_blocked_full) {
			// Verifico si el team ya está lleno, en cuyo caso lanzo algoritmo de deteccion de deadlock
			log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a BLOCKED_FULL porque tiene capacidad máxima, pero no cumple su objetivo", tcb->entrenador->id_entrenador);
			pthread_t thread;	// Lo ejecuto en un hilo, porque sino nunca se completaria el agregarLista
			pthread_create(&thread, NULL, verificarSiTeamTerminoDeCapturar, NULL);
			pthread_detach(thread);
		}
	}
}

void cambiarDeCola(t_tcb* tcb, t_cola_planificacion* cola_actual, t_cola_planificacion* cola_destino) {

	if (cola_actual != NULL)
		sacarDeCola(tcb, cola_actual);

	agregarACola(tcb, cola_destino);
}

void cambiarColaSegunCapacidad(t_tcb* tcb) {
	if (entrenadorAlMaximoDeCapacidad(tcb->entrenador)) {
		cambiarColaSegunObjetivo(tcb, entrenadores_blocked_waiting_caught);
	} else {
		log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a BLOCKED_IDLE porque todavía tiene espacio para más pokemones", tcb->entrenador->id_entrenador);
		cambiarDeCola(tcb, entrenadores_blocked_waiting_caught, entrenadores_blocked_idle);
	}
}

void cambiarColaSegunObjetivo(t_tcb* tcb, t_cola_planificacion* cola_actual) {
	if (entrenadorCumpleObjetivo(tcb->entrenador)) {
		log_debug(logger, "Felicidades! El entrenador %d cumplió su objetivo", tcb->entrenador->id_entrenador);
		log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a EXIT porque cumplió su objetivo", tcb->entrenador->id_entrenador);
		tcb->finalizado = 1;
		cambiarDeCola(tcb, cola_actual, entrenadores_exit);

		sem_post(&counter_entrenadores_terminados);
	} else {
		cambiarDeCola(tcb, cola_actual, entrenadores_blocked_full);
	}
}

void ponerAEjecutarEntrenador(t_tcb* tcb) {
	pthread_mutex_lock(&(tcb->exec_mutex));
	entrenador_exec = tcb;
	tcb->ejecucion = 1;
	ocuparCPU();
	pthread_cond_broadcast(&(tcb->exec_cond));	// Desbloqueo a los cond de este tcb
	pthread_mutex_unlock(&(tcb->exec_mutex));
}

//Solo lo saca de ejecucion, otro metodo tiene que cambiarlo de lista
t_tcb* terminarDeEjecutar(t_tcb* tcb) {
	t_tcb* entrenador = NULL;
	if (entrenador_exec != NULL && tcb->ejecucion) {
		tcb->ejecucion = 0;
		entrenador = tcb;
		// SJF
		actualizarValoresSJF(entrenador_exec);
		entrenador_exec = NULL;

		liberarCPU();

		pthread_mutex_unlock(&mutex_quantum);
		quantum_actual = 0;
		pthread_cond_broadcast(&cond_quantum);
		pthread_mutex_unlock(&mutex_quantum);
	}

	return entrenador;
}

void liberarCPU(void) {
	pthread_mutex_lock(&mutex_cpu_libre);
	cpu_libre = 1;
	pthread_cond_signal(&cond_cpu_libre);
	pthread_mutex_unlock(&mutex_cpu_libre);
}

void ocuparCPU(void) {
	pthread_mutex_lock(&mutex_cpu_libre);
	cpu_libre = 0;
	pthread_mutex_unlock(&mutex_cpu_libre);
}

// Bloquear por caught
void bloquearPorEsperarCaught(t_tcb* tcb) {
	log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a BLOCKED_WAITING_CAUGHT porque envió un catch recientemente", tcb->entrenador->id_entrenador);
	agregarACola(tcb, entrenadores_blocked_waiting_caught);
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
	pthread_mutex_lock(&(entrenadores_blocked_idle->mutex));
	int blocked_idle_vacio = list_is_empty(entrenadores_blocked_idle->lista);
	pthread_mutex_unlock(&(entrenadores_blocked_idle->mutex));

	if (!blocked_idle_vacio) {

		pthread_mutex_lock(&(entrenadores_blocked_idle->mutex));
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
		pthread_mutex_unlock(&(entrenadores_blocked_idle->mutex));

		// Si ya tengo al minimo, directamente salgo
		if (menor_distancia == 0) {
			return entrenador_mas_cercano;
		}
	}


	// Busco en new
	pthread_mutex_lock(&(entrenadores_new->mutex));
	int new_vacio = list_is_empty(entrenadores_new->lista);
	pthread_mutex_unlock(&(entrenadores_new->mutex));

	if (!new_vacio) {

		index = 0;

		pthread_mutex_lock(&(entrenadores_blocked_idle->mutex));
		int blocked_idle_vacio = list_is_empty(entrenadores_blocked_idle->lista);
		pthread_mutex_unlock(&(entrenadores_blocked_idle->mutex));

		if (blocked_idle_vacio) { // Si no se busco en los bloqueados
			pthread_mutex_lock(&(entrenadores_new->mutex));
			entrenador_mas_cercano = list_get(entrenadores_new->lista, index++);
			menor_distancia = distanciaA(entrenador_mas_cercano->entrenador->posicion, pokemon->posicion);
			*cola = entrenadores_new;
			pthread_mutex_unlock(&(entrenadores_new->mutex));
		}


		// Recorro en los de estado new
		pthread_mutex_lock(&(entrenadores_new->mutex));
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
		pthread_mutex_unlock(&(entrenadores_new->mutex));
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

		pthread_mutex_lock(&mutex_pokemones_en_el_mapa);
		pokemon = queue_pop(pokemones_en_el_mapa);
		pthread_mutex_unlock(&mutex_pokemones_en_el_mapa);

		// Verifico si el pokemon es necesario.si no lo es, lo devuelvo a la lista.
		pthread_mutex_lock(&mutex_actuales_global);
		t_list* actuales = actuales_global;
		pthread_mutex_lock(&mutex_objetivo_global);
		t_list* objetivos = objetivo_global;
		int objetivo_cumplido = objetivoCumplidoSegunPokemon(pokemon->pokemon, actuales, objetivos);
		pthread_mutex_unlock(&mutex_objetivo_global);
		pthread_mutex_unlock(&mutex_actuales_global);

		if (objetivo_cumplido) {
			// Lo añado a la lista auxiliar, que en caso de que no se atrape a un pokemon, se busca si hay uno de esos en esta lista
			log_debug(logger, "Se pasa el %s de la posicion x:%d y:%d a la lista de auxiliares", pokemon->pokemon->name, pokemon->posicion->posX, pokemon->posicion->posY);

			pthread_mutex_lock(&mutex_pokemones_auxiliares_en_el_mapa);
			list_add(pokemones_auxiliares_en_el_mapa, pokemon);
			pthread_mutex_unlock(&mutex_pokemones_auxiliares_en_el_mapa);
		} else {
			log_debug(logger, "Voy a esperar a que haya entrenadores disponibles");
			sem_wait(&counter_entrenadores_disponibles);

			log_debug(logger, "Hay un pokemon disponible para buscarlo");

			// Cargo en el global, lo cargo aca para que en caso de haber mas de este,
			// Pero necesitar menos instancias, que se queden esperando.
			pthread_mutex_lock(&mutex_actuales_global);
			cargarPokemonEnListaDeInventario(actuales_global, pokemon->pokemon->name);
			pthread_mutex_unlock(&mutex_actuales_global);


			tcb_entrenador = entrenadorMasCercanoA(pokemon, &cola_actual);

			log_debug(logger, "El entrenador %d va a ir a buscarlo", tcb_entrenador->entrenador->id_entrenador);

			tcb_entrenador->entrenador->objetivo = pokemon;

			log_debug(logger, "cantidad de lista actual = %d", cola_actual->lista->elements_count);

			log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d, que está en x: %d y: %d, pasa a READY porque es el más cercano al pokemon %s en x:%d y:%d", tcb_entrenador->entrenador->id_entrenador, tcb_entrenador->entrenador->posicion->posX, tcb_entrenador->entrenador->posicion->posY, pokemon->pokemon->name, pokemon->posicion->posX, pokemon->posicion->posY);
			cambiarDeCola(tcb_entrenador, cola_actual, entrenadores_ready);
		}
	}
}

//////////////////////////////////////////
//			PLANI CORTO PLAZO			//
//////////////////////////////////////////

void *planificadorCortoPlazo(void* _) {
	algoritmo_planificacion = config_get_string_value(config, "ALGORITMO_PLANIFICACION");

	while (1) {	// TODO proceso no en exit
		log_debug(logger, "Planificador de corto plazo esperando a que haya entrenadores en ready");
		sem_wait(&counter_entrenadores_ready);	// Espero a que haya algun entrenador para planificar


		if (strcmp(algoritmo_planificacion, "FIFO") == 0)
			planificarSegunFifo();

		if (strcmp(algoritmo_planificacion, "RR") == 0)
			planificarSegunRR();

		if (strcmp(algoritmo_planificacion, "SJF-CD") == 0)
			planificarSegunSJFCD();

		if (strcmp(algoritmo_planificacion, "SJF-SD") == 0)
			planificarSegunSJFSD();
	}
}

void esperarCpuLibre(void) {
	pthread_mutex_lock(&mutex_cpu_libre);
	while(cpu_libre == 0) pthread_cond_wait(&cond_cpu_libre, &mutex_cpu_libre);
	pthread_mutex_unlock(&mutex_cpu_libre);
}

void desalojarCPU(int ultimo_ciclo) {
	if (entrenador_exec != NULL) {
		log_debug(logger, "Se va a desalojar al entrenador %d", entrenador_exec->entrenador->id_entrenador);
		t_tcb* entrenador_desalojado = terminarDeEjecutar(entrenador_exec);	// Lo saco de ejecucion y lo mando a ready
		if (!ultimo_ciclo) {
			// Si en realidad iba a terminar, no lo mando a ready

			// Puede ser que primero se muestre que se ejecutó otro entrenador antes de "desalojar" a éste, ya que se termina de ejecutar antes, lo que libera el semaforo de cpu libre y el planificador envía otro a ejecutar
			log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a READY por que fué desalojado según el algoritmo %s", entrenador_desalojado->entrenador->id_entrenador, algoritmo_planificacion);
			agregarACola(entrenador_desalojado, entrenadores_ready);
		}
	}
}

	//////////////////////////////////////////
	//				   FIFO					//
	//////////////////////////////////////////

void planificarSegunFifo(void) {
	// como es sin desalojo, tengo que esperar a que este la "cpu" libre
	log_debug(logger, "Planificador %s esperando a que la cpu libere", algoritmo_planificacion);
	esperarCpuLibre();

	// tecnicamente si o si hay un entrenador en ready
	pthread_mutex_lock(&(entrenadores_ready->mutex));
	t_tcb* entrenador_a_ejecutar = (t_tcb*)list_remove(entrenadores_ready->lista, 0); // Saco el primero
	pthread_mutex_unlock(&(entrenadores_ready->mutex));

	log_debug(logger, "Planificador %s pone a ejecutar al entrenador %d", algoritmo_planificacion, entrenador_a_ejecutar->entrenador->id_entrenador);

	log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a EXEC por ser el primero de la cola READY", entrenador_a_ejecutar->entrenador->id_entrenador);
	ponerAEjecutarEntrenador(entrenador_a_ejecutar);
}

	//////////////////////////////////////////
	//				    RR					//
	//////////////////////////////////////////

void planificarSegunRR(void) {
	quantum_actual = quantum_max;

	planificarSegunFifo();

	// Esperar a que se termine el quantum, o que el proceso libere la cpu;
	pthread_mutex_lock(&mutex_quantum);
	while(quantum_actual > 0) pthread_cond_wait(&cond_quantum, &mutex_quantum);
	log_debug(logger, "Planificador RR se vació el quantum");
	pthread_mutex_unlock(&mutex_quantum);

	// cambio de contexto
}

// Tambien libera el RR si se termina de ejecutar
void vaciarQuantum(int ultimo_ciclo) {
	pthread_mutex_lock(&mutex_quantum);
	if (--quantum_actual == 0) {
		desalojarCPU(ultimo_ciclo);
	}
	pthread_cond_broadcast(&cond_quantum);
	pthread_mutex_unlock(&mutex_quantum);
}

	//////////////////////////////////////////
	//				 	 SJF				//
	//////////////////////////////////////////

void planificarSegunSJFCD(void) {
	// Ver si tengo que desalojar al actual, por el nuevo que entra (el ultimo, por como funciona el list add)
	if (entrenador_exec != NULL) {
		pthread_mutex_lock(&(entrenador_exec->exec_mutex));
		log_debug(logger, "Se entra a verificar si se tiene que desalojar el proceso en ejecución");
		pthread_mutex_lock(&(entrenadores_ready->mutex));
		t_tcb* entrenador_a_verificar = list_get(entrenadores_ready->lista, list_size(entrenadores_ready->lista) - 1);
		pthread_mutex_unlock(&(entrenadores_ready->mutex));

		// Ignoro la validacion si el que entró es el último en ser desalojado (ya que por algo fue desalojado), mancha con mancha no engancha
		if (entrenador_a_verificar != ultimo_desalojado) {
			// Se verifica la estimacion del nuevo entrenador contra lo RESTANTE del que está en ejecución
			calcularEstimacion(entrenador_a_verificar);

			double estimacion_restante = maximoDouble(entrenador_exec->estim_actual - entrenador_exec->real_actual, 0.0) ;
			if (estimacionDe(entrenador_a_verificar) < estimacion_restante) {
				// guardo la estimacion restante, que es con lo que se debería comparar al volver a ingresar el entrenador desalojado
				entrenador_exec->estim_restante = estimacion_restante;
				ultimo_desalojado = entrenador_exec;
				desalojarCPU(0);
				pthread_mutex_unlock(&(ultimo_desalojado->exec_mutex));

				sacarDeCola(entrenador_a_verificar, entrenadores_ready);
				log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a EXEC por tener menor estimación que la restante del entrenador actual (%f vs %f)", entrenador_a_verificar->entrenador->id_entrenador, estimacionDe(entrenador_a_verificar), estimacion_restante);
				ponerAEjecutarEntrenador(entrenador_a_verificar);
				return;
			}
		}
		pthread_mutex_unlock(&(entrenador_exec->exec_mutex));
	}

	planificarSegunSJFSD();
}

void planificarSegunSJFSD(void) {
	log_debug(logger, "Planificador %s esperando a que la cpu libere", algoritmo_planificacion);
	esperarCpuLibre();

	pthread_mutex_lock(&(entrenadores_ready->mutex));
	t_tcb* entrenador_a_ejecutar = entrenadorConMenorEstimacion();
	pthread_mutex_unlock(&(entrenadores_ready->mutex));

	log_debug(logger, "Planificador %s pone a ejecutar al entrenador %d", algoritmo_planificacion, entrenador_a_ejecutar->entrenador->id_entrenador);
	log_info(logger, "CAMBIO DE COLA DE PLANIFICACIÓN: el entrenador %d pasa a EXEC por tener la menor estimación (%f)", entrenador_a_ejecutar->entrenador->id_entrenador, estimacionDe(entrenador_a_ejecutar));
	ponerAEjecutarEntrenador(entrenador_a_ejecutar);
}

// Se devuelve el entrenador con menor estimacion, si son iguales desempata FIFO
t_tcb* entrenadorConMenorEstimacion(void) {
	int index = 0;
	t_tcb* entrenador_temp = NULL;

	int pos = 0;
	t_tcb* entrenador_menor_estimacion = list_get(entrenadores_ready->lista, index);
	calcularEstimacion(entrenador_menor_estimacion);
	log_debug(logger, "El entrenador %d tiene una estimación de %f", entrenador_menor_estimacion->entrenador->id_entrenador, estimacionDe(entrenador_menor_estimacion));

	for (index = 1; index < list_size(entrenadores_ready->lista); index++) {
		entrenador_temp = list_get(entrenadores_ready->lista, index);
		calcularEstimacion(entrenador_temp);
		log_debug(logger, "El entrenador %d tiene una estimación de %f", entrenador_temp->entrenador->id_entrenador, estimacionDe(entrenador_temp));
		if (estimacionDe(entrenador_temp) < estimacionDe(entrenador_menor_estimacion)) {
			entrenador_menor_estimacion = entrenador_temp;
			pos = index;
		}
	}

	return list_remove(entrenadores_ready->lista, pos);
}

double estimacionDe(t_tcb* tcb) {
	return tcb->estim_restante > 0 ? tcb->estim_restante : tcb->estim_actual;
}

void calcularEstimacion(t_tcb* tcb) {
	if (estimacionDe(tcb) != 0) // Es 0 si todavia no se calculó
		return;
	// est = alpha * real_ant + (1 - alpha) * est_ant
	double estimacion = alpha * tcb->real_ant + (1 - alpha) * tcb->estim_ant;
	tcb->estim_actual = estimacion;
}

void actualizarValoresSJF(t_tcb* tcb) {
	if (tcb->estim_actual == 0 || tcb->estim_restante != 0)
		return;

	tcb->estim_ant = tcb->estim_actual;
	tcb->real_ant = tcb->real_actual;
	tcb->estim_restante = 0;
	tcb->estim_actual = 0;
	tcb->real_actual = 0;
}

//////////////////////////////////////
//				EJECUCION			//
//////////////////////////////////////

void realizarCicloDeCPU(t_tcb* tcb, int ultimo_ciclo) {
	verificarSiTieneQueEjecutar(tcb);
	sleep(retardo_ciclo_cpu);
	log_debug(logger, "El entrenador %d ejecuta un ciclo de CPU", tcb->entrenador->id_entrenador);
	// SJF
	tcb->real_actual++;
	// RR
	vaciarQuantum(ultimo_ciclo);
}


//////////////////////////////////////
//			OBJETIVOS + MAPA		//
//////////////////////////////////////

int pokemonNecesario(t_pokemon* pokemon) {
	pthread_mutex_lock(&mutex_objetivo_global);
	t_inventario* inventario = buscarInventarioPorPokemonName(objetivo_global, pokemon->name, NULL);
	pthread_mutex_unlock(&mutex_objetivo_global);


	// Solo aceptar si existe en el objetivo, y si no lo recibí
	return inventario != NULL && !pokemonYaRecibido(pokemon->name);
}

void agregarPokemonAlMapa(t_pokemon* pokemon, t_coords* posicion) {
	t_pokemon_en_mapa* pok_mapa = malloc(sizeof(t_pokemon_en_mapa));
	pok_mapa->pokemon = pokemon;
	pok_mapa->posicion = posicion;

	pthread_mutex_lock(&mutex_pokemones_en_el_mapa);
	queue_push(pokemones_en_el_mapa, pok_mapa);
	pthread_mutex_unlock(&mutex_pokemones_en_el_mapa);

	sem_post(&counter_pokemones_libres);
}

void buscarPokemonAuxiliarYPasarAlMapa(char* pokemon_name) {
	int pos = 0;
	t_pokemon_en_mapa* actual;
	pthread_mutex_lock(&mutex_pokemones_auxiliares_en_el_mapa);
	actual = list_get(pokemones_auxiliares_en_el_mapa, pos);
	pthread_mutex_unlock(&mutex_pokemones_auxiliares_en_el_mapa);

	while (actual != NULL && strcmp(actual->pokemon->name, pokemon_name) != 0) {
		// Recorro la lista hasta que se termine o que encuentre un inventario con el mismo nombre del pokemon
		pos++;
		pthread_mutex_lock(&mutex_pokemones_auxiliares_en_el_mapa);
		actual = list_get(pokemones_auxiliares_en_el_mapa, pos);
		pthread_mutex_unlock(&mutex_pokemones_auxiliares_en_el_mapa);
	}

	if (actual != NULL) {
		pthread_mutex_lock(&mutex_pokemones_auxiliares_en_el_mapa);
		list_remove(pokemones_auxiliares_en_el_mapa, pos);
		pthread_mutex_unlock(&mutex_pokemones_auxiliares_en_el_mapa);

		log_debug(logger, "Se pasa el pokemon %s de la lista de auxiliares al mapa", actual->pokemon->name);

		pthread_mutex_lock(&mutex_pokemones_en_el_mapa);
		queue_push(pokemones_en_el_mapa, actual);
		pthread_mutex_unlock(&mutex_pokemones_en_el_mapa);

		sem_post(&counter_pokemones_libres);
	}
}

int teamAlMaximoDeCapacidad(void) {

	pthread_mutex_lock(&mutex_actuales_global);
	int cant_actuales = cantidadDePokemonesEnInventario(actuales_global);
	pthread_mutex_unlock(&mutex_actuales_global);

	pthread_mutex_lock(&mutex_objetivo_global);
	int cant_objetivo = cantidadDePokemonesEnInventario(objetivo_global);
	pthread_mutex_unlock(&mutex_objetivo_global);

	// le resto los catch pendientes ya que realmente no los tiene todavia
	return cant_actuales - catchPendientes() >= cant_objetivo;
}

void* verificarSiTeamTerminoDeCapturar(void* _) {
	pthread_mutex_lock(&mutex_entrenadores_cargando);
	int cargando = entrenadores_cargando;
	pthread_mutex_unlock(&mutex_entrenadores_cargando);

	log_debug(logger, "Entrenadores cargando = %d", cargando);
	if (cargando)
		return NULL;

	if (teamAlMaximoDeCapacidad()) {
		deteccionYCorreccionDeadlock();	// Sigo verificando hasta terminar todos los dea
	}
	return NULL;
}
