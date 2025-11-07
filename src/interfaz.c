#include "stdio.h"
#include "stdlib.h"
#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
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
      inicializar_robot();
      imprimir_estado_robot();
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
    printf("Opcion 4: ACA HAY QUE AGREGAR OBSTACULO SEGUN 2 COORDENADAS");
}

void opcion_cinco() {
    
    automatizar_robot();
    
    if(robot.posicion_actual.x == robot.posicion_destino.x || robot.posicion_actual.y == robot.posicion_destino.y){

        printf("\n  \033[36m\033[1m🤖 El Robot llego al punto A.\033[0m\n");
        intercambiar_destinos();
        automatizar_robot();
    }
          
}

void opcion_seis(){
    reiniciar_robot();
    borrar_rastros_del_mapa();
}

void opcion_siete() {
    puts("\n  \033[1m\033[4mEstado actual del mapa y robot:\033[0m");
    imprimir_estado_robot();
    imprimir_rastro_del_robot();
    imprimir_matriz();
}