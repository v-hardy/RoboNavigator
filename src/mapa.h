#ifndef MAPA_H
#define MAPA_H

#define FILAS 20
#define COLUMNAS 20

#include "posicion.h" // para Posicion
#include "robot.h"    // para Robot

extern int matriz[FILAS][COLUMNAS];  // Solo la declaración

bool matriz_vacia(int matriz[FILAS][COLUMNAS]);
void cargar_matriz();
void imprimir_matriz();
void imprimir_mapa_ascii();

#endif
