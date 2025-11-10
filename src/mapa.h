#ifndef MAPA_H
#define MAPA_H

#define FILAS 20
#define COLUMNAS 20

#include "posicion.h" 
#include "robot.h"    

extern int matriz[FILAS][COLUMNAS];
extern int ultimo_mapa_seleccionado;

extern int mapa1[20][20];
extern int mapa2[20][20];
extern int mapa3[20][20];

void seleccionar_mapa();
bool matriz_vacia(int matriz[FILAS][COLUMNAS]);
void cargar_matriz(int matriz[FILAS][COLUMNAS]);
void borrar_rastros_del_mapa();
void imprimir_matriz();
void imprimir_mapa_ascii();
int agregar_obstaculo(int fila, int columna);
void limpiar_numeritos(void);

#endif
