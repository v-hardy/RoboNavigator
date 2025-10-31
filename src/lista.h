#ifndef LISTA_H
#define LISTA_H

// Estructura para un nodo de la lista doblemente enlazada
typedef struct Nodo {
    int x;              // Coordenada x
    int y;              // Coordenada y
    struct Nodo* sig;   // Puntero al siguiente nodo
    struct Nodo* ant;   // Puntero al nodo anterior
} Nodo;

// Variable global: puntero al primer nodo de la lista
extern Nodo* PRIM;

// Prototipos de funciones
void apilar(int x, int y);              // Apila un nuevo nodo con coordenadas x, y
int desapilar(int* x, int* y);          // Desapila el primer nodo y devuelve x, y

#endif
