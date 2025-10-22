#include "mapa.h"
#include "interfaz.h"
#include <stdio.h>

extern int matriz[FILAS][COLUMNAS];

void opcion_uno() {
  puts("\nEjecutando la opción UNO...");
  rellenar_matriz(matriz);
}

void opcion_dos() {
    puts("\nEjecutando la opción DOS...");
    rellenar_matriz(matriz);
    imprimir_matriz(matriz);
}

void opcion_tres() {
    puts("\nMostrar Mapa ASCII...");
    rellenar_matriz(matriz);
    imprimir_mapa_ascii(matriz);
}
