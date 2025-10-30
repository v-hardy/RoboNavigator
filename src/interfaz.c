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
      imprimir_mapa_ascii();
      
    } else {
    puts("\n  🗺️  El mapa ya fue cargado previamente.​");
    //PODEMOS PREGUNTAR SI DESEA MOSTRARLO
    imprimir_mapa_ascii();
  }
}

void opcion_dos() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      puts(" \n\033[33m\033[1m⚠️  No se puede establecer coordenadas debe cargar el mapa antes.\033[0m\n");
    } else {
      imprimir_mapa_ascii();
      inicializar_robot();      // inicializar el robot
      imprimir_estado_robot();  // mostrar su estado (opcional)
    }
}

void opcion_tres() {
    if (robot.posicion_actual.x == -1) {
      puts(" \n\033[33m\033[1m⚠️  No se puede mostrar mapa. 🤖 Robot no inicializado.\033[0m\n");
    } else { 
      
      imprimir_rastro_del_robot();
      imprimir_mapa_ascii();
    }
}

void opcion_cuatro() {
    puts("Acá la logica de Planificar ruta hacia el destino");
    //continuar por algoritmo de dijkstra o A*
}

void opcion_cinco() {
    mover_robot(); // si solo si esta inicializado y no esta en el fin
    imprimir_rastro_del_robot();
    if (robot.posicion_actual.x != -1) {
      imprimir_mapa_ascii();
    } 
}

void opcion_ocho() {
  puts("\n  \033[1m\033[4mEstado actual del mapa y robot:\033[0m");
  imprimir_estado_robot();
  imprimir_rastro_del_robot();
  imprimir_matriz();
}

void limpiarPantalla(void) {
    #ifdef _WIN32
        system("cls");
    #else
        (void) system("clear"); // o para capturar int r = system("clear");
    #endif
}