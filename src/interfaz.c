#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
#include "camino.h"
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
    puts("\n\033[1m  🗺️  El mapa ya fue cargado previamente.​\033[0m");
    //PODEMOS PREGUNTAR SI DESEA CAMBIARLO
    //imprimir_mapa_ascii();
  }
}

void opcion_dos() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      puts("\n\033[33m\033[1m  ⚠️  No se puede establecer coordenadas debe cargar el mapa antes.\033[0m");
    } else {
      imprimir_mapa_ascii();
      inicializar_robot();      // inicializar el robot
      imprimir_estado_robot();  // mostrar su estado (opcional)
      imprimir_rastro_del_robot();
    }
}

void opcion_tres() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
        puts("\n\033[33m\033[1m  ⚠️  Mapa no cargado. 🤖 Robot no inicializado.\033[0m");
    } else if (robot.posicion_actual.x == -1) {
      puts("\n\033[33m\033[1m  ⚠️  Robot no inicializado.\033[0m");
      imprimir_mapa_ascii();
    } else { 
      imprimir_rastro_del_robot();
      imprimir_mapa_ascii();
    }
}

void opcion_cuatro() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
        puts("\n\033[33m\033[1m  ⚠️  No se puede planificar ruta. Debe cargar el mapa antes.\033[0m");
    } else if (robot.posicion_actual.x == -1) {
        puts("\n\033[33m\033[1m  ⚠️  No se puede planificar ruta. Debe establecer coordenadas del robot antes.\033[0m");
    } else { 
        construirGrafo();
        int xInicio = robot.posicion_inicial.x;
        int yInicio = robot.posicion_inicial.y;
        int xFin = robot.posicion_destino.x;
        int yFin = robot.posicion_destino.y;
        
        //inicio y fin = a datos del robot
        mostrar_camino(xInicio, yInicio, xFin, yFin);
        imprimir_mapa_ascii();
    }
    //continuar por algoritmo de dijkstra
}

void opcion_cinco() {
    if (robot.ha_llegado == 1) {
        printf("\n  \033[36m\033[1m🤖 El Robot ya se encuentra en el destino.\033[0m\n");
    } else {
        mover_robot(); // si solo si esta inicializado y no esta en el fin
        imprimir_rastro_del_robot();
        if (robot.posicion_actual.x != -1) {
            imprimir_mapa_ascii();
        } 
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

void opcion_siete(){
    borrar_rastros_del_mapa();
    // hay que restablecer al bicho tmb
}