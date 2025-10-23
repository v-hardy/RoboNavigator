#include "robot.h"
#include "mapa.h"   // 👈 necesario para obtener_posicion_inicial_robot() y obtener_destino_robot()
#include <stdio.h>

// Inicializa el robot con posición y destino desde el mapa
void inicializar_robot(Robot* robot) {
    if (robot == NULL) return;

    robot->posicion_actual = obtener_posicion_inicial_robot();
    robot->destino = obtener_destino_robot();
    robot->ha_llegado = false;
}

// Verifica si el robot ha llegado a su destino
bool robot_ha_llegado(const Robot* robot) {
    return robot->posicion_actual.x == robot->destino.x &&
           robot->posicion_actual.y == robot->destino.y;
}

// Mueve el robot un paso hacia el destino
void mover_robot(Robot* robot) {
    if (robot == NULL || robot->ha_llegado) return;

    if (robot->posicion_actual.x < robot->destino.x) {
        robot->posicion_actual.x++;
    } else if (robot->posicion_actual.x > robot->destino.x) {
        robot->posicion_actual.x--;
    }

    if (robot->posicion_actual.y < robot->destino.y) {
        robot->posicion_actual.y++;
    } else if (robot->posicion_actual.y > robot->destino.y) {
        robot->posicion_actual.y--;
    }

    robot->ha_llegado = robot_ha_llegado(robot);
}

// Imprime el estado actual del robot
void imprimir_estado_robot(const Robot* robot) {
    if (robot == NULL) return;
    printf("Posición actual: (%d, %d)\n", robot->posicion_actual.x, robot->posicion_actual.y);
    printf("Destino: (%d, %d)\n", robot->destino.x, robot->destino.y);
    printf("¿Ha llegado?: %s\n", robot->ha_llegado ? "Sí" : "No");
}

