#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
#include "stdio.h"
#include "stdlib.h"

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

void opcion_uno() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      cargar_matriz();
      
      puts("\nMostrando datos de la matriz...");
      imprimir_matriz();
      
    } else {
    puts("\n 🗺️ El mapa ya fue cargado previamente.​");
    //PODEMOS MOSTRARLO
  }
}

void opcion_dos() {
    puts("\nEstablecer coordenadas manualmente..."); 
    puts("\nRECUERDE: El valor de la posicion va de 1 a 20"); 
    inicializar_robot();      // inicializar el robot
    imprimir_estado_robot();  // mostrar su estado (opcional)
}

void opcion_tres() {
    if (robot.posicion_actual.x == -1) {
      puts("\nPrimero de Inicializar el robot!...🤖​");
    } else { 
      puts("\n  🗺️ Generando Mapa...\n");
      cargar_matriz();
      imprimir_mapa_ascii();
    }
}

void opcion_cuatro() {
    puts("Opcion Numero 4!");
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}