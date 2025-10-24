#include "robot.h"
#include "mapa.h"   // 👈 necesario para capturar_posiciones_iniciales_del_robot() y obtener_destino_robot()
#include <stdio.h>

// Inicializa el robot con posición y destino desde el mapa,
void inicializar_robot(Robot* robot) {
    robot->posicion_inicial = capturar_posiciones_iniciales_del_robot();
    robot->posicion_actual = robot->posicion_inicial;
    robot->posicion_destino = obtener_destino_robot();
    robot->ha_llegado = false;
}

// Verifica si el robot ha llegado a su destino
bool robot_ha_llegado(const Robot* robot) {
    return robot->posicion_actual.x == robot->posicion_destino.x &&
           robot->posicion_actual.y == robot->posicion_destino.y;
}

// Mueve el robot un paso hacia el destino
void mover_robot(Robot* robot) {
    if (robot == NULL || robot->ha_llegado) return;

    if (robot->posicion_actual.x < robot->posicion_destino.x) {
        robot->posicion_actual.x++;
    } else if (robot->posicion_actual.x > robot->posicion_destino.x) {
        robot->posicion_actual.x--;
    }

    if (robot->posicion_actual.y < robot->posicion_destino.y) {
        robot->posicion_actual.y++;
    } else if (robot->posicion_actual.y > robot->posicion_destino.y) {
        robot->posicion_actual.y--;
    }

    robot->ha_llegado = robot_ha_llegado(robot);
}

// Imprime el estado actual del robot
void imprimir_estado_robot(const Robot* robot) {
    if (robot == NULL) return;
    printf("Posición actual: (%d, %d)\n", robot->posicion_actual.x+1, robot->posicion_actual.y+1);
    printf("Destino: (%d, %d)\n", robot->posicion_destino.x+1, robot->posicion_destino.y+1);
    printf("¿Ha llegado?: %s\n", robot->ha_llegado ? "Sí" : "No");
}

