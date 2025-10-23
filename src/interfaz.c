#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
#include <stdio.h>

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

void opcion_uno(Robot *robot) {
  puts("\nEstablecer coordenadas manualmente..."); 
  puts("\nRECUERDE: El valor de la posicion va de 1 a 20"); 
  inicializar_robot(robot);      // inicializar el robot
  imprimir_estado_robot(robot);  // mostrar su estado (opcional)
}

void opcion_dos(Robot *robot) {
    puts("\nMostrando datos de la matriz...");
    rellenar_matriz(matriz, robot);
    imprimir_matriz(matriz);
}

void opcion_tres(Robot *robot) {
    puts("\n  🗺️ Generando Mapa...\n");
    rellenar_matriz(matriz, robot);
    imprimir_mapa_ascii(matriz);
}
