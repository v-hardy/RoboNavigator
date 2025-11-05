#ifndef MAPA_H
#define MAPA_H

#define FILAS 20
#define COLUMNAS 20

#include "posicion.h" // para Posicion
#include "robot.h"    // para Robot

extern int matriz[FILAS][COLUMNAS];  // Solo la declaración

void seleccionar_mapa();
bool matriz_vacia(int matriz[FILAS][COLUMNAS]);
void cargar_matriz(int matriz[FILAS][COLUMNAS]);
void borrar_rastros_del_mapa();
void imprimir_matriz();
void imprimir_mapa_ascii();

#endif
