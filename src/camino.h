#ifndef CAMINO_H
#define CAMINO_H

#define FILAS    20
#define COLUMNAS 20
#define MAX_NODOS (FILAS * COLUMNAS)
 
extern int mapa2[FILAS][COLUMNAS];

typedef struct {
    int x, y;
    int vecinos[4];
    int num_vecinos;
} Nodo;

typedef struct {
    int datos[MAX_NODOS];
    int frente;
    int fondo;
} Cola;

void construirGrafo();
int busqueda_camino(int inicio, int fin, int padre[MAX_NODOS]);
int mostrar_camino(int xInicio, int yInicio, int xFin, int yFin);

#endif