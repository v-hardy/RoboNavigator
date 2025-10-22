#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapa.h"
#include "interfaz.h"

// ✅ Aquí sí definimos la matriz global
int matriz[FILAS][COLUMNAS];

// Función para rellenar la matriz con 0 y 1 (20% de 1)
void rellenar_matriz(int matriz[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = (rand() % 100 < 20) ? 1 : 0;
        }
    }
}

// Función para imprimir la matriz como números
void imprimir_matriz(int matriz[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para imprimir la matriz como mapa ASCII
void imprimir_mapa_ascii(int matriz[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] == 1)
                printf("█");  // Obstáculo
            else
                printf("░");  // Espacio libre
        }
        printf("\n");
    }
}
