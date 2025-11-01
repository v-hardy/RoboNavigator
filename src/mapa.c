#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapa.h"
#include "robot.h"
#include "interfaz.h"

// ✅ Aquí sí definimos la matriz global
int matriz[FILAS][COLUMNAS] = {0};

int mapa1[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,1,1},
    {1,0,1,0,0,0,1,1,1,1,1,0,0,0,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1},
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,0,0,0,1,1,0,1,0,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
    {1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1},
    {1,1,1,1,1,1,1,0,0,0,0,1,0,0,1,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1},
    {1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
    {1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
extern Robot robot;

// Función para verificar si la matriz está vacía (todos los elementos son 0)
bool matriz_vacia(int matriz[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] != 0) {
                return false;  // Si encontramos un valor distinto de 0, la matriz no está vacía
            }
        }
    }
    return true;  // Si no encontramos valores distintos de 0, la matriz está vacía
}
// Función para rellenar la matriz con 0 y 1
void cargar_matriz() {

    bool mapa_vacio = matriz_vacia(mapa1);
    if (!mapa_vacio) {
    // Copiar los valores de mapa1 a matriz usando un bucle
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                matriz[i][j] = mapa1[i][j];
            }
        }
    }
    // POR SI NO EXISTE MAPA DEFINIDO, GENERA UNO ALEATORIO
    bool vacia = matriz_vacia(matriz);
    if (vacia) {   
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                // 20% de probabilidad de obstáculo (1), resto vacío (0)
                matriz[i][j] = (rand() % 100 < 20) ? 1 : 0;
            }
        }
    }
    puts("\n\033[32m\033[1m  ✅  Mapa cargado con éxito.\033[0m");
        
}

// Función para imprimir la matriz como números
void imprimir_matriz() {
    bool vacia = matriz_vacia(matriz);
    if (!vacia) { 
    // si la matriz esta vacia, deberia avisar y no imprimir
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                if ( j == 0 ) {
                    printf("  ");
                }
                printf("%d ", matriz[i][j]);
            }
            printf("\n");
        }
    } else {
        puts("  \033[33m\033[1m⚠️  Debe cargar el mapa antes.\033[0m\n");
    }
}

// Función para imprimir la matriz como mapa ASCII
void imprimir_mapa_ascii() {
    puts("\n\033[1m  🗺️  Generando Mapa...\033[0m\n");
    for (int i = 0; i < FILAS; i++) {
        printf("  ");
        if (i == 0) {
            printf("    ");
            for (int j = 0; j < COLUMNAS; j++) {
                if (j < 9) {
                printf("0%d  ", j+1 );
                } else if (j == 9) {
                printf("%d ", j+1 );
                } else {
                printf(" %d ", j+1 );
                }
                if ( j+1 == COLUMNAS ) {
                    printf("\n\n  ");
                }
            }
        } 
        printf("%2d |", i + 1);
        for (int j = 0; j < COLUMNAS; j++) {
            if (matriz[i][j] == 1) {
                printf("██");  // Obstáculo
            } else if (matriz[i][j] == 2) {
                printf("🤖​");  // Robot
            } else if (matriz[i][j] == 3) {
                printf("​🔸​​​");  // Recorrido
            } else if (matriz[i][j] == 4) {
                printf("​🚩​​​");  // Parada intermedia
            } else if (matriz[i][j] == 5) {
                printf("🏁​​");  // Destino
            } else {
                printf("░░");  // Espacio libre
            }
            printf("  ");
        }
        printf("%d\n", i+1 );
        printf("\n");
    }
}

