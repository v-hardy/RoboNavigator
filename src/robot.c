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

bool verificar_todos_adyacentes() {
    // printf("hola %d", matriz[10][10]);
    int arriba = matriz[robot.posicion_actual.x-1][robot.posicion_actual.y];
    int abajo = matriz[robot.posicion_actual.x+1][robot.posicion_actual.y];
    int izq = matriz[robot.posicion_actual.x][robot.posicion_actual.y-1];
    int der = matriz[robot.posicion_actual.x][robot.posicion_actual.y+1];

    printf("posicion robot X %d", robot.posicion_actual.x);
    printf(" posicion robot Y %d", robot.posicion_actual.y);
    //Esto imprime los valores que hay en la matriz
    printf("\n izq %d", izq);
    printf("\n der %d", der);
    printf("\n arriba %d", arriba);
    printf("\n abajo %d", abajo);

    if(izq == 0 && der == 0 && arriba == 0 && abajo == 0){
        puts("verdadero!");
        return true;
    }else{
        puts("FALSO!");
        return false;
    }
}

// Mueve el robot un paso hacia el destino
void mover_robot() {
    if (robot.ha_llegado == true) return;

    if (robot.posicion_actual.x < robot.posicion_destino.x) {
        robot.posicion_actual.x++;
    } else if (robot.posicion_actual.x > robot.posicion_destino.x) {
        robot.posicion_actual.x--;
    }

    if (robot.posicion_actual.y < robot.posicion_destino.y) {
        robot.posicion_actual.y++;
    } else if (robot.posicion_actual.y > robot.posicion_destino.y) {
        robot.posicion_actual.y--;
    }

    robot.ha_llegado = robot_ha_llegado();
}

// Imprime el estado actual del robot
void imprimir_estado_robot() {
    //if (robot == -1) return;
    printf("Posición actual: (%d, %d)\n", robot.posicion_actual.x+1, robot.posicion_actual.y+1);
    printf("Destino: (%d, %d)\n", robot.posicion_destino.x+1, robot.posicion_destino.y+1);
    printf("¿Ha llegado?: %s\n", robot.ha_llegado ? "Sí" : "No");
}

