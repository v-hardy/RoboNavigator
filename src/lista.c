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
    nuevo->ant = NULL; // El nuevo nodo será el primero, por lo que no tiene anterior
    
    // Si la lista no está vacía, actualizar el puntero ant del antiguo primer nodo
    if (PRIM != NULL) {
        PRIM->ant = nuevo;
    }
    
    // Actualizar PRIM para que apunte al nuevo nodo
    PRIM = nuevo;
}

// Función para desapilar el primer nodo y devolver sus coordenadas x, y
int desapilar(int* x, int* y) {
    // Verificar si la lista está vacía
    if (PRIM == NULL) {
        return 0; // Retorna 0 si la lista está vacía
    }
    
    // Guardar el nodo a eliminar
    Nodo* temp = PRIM;
    
    // Almacenar los valores x, y antes de liberar el nodo
    *x = temp->x;
    *y = temp->y;
    
    // Actualizar PRIM al siguiente nodo
    PRIM = temp->sig;
    
    // Si hay un nuevo nodo cabeza, su puntero ant debe ser NULL
    if (PRIM != NULL) {
        PRIM->ant = NULL;
    }
    
    // Liberar la memoria del nodo desapilado
    free(temp);
    
    return 1; // Retorna 1 si se logró desapilar con éxito
}
