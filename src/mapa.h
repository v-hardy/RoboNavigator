#ifndef MAPA_H
#define MAPA_H

#define FILAS 20
#define COLUMNAS 20

extern int matriz[FILAS][COLUMNAS];  // Solo la declaración

void rellenar_matriz(int matriz[FILAS][COLUMNAS]);
void imprimir_matriz(int matriz[FILAS][COLUMNAS]);
void imprimir_mapa_ascii(int matriz[FILAS][COLUMNAS]);

#endif
