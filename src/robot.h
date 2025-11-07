#ifndef ROBOT_H
#define ROBOT_H
#include <stdbool.h>
#include "posicion.h"
#include "lista.h"

extern Posicion p;

typedef struct {
    Posicion posicion_inicial;
    Posicion posicion_actual;
    Posicion posicion_destino; 
    Posicion posicion_destinoB; //se agrego nueva posicion de destino a capturar
    //Nodo* circuito;
    bool ha_llegado;
} Robot;



void inicializar_robot();

void reiniciar_robot();

bool robot_ha_llegado();

void imprimir_estado_robot();

void imprimir_rastro_del_robot();

Posicion capturar_posiciones_iniciales_del_robot();

Posicion capturar_posiciones_destino_del_robot();

void mover_robot();

#endif