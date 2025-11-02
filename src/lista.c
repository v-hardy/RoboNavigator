#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Variables globales
Nodo* PRIM = NULL;
Nodo* ULT  = NULL;

// Función: encolar un nodo al final de la cola
void encolar_lista(int x, int y) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: No hay memoria disponible\n");
        exit(1);
    }

    nuevo->x = x;
    nuevo->y = y;
    nuevo->sig = NULL;

    if (ULT == NULL) {
        // Cola vacía: nuevo nodo es el primero y último
        PRIM = ULT = nuevo;
    } else {
        // Enlazar al final
        ULT->sig = nuevo;
        ULT = nuevo;
    }
}

// Función: desencolar el nodo del frente
int desencolar_lista(int* x, int* y) {
    if (PRIM == NULL) {
        return 0; // Cola vacía
    }

    Nodo* temp = PRIM;
    *x = temp->x;
    *y = temp->y;

    PRIM = PRIM->sig;
    free(temp);

    // Si se vació la cola, actualizar ULT
    if (PRIM == NULL) {
        ULT = NULL;
    }

    return 1; // Éxito
}

// Función: recorrer e imprimir la cola sin modificarla
void recorrer_lista(void) {
    if (PRIM == NULL) {
        printf("Cola vacía.\n");
        return;
    }

    printf("COLA (de frente a fondo):\n");
    Nodo* actual = PRIM;
    int pos = 1;

    while (actual != NULL) {
        printf("  [%d] -> (%d, %d)\n", pos++, actual->x+1, actual->y+1);
        actual = actual->sig;
    }
    printf("Fin de la cola.\n");
}