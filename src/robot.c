#include <stdio.h>
#include "robot.h"
#include "mapa.h"
#include "posicion.h"  
#include "windows.h"
#include "lista.h"
#include "camino.h"
#include "interfaz.h"

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Función segura para limpiar el buffer
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

Posicion capturar_posiciones_iniciales_del_robot() {
    Posicion p;
    do {
        printf("  Ingrese la posicion inicial del robot (x y): ");
        
        if (scanf("%d %d", &p.x, &p.y) != 2) {
            fprintf(stderr, "  \033[1m\033[31m¡Error! Entrada invalida. Use numeros.\033[0m\n");
            limpiar_buffer();
            continue;
        }

        p.x -= 1;  // x = fila
        p.y -= 1;  // y = columna

        // Validar rango
        if (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS) {
            printf("  \033[1m\033[31m¡Error! Coordenadas fuera del mapa (1-%d, 1-%d).\033[0m\n", FILAS, COLUMNAS);
            continue;
        }

        // Validar que no sea pared
        if (matriz[p.x][p.y] != 0) {
            puts("  \033[1m\033[31m¡Error! No puedes colocar el robot en una pared.\033[0m");
            continue;
        }
        
        break;
    } while (1);

    return p;
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

Posicion capturar_posiciones_destino_del_robot() {
    Posicion p;
    do {
        printf("  Ingrese la posicion destino del robot (x y): ");
        if (scanf("%d %d", &p.x, &p.y) != 2) {
            fprintf(stderr, "  \033[1m\033[31m¡Error! Entrada invalida. Use numeros.\033[0m\n");
            while (getchar() != '\n');
            p.x = p.y = -1;
            continue;
        }

        p.x -= 1;
        p.y -= 1;

        // Validar rango
        if (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS) {
            printf("  \033[1m\033[31m¡Error! Coordenadas fuera del mapa (1-%d, 1-%d).\033[0m\n", FILAS, COLUMNAS);
            continue;
        }

        // Validar que no sea pared
        if (matriz[p.x][p.y] != 0) {
            puts("  \033[1m\033[31m¡Error! El destino no puede estar en una pared.\033[0m");
            continue;
        }

        break;
    } while (1);

    return p;
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>
// cuando el robot llega despoues de hacer los 2 destinos y le ingresamos nuevos destinos solo pide 1 destino en vez de 2, hay que corregir eso, creo que es aca
void inicializar_robot() {
    puts("\033[1m\n  RECUERDE: Para establecer coordenadas, el valor de \n  la posicion osila de 1 a 20, en X e Y.\033[0m\n");
    if (robot.ha_llegado == true) {
        robot.posicion_inicial = robot.posicion_actual;    
        robot.posicion_destino = capturar_posiciones_destino_del_robot();
        robot.ha_llegado = false;
    } else {

        robot.posicion_inicial = capturar_posiciones_iniciales_del_robot();
        robot.posicion_actual = robot.posicion_inicial;

        robot.posicion_destino = capturar_posiciones_destino_del_robot();
        robot.posicion_destinoB = capturar_posiciones_destino_del_robot();
  
        robot.ha_llegado = false;
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

void reiniciar_robot() {
    robot.posicion_inicial = (Posicion){-1, -1};
    robot.posicion_actual = (Posicion){-1, -1};
    robot.posicion_destino = (Posicion){-1, -1};
    robot.ha_llegado = false;
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

bool robot_ha_llegado() {
    return robot.posicion_actual.x == robot.posicion_destino.x &&
           robot.posicion_actual.y == robot.posicion_destino.y;
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

void imprimir_estado_robot() {
    if (robot.posicion_actual.x != -1) {
        if (robot.posicion_actual.x == robot.posicion_inicial.x && robot.posicion_actual.y == robot.posicion_inicial.y) {
            puts("\n\033[32m\033[1m  ✅ El robot se inicializo correctamente.\033[0m");
            printf("\033[1m     Posición inicial: (%d, %d)\033[0m\n", robot.posicion_inicial.x+1, robot.posicion_inicial.y+1);
            printf("\033[1m     Posición destino: (%d, %d)\033[0m\n", robot.posicion_destino.x+1, robot.posicion_destino.y+1);

        } else {
            printf("  Posición inicial: (%d, %d)\n", robot.posicion_inicial.x+1, robot.posicion_inicial.y+1);
            printf("  Posición actual: (%d, %d)\n", robot.posicion_actual.x+1, robot.posicion_actual.y+1);
            printf("  Posición destino: (%d, %d)\n", robot.posicion_destino.x+1, robot.posicion_destino.y+1);
            printf("  ¿Ha llegado?: %s\n", robot.ha_llegado ? "Sí" : "No");
        }
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

void imprimir_rastro_del_robot() {
    if (robot.posicion_actual.x == -1) {
        puts("\n\033[33m\033[1m  ⚠️  El robot no ha sido inicializado.\033[0m\n");
    } else if (robot.posicion_actual.x != -1) {
        if (robot.posicion_actual.x == robot.posicion_inicial.x && robot.posicion_actual.y == robot.posicion_inicial.y) {
            puts("\n\033[32m\033[1m  ✅ El robot está listo para ser usado.\033[0m");
        }

        // Marcar la posicion destino del robot con un 1
        matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 1;
  
        // Marcar la posición actual del robot con un -2
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = -2;
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//Llama Junta las funciones que ayudan a descubrir la ruta que debe tomar el robot

void planificar_ruta(){
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
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//Recorre la lista en la que se guardo el recorrido que debe hacer el robot para llegar a su destino e imprime el mismo en el mapa

void mostrar_ruta(){
    recorrer_lista(); //Internamente marca la ruta planificada previamente
    imprimir_rastro_del_robot();
    imprimir_mapa_ascii();
    Sleep(800);
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//Avanza el robot actualizando la posicion actual del mismo y va imprimiendo el mapa, tambien actualiza el valor Booleano que indica si se llego o no a destino

void mover_robot(){

    int row, col;
    while (desencolar_lista(&row, &col)){

        robot.posicion_actual.x = row;
        robot.posicion_actual.y = col;
       
        limpiarPantalla();
        borrar_rastros_del_mapa();
        imprimir_rastro_del_robot();
    
        imprimir_mapa_ascii();
        Sleep(350);

        robot.ha_llegado = robot_ha_llegado();
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//Una vez el robot llega a destino, se asigna destinoB guardado a destino para calcular la  nueva ruta

void intercambiar_destinos(){
    robot.posicion_destino.x = robot.posicion_destinoB.x;
    robot.posicion_destino.y = robot.posicion_destinoB.y;
    robot.ha_llegado = false;
    imprimir_rastro_del_robot();
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//Junta las funciones en una serie de pasos ordenados para que el robot haga todo el calculo y el movimiento por si mismo

void automatizar_robot(){
    
    planificar_ruta();
    mostrar_ruta();
    limpiarPantalla();
    mover_robot();
}