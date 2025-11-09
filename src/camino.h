#ifndef CAMINO_H
#define CAMINO_H

#define MAX_NODOS (FILAS * COLUMNAS)

extern int matriz[FILAS][COLUMNAS];

bool explorador();
int marcarAdyacentes(int row, int col, int value, int robot_encontrado);
Posicion encontrar_camino(int mov);
void actualizar_posicion(int x, int y);

#endif