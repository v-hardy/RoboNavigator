#ifndef MAPA_H
#define MAPA_H

#define FILAS 20
#define COLUMNAS 20

extern int matriz[FILAS][COLUMNAS];  // Solo la declaración

void rellenar_matriz(int matriz[FILAS][COLUMNAS]);
void imprimir_matriz(int matriz[FILAS][COLUMNAS]);
void imprimir_mapa_ascii(int matriz[FILAS][COLUMNAS]);

// PARA EL ROBOT
typedef struct {
    int x;
    int y;
} Posicion;

// Devuelve la posición inicial del robot
Posicion obtener_posicion_inicial_robot(void);

// Devuelve la posición de destino del robot
Posicion obtener_destino_robot(void);

#endif
