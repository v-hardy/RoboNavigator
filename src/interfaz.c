#include "stdio.h"
#include "stdlib.h"
#include "mapa.h"
#include "robot.h"
#include "interfaz.h"
#include "windows.h"

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Ve que sistema operativo se esta utilizando para limpiar la pantalla con la funcion correspondiente

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        (void) system("clear");
    #endif
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 1.- Cargar mapa

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

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//  2.- Establecer coordenadas del robot

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

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 3.- Mostrar Mapa+Robot ASCII

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

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 4.- Agregar Obstaculo

void opcion_cuatro() {
    printf("Opcion 4: ACA HAY QUE AGREGAR OBSTACULO SEGUN 2 COORDENADAS");
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 5.- Mover robot hacia el destino

void opcion_cinco() {
    
    automatizar_robot();
    
    if(robot.posicion_actual.x == robot.posicion_destino.x || robot.posicion_actual.y == robot.posicion_destino.y){

        printf("\n  \033[36m\033[1m🤖 El Robot llego al punto A.\033[0m\n");
        intercambiar_destinos();
        automatizar_robot();
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 6.- Reiniciar mapa

void opcion_seis(){
    reiniciar_robot();
    borrar_rastros_del_mapa();
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 7.- Ver estado de la matriz

void opcion_siete(){
    puts("\n  \033[1m\033[4mEstado actual del mapa y robot:\033[0m");
    imprimir_estado_robot();
    imprimir_rastro_del_robot();
    imprimir_matriz();
}