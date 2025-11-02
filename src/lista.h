#ifndef LISTA_H
#define LISTA_H

// Estructura para un nodo de la lista simplemente enlazada
typedef struct Nodo {
    int x;              // Coordenada x
    int y;              // Coordenada y
    struct Nodo* sig;   // Puntero al siguiente nodo
} Nodo;

// Variables globales
extern Nodo* PRIM;  // Frente de la cola (primer nodo)
extern Nodo* ULT;   // Fondo de la cola (Ãºltimo nodo)

// Prototipos de funciones
void encolar_lista(int x, int y);             // Inserta al final de la cola
int desencolar_lista(int* x, int* y);         // Elimina del frente y devuelve coordenadas
void recorrer_lista(void);               // Muestra la cola sin modificarla

#endif