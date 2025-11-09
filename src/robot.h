#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include "posicion.h"
#include "lista.h"

extern Posicion p;

typedef struct {
    Posicion posicion_inicial;
    Posicion posicion_actual;
    Posicion posicion_destino; //destino A (donde busca el objeto)
    Posicion posicion_destinoB; //destino B (donde deja el objeto)
    bool ha_llegado;
    bool es_primer_ciclo;
} Robot;

void inicializar_robot();
void reiniciar_robot();
bool robot_ha_llegado();
void imprimir_estado_robot();
void imprimir_rastro_del_robot();
Posicion capturar_posiciones_iniciales_del_robot();
Posicion capturar_posiciones_destino_del_robot();
void mover_robot();
void intercambiar_destinos();
void planificar_ruta();
void mostrar_ruta();
void automatizar_robot();
void inicializar_sistema();
bool robot_esta_inicializado();

#endif