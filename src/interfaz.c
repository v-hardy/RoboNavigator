#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
#include <stdio.h>

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

void opcion_uno(Robot* robot) {
    if (robot == NULL) {
      puts("\nPrimero de Inicializar el robot!...🤖​");
    } else {
      puts("\nMostrando datos de la matriz...");
      cargar_matriz(matriz);
      imprimir_matriz(matriz, robot);
  }
}

void opcion_dos(Robot* robot) {
    puts("\nEstablecer coordenadas manualmente..."); 
    puts("\nRECUERDE: El valor de la posicion va de 1 a 20"); 
    inicializar_robot(robot);      // inicializar el robot
    imprimir_estado_robot(robot);  // mostrar su estado (opcional)
}

void opcion_tres(Robot* robot) {
    if (robot == NULL) {
      puts("\nPrimero de Inicializar el robot!...🤖​");
    } else { 
      puts("\n  🗺️ Generando Mapa...\n");
      cargar_matriz(matriz);
      imprimir_mapa_ascii(matriz, robot);
    }
}

void opcion_cuatro(Robot* robot) {
    puts("Opcion Numero 4!");
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}