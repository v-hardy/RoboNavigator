#ifndef CAMINO_H
#define CAMINO_H

#define FILAS    20
#define COLUMNAS 20
#define MAX_NODOS (FILAS * COLUMNAS)

// ======== ESTRUCTURAS =========
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

#endif