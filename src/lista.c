#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "mapa.h"
#include "robot.h"

// Variables globales
extern Robot robot;
Nodo* PRIM = NULL;
Nodo* ULT  = NULL;
extern int matriz[FILAS][COLUMNAS];

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
    printf("COLA (de inicio a fin):\n");
    Nodo* actual = PRIM;
    int pos = 1;

    while (actual != NULL) {
        // Marca con -7 solo si NO es inicio Y NO es destino
        int es_inicio = (actual->x == robot.posicion_actual.x && actual->y == robot.posicion_actual.y);
        int es_destino = (actual->x == robot.posicion_destino.x && actual->y == robot.posicion_destino.y);

        if (!es_inicio && !es_destino) {
            matriz[actual->x][actual->y] = -7;
        }
        
        printf("  [%d] -> (%d, %d)\n", pos++, actual->x+1, actual->y+1);
        actual = actual->sig;
    }
    printf("Fin de la cola.\n");
}
/*
// Encolar n+1 elementos (coordenadas iniciales x, y)
void encolar_circular(Nodo** SEG, int x, int y) {
    Nodo* nuevo = malloc(sizeof(Nodo));
    if (!nuevo) return;

    nuevo->x = x;
    nuevo->y = y;

    if (*SEG == NULL) {
        *SEG = nuevo;
        nuevo->sig = nuevo;
    } else {
        Nodo* ultimo = *SEG;
        while (ultimo->sig != *SEG){
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevo;
        nuevo->sig = *SEG;
    }
}

//recorrer
void mostrar_circular(Nodo** SEG){
    if (!SEG) {
        printf("Cola vacía\n");
        return;
    }
    Nodo* actual = *SEG;
    printf("Cola: ");
    do {
        printf("(%d,%d) ", actual->x, actual->y);
        actual = actual->sig;
    } while (actual != SEG);
    printf("\n");
}

// Desencolar todos menos el primero (imprime cada uno)
void desencolar_circular(Nodo** SEG) {
    if (SEG == NULL) {
        printf("Lista vacía.\n");
        return;
    }

    Nodo* primero = *SEG;
    Nodo* actual = primero->sig;
    Nodo* temp;

    printf("Desencolando elementos (excepto el inicial):\n");

    while (actual != primero) {
        printf("Desencolado: (%d, %d)\n", actual->x, actual->y);

        temp = actual;
        actual = actual->sig;
        primero->sig = actual;  // Reconecta
        free(temp);
    }

    primero->sig = primero;  // Solo queda el inicial
    printf("Queda solo el nodo inicial: (%d, %d)\n", primero->x, primero->y);
    printf("Coordenadas iniciales preservadas.\n");
}

void liberar_lista_circular(Nodo** cabeza) {
    if (*cabeza == NULL) return;

    Nodo* actual = (*cabeza)->sig;  // empezar desde el segundo
    Nodo* temp;

    // Liberar todos menos el primero
    while (actual != *cabeza) {
        temp = actual;
        actual = actual->sig;
        free(temp);
    }

    // Liberar el primero
    free(*cabeza);
    *cabeza = NULL;
}
*/