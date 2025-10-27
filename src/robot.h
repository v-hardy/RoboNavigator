#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>
#include "posicion.h"

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

// Inicializa el robot con las posiciones obtenidas del mapa
void inicializar_robot();

int verificar_todos_adyacentes();

int prioridad_de_sentido();

// Mueve el robot un paso hacia su destino
void mover_robot();

// Verifica si el robot ha llegado a su destino
bool robot_ha_llegado();

// Imprime el estado actual del robot (para depuración)
void imprimir_estado_robot();

#endif // ROBOT_H