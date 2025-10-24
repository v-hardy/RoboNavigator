#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapa.h"
#include "robot.h"
#include "interfaz.h"

// ✅ Aquí sí definimos la matriz global
int matriz[FILAS][COLUMNAS] = {0};

int direcciones[5][2];

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
// Función para rellenar la matriz con 0 y 1 (20% de 1)
void cargar_matriz(int matriz[FILAS][COLUMNAS]) {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
        // ACA SE DEBERIA REEMPLAZAR POR MAPAS DEFINIDOS
        for (int i = 0; i < FILAS; i++) {
            for (int j = 0; j < COLUMNAS; j++) {
                // 20% de probabilidad de obstáculo (1), resto vacío (0)
                matriz[i][j] = (rand() % 100 < 20) ? 1 : 0;
            }
        }
    } else {
        printf("Refrescando el mapa...\n");
    }
}

// Función para imprimir la matriz como números
void imprimir_matriz(int matriz[FILAS][COLUMNAS], Robot* robot) {
    // Marcar la posición actual del robot con un 2
    matriz[robot->posicion_actual.x][robot->posicion_actual.y] = 2;

    // agregar logica para lo recorrido
    //matriz[robot->destino.x][robot->destino.y] = 3;

    // agregar logica para paradas intermedias
    //matriz[robot->destino.x][robot->destino.y] = 4;

    // (Opcional) marcar destino con un 5, por ejemplo
    matriz[robot->posicion_destino.x][robot->posicion_destino.y] = 5;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Función para imprimir la matriz como mapa ASCII
void imprimir_mapa_ascii(int matriz[FILAS][COLUMNAS], Robot* robot) {
    // Marcar la posición actual del robot con un 2
    matriz[robot->posicion_actual.x][robot->posicion_actual.y] = 2;

    // agregar logica para lo recorrido
    //matriz[robot->destino.x][robot->destino.y] = 3;

    // agregar logica para paradas intermedias
    //matriz[robot->destino.x][robot->destino.y] = 4;

    // (Opcional) marcar destino con un 5, por ejemplo
    matriz[robot->posicion_destino.x][robot->posicion_destino.y] = 5;

    for (int i = 0; i < FILAS; i++) {
        printf("  ");
        if (i == 0) {
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

Posicion capturar_posiciones_iniciales_del_robot(void) {
    Posicion p;
    do {
        printf("Ingrese la posición inicial del robot (x y): ");
        scanf("%d %d", &p.x, &p.y);
        // Restamos 1 a las coordenadas ingresadas
        p.x -= 1;
        p.y -= 1;
        if (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS) {
            printf("¡Error! Las coordenadas están fuera de los límites del mapa.\n");
        }
    } while (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS);  // Validar que esté dentro del rango
    
    matriz[p.x][p.y] = 2;  // Marcar el robot en la matriz
    return p;
}

Posicion obtener_destino_robot(void) {
    Posicion p;
    do {
        printf("Ingrese la posición destino del robot (x y): ");
        scanf("%d %d", &p.x, &p.y);
        // Restamos 1 a las coordenadas ingresadas
        p.x -= 1;
        p.y -= 1;
        if (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS) {
            printf("¡Error! Las coordenadas están fuera de los límites del mapa.\n");
        }
    } while (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS);  // Validar que esté dentro del rango
    return p;
}
