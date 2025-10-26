#include "robot.h"
#include "mapa.h"   // 👈 necesario para capturar_posiciones_iniciales_del_robot() y obtener_destino_robot()
#include <stdio.h>

extern Robot robot;

// Inicializa el robot con posición y destino desde el mapa,
void inicializar_robot() {
    robot.posicion_inicial = capturar_posiciones_iniciales_del_robot();
    robot.posicion_actual = robot.posicion_inicial;
    robot.posicion_destino = obtener_destino_robot();
    robot.ha_llegado = false;
}

// Verifica si el robot ha llegado a su destino
bool robot_ha_llegado() {
    return robot.posicion_actual.x == robot.posicion_destino.x &&
           robot.posicion_actual.y == robot.posicion_destino.y;
}

int verificar_todos_adyacentes() {
    // printf("hola %d", matriz[10][10]);
    int verificado = 0 ; 
    
    int arriba = matriz[robot.posicion_actual.x-1][robot.posicion_actual.y];
    if( arriba != 3 ) {
        verificado += 1*arriba ;
    }
    
    int der = matriz[robot.posicion_actual.x][robot.posicion_actual.y+1];   
    if( der != 3 ) {
        verificado += 2*der ;
    }

    int abajo = matriz[robot.posicion_actual.x+1][robot.posicion_actual.y];
    if( abajo != 3 ) {
        verificado += 4*abajo ;
    }

    int izq = matriz[robot.posicion_actual.x][robot.posicion_actual.y-1];
    if( izq != 3 ) {
        verificado += 8*izq ;
    }

    printf("posicion robot X %d", robot.posicion_actual.x);
    printf(" posicion robot Y %d", robot.posicion_actual.y);
    //Esto imprime los valores que hay en la matriz
    if (verificado == 1) {
        printf("\n Hay obstaculo hacia arriba.");
    } else if (verificado == 2) {
        printf("\n Hay obstaculo hacia la derecha.");
    } else if (verificado == 3) {
        printf("\n Hay obstaculo hacia arriba y hacia la derecha.");
    } else if (verificado == 4) {
        printf("\n Hay obstaculo hacia abajo.");
    } else if (verificado == 5) {
        printf("\n Hay obstaculo hacia arriba y hacia abajo.");
    } else if (verificado == 6) {
        printf("\n Hay obstaculo hacia la derecha y hacia abajo.");
    } else if (verificado == 7) {
        printf("\n Hay obstaculo hacia arriba, derecha y abajo.");
    } else if (verificado == 8) {
        printf("\n Hay obstaculo hacia la izquierda.");
    } else if (verificado == 9) {
        printf("\n Hay obstaculo hacia arriba y hacia la izquierda.");
    } else if (verificado == 10) {
        printf("\n Hay obstaculo hacia la derecha y hacia la izquierda.");
    } else if (verificado == 11) {
        printf("\n Hay obstaculo hacia arriba, derecha y hacia la izquierda.");
    } else if (verificado == 12) {
        printf("\n Hay obstaculo hacia abajo y hacia la izquierda.");
    } else if (verificado == 13) {
        printf("\n Hay obstaculo hacia arriba, abajo y hacia la izquierda.");
    } else if (verificado == 14) {
        printf("\n Hay obstaculo hacia la derecha, abajo y hacia la izquierda.");
    } else if (verificado == 15) {
        printf("\n Hay obstaculo hacia arriba, derecha, abajo y hacia la izquierda.");
    } else {
        printf("\n No hay obstáculos.");
    }

    printf("\n Valor de sumatoria: %d!!!", verificado);
    return verificado;
}

void mover_robot() {
    if (robot.ha_llegado == true) return;
    //Version Original (muy bruta sin evitar obstaculos)
    // if (robot.posicion_actual.x < robot.posicion_destino.x) {
    //     robot.posicion_actual.x++;
    // } else if (robot.posicion_actual.x > robot.posicion_destino.x) {
    //     robot.posicion_actual.x--;
    // }

    // if (robot.posicion_actual.y < robot.posicion_destino.y) {
    //     robot.posicion_actual.y++;
    // } else if (robot.posicion_actual.y > robot.posicion_destino.y) {
    //     robot.posicion_actual.y--;
    // }
    verificar_todos_adyacentes();
    //Separar en eje 'x' e 'y'    
    //Opcion 1 Priorizar un eje sobre otro (ejemplo 'x' primero, luego 'y')
    int s_casillero;
    if (robot.posicion_actual.x < robot.posicion_destino.x) {
        // robot.posicion_actual.x++; //ver original
        s_casillero = matriz[robot.posicion_actual.x+1][robot.posicion_actual.y];
        printf("\n caseillero x++ %d", s_casillero);
        if(s_casillero == 0 || s_casillero == 5){
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
            robot.posicion_actual.x++;
        }

    } else if (robot.posicion_actual.x > robot.posicion_destino.x) {
        // robot.posicion_actual.x--; 
        s_casillero = matriz[robot.posicion_actual.x-1][robot.posicion_actual.y];
        printf("\n caseillero x-- %d", s_casillero);

        if(s_casillero == 0 || s_casillero == 5){
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
            robot.posicion_actual.x--;
        }
    }
        
    if (robot.posicion_actual.y < robot.posicion_destino.y) {
        // robot.posicion_actual.x++; //ver original
        s_casillero = matriz[robot.posicion_actual.x][robot.posicion_actual.y+1];
        printf("\n caseillero x++ %d", s_casillero);
        if(s_casillero == 0 || s_casillero == 5){
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
            robot.posicion_actual.y++;
        }

    } else if (robot.posicion_actual.y > robot.posicion_destino.y) {
        // robot.posicion_actual.x--; 
        s_casillero = matriz[robot.posicion_actual.x][robot.posicion_actual.y-1];
        printf("\n caseillero x-- %d", s_casillero);

        if(s_casillero == 0|| s_casillero == 5){
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
            robot.posicion_actual.y--;
        }
    }
        //  matriz[robot.posicion_actual.x][robot.posicion_actual.y];
    //Opcion 2 50%50 de probabilidad de mover en 'x' o en 'y'


    robot.ha_llegado = robot_ha_llegado();
}

// Imprime el estado actual del robot
void imprimir_estado_robot() {
    //if (robot == -1) return;
    printf("Posición actual: (%d, %d)\n", robot.posicion_actual.x+1, robot.posicion_actual.y+1);
    printf("Destino: (%d, %d)\n", robot.posicion_destino.x+1, robot.posicion_destino.y+1);
    printf("¿Ha llegado?: %s\n", robot.ha_llegado ? "Sí" : "No");
}

