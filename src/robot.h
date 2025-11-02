#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include "posicion.h"

extern Posicion p;

typedef struct {
    Posicion posicion_inicial;
    Posicion posicion_actual;
    Posicion posicion_destino;
    bool ha_llegado;
} Robot;

typedef struct {
    int arriba;
    int derecha;
    int abajo;
    int izquierda;
} Desplazamiento;

void inicializar_robot();

void reiniciar_robot();

void mover_segun_lista(int z);

bool robot_ha_llegado();

void imprimir_estado_robot();

void imprimir_rastro_del_robot();

Posicion capturar_posiciones_iniciales_del_robot();

Posicion capturar_posiciones_destino_del_robot();

#endif