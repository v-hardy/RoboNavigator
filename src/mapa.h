#ifndef MAPA_H
#define MAPA_H

#define FILAS 20
#define COLUMNAS 20


#include "posicion.h" // para Posicion
#include "robot.h"    // para Robot

extern int matriz[FILAS][COLUMNAS];  // Solo la declaración

void cargar_matriz();
void imprimir_matriz();
void imprimir_mapa_ascii();

// PARA EL ROBOT


// Devuelve la posición inicial del robot
Posicion capturar_posiciones_iniciales_del_robot(void);

// Devuelve la posición de destino del robot
Posicion obtener_destino_robot(void);

#endif
