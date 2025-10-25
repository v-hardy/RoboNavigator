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
    puts("\n 🗺️  El mapa ya fue cargado previamente.​");
    //PODEMOS PREGUNTAR SI DESEA MOSTRARLO
  }
}

void opcion_dos() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      puts("⚠️  No se puede establecer coordenadas debe cargar el mapa antes.");
    } else {
      puts("\nRECUERDE: Para establecer coordenadas, el valor de \nla posicion osila de 1 a 20, en X e Y.\n");
      inicializar_robot();      // inicializar el robot
      imprimir_estado_robot();  // mostrar su estado (opcional)
    }
}

void opcion_tres() {
    if (robot.posicion_actual.x == -1) {
      puts("\nPrimero de Inicializar el robot!...🤖​");
    } else { 
      puts("\n  🗺️  Generando Mapa...\n");
      cargar_matriz();
      imprimir_mapa_ascii();
    }
}

void opcion_cuatro() {
    puts("Acá la logica de Planificar ruta hacia el destino");
    //continuar por algoritmo de dijkstra o A*
}

void opcion_cinco() {
    puts("Movimiento bruto");
    mover_robot(); // el verificar_todos_adyacentes(); deberia estar dentro del mover para detectar el casillero libre y mover
    imprimir_mapa_ascii();
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}