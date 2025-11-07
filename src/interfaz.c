#include "stdio.h"
#include "stdlib.h"
#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
#include "camino.h"
#include "lista.h"
#include "windows.h"

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        (void) system("clear"); // o para capturar int r = system("clear");
    #endif
}

void opcion_uno() {

    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      seleccionar_mapa();    
      imprimir_mapa_ascii();
      
    } else {
    puts("\n\033[1m  🗺️  Ya hay un mapa cargado. ¿Desea reemplazarlo?​\033[0m");
        seleccionar_mapa();
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
        if (robot.ha_llegado != true) {
            explorador();
            int cant=0;

            actualizar_posicion(robot.posicion_actual.x, robot.posicion_actual.y);
            Posicion pos;

            while((pos.x != robot.posicion_destino.x || pos.y != robot.posicion_destino.y) && cant < 100){ //cant es una variable de seguridad nada mas
        
                cant++;
                //printf("Cantidad de iteraciones: %d\n", cant);

                pos = encontrar_camino(cant);
            }
            
            //printf(" Esta es la cantidad de %d pasos ", cant);
            //imprimir_mapa_ascii();
            
        } else if (robot.ha_llegado == true) {
            printf("\n  \033[36m\033[1m🤖 Establezca nuevas coordenadas para poder planificar ruta.\033[0m\n");
        }
    }
    //continuar por algoritmo de dijkstra
}

void opcion_cinco() {
    
    mover_robot();

    if(robot.posicion_actual.x == robot.posicion_destino.x || robot.posicion_actual.y == robot.posicion_destino.y){

        printf("\n  \033[36m\033[1m🤖 El Robot ya se encuentra en el destino.\033[0m\n");
    }
    
    //printf("\n  \033[36m\033[1m  🤖 El robot debe tener un ruta planificada para que se mueva.\033[0m\n");
      
}

void opcion_seis() {
    recorrer_lista();
    imprimir_rastro_del_robot();
    imprimir_mapa_ascii();
}

void opcion_siete(){
    reiniciar_robot();
    borrar_rastros_del_mapa();
}

void opcion_ocho() {
    puts("\n  \033[1m\033[4mEstado actual del mapa y robot:\033[0m");
    imprimir_estado_robot();
    imprimir_rastro_del_robot();
    imprimir_matriz();
}

