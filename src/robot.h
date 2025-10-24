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

// Inicializa el robot con las posiciones obtenidas del mapa
void inicializar_robot(Robot* robot);

// Mueve el robot un paso hacia su destino
void mover_robot(Robot* robot);

// Verifica si el robot ha llegado a su destino
bool robot_ha_llegado(const Robot* robot);

// Imprime el estado actual del robot (para depuración)
void imprimir_estado_robot(const Robot* robot);

#endif // ROBOT_H