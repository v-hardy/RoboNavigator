#ifndef LISTA_H
#define LISTA_H

// Lista simplemente enlazada
typedef struct Nodo {
    int x;              // Coordenada x
    int y;              // Coordenada y
    struct Nodo* sig;   // Puntero al siguiente nodo
} Nodo;

// Variables globales
extern Nodo* PRIM;
extern Nodo* ULT;

// Prototipos de funciones
void encolar_lista(int x, int y);
int desencolar_lista(int* x, int* y); 
void recorrer_lista(void);
void encolar_circular(Nodo** SEG, int x, int y);
void mostrar_circular(Nodo** SEG);
void desencolar_circular(Nodo** SEG);

#endif