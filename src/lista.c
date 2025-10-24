#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Nodo* PRIM = NULL;

// Función para apilar un nodo con coordenadas x, y

void apilar(int x, int y) {
    // Crear nuevo nodo
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: No hay memoria disponible\n");
        exit(1);
    }
    
    // Asignar valores
    nuevo->x = x;
    nuevo->y = y;
    nuevo->sig = PRIM; 
    
    PRIM = nuevo;
}


// Función para desapilar el primer nodo y devolver sus coordenadas x, y

int desapilar(int* x, int* y) {

    // Verificar si la lista está vacía
    if (PRIM == NULL) {
        return 0; // Retorna 1 si la lista esta vacia
        
    }
    
    // Guardar el nodo a eliminar (nuevo (temp))
    Nodo* temp = PRIM;
    
    // Almacenar los valores x, y antes de liberar el nodo
    *x = temp->x;
    *y = temp->y;
    
    // Actualizar PRIM al siguiente nodo
    PRIM = temp->sig;
    
    // Liberar la memoria del nodo desapilado
    free(temp);
    
    return 1;  // Retorna 1 si se logro éxito
}