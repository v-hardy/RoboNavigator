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

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Agrega un nodo al final de la cola
void encolar_lista(int x, int y){
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: No hay memoria disponible\n");
        exit(1);
    }

    nuevo->x = x;
    nuevo->y = y;
    nuevo->sig = NULL;

    if (ULT == NULL) {
        // Cola vacia: nuevo nodo es el primero y ultimo
        PRIM = ULT = nuevo;
    } else {
        // Agrego al final
        ULT->sig = nuevo;
        ULT = nuevo;
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Desencolar o recuperar el nodo inicial
int desencolar_lista(int* x, int* y){
    if (PRIM == NULL) {
        return 0; // Cola vacia
    }

    Nodo* temp = PRIM;
    *x = temp->x;
    *y = temp->y;

    PRIM = PRIM->sig;
    free(temp);

    // Si se vacio la cola, actualizar ULT
    if (PRIM == NULL) {
        ULT = NULL;
    }

    return 1;
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Recorrer, imprimir, y marcar las posiciones para pintar el camino a seguir de la cola sin modificarla
void recorrer_lista(void){
    if (PRIM == NULL) {
        printf("Cola vacía.\n");
        return;
    }
    
    Nodo* actual = PRIM;
    int pos = 1;

    while (actual != NULL) {
        
        // Marca con -7 solo si NO es inicio Y NO es destino
        int es_inicio = (actual->x == robot.posicion_actual.x && actual->y == robot.posicion_actual.y);
        int es_destino = (actual->x == robot.posicion_destino.x && actual->y == robot.posicion_destino.y);

        if (!es_inicio && !es_destino) {
            matriz[actual->x][actual->y] = -7;
        }
        
        //printf("  [%d] -> (%d, %d)\n", pos++, actual->x+1, actual->y+1);
        actual = actual->sig;
    }
    //printf("Fin de la cola.\n");
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Solo verifica si la cola está vacía
bool lista_vacia(){
    return PRIM == NULL; 
}