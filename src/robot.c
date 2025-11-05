#include <stdio.h>
#include "robot.h"
#include "mapa.h"  

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

Posicion capturar_posiciones_iniciales_del_robot() {
    Posicion p;
    do {
        printf("  Ingrese la posicion inicial del robot (x y): ");
        if (scanf("%d %d", &p.x, &p.y) != 2) {
            fprintf(stderr, "  \033[1m\033[31m¡Error! Entrada invalida. Use numeros.\033[0m");
            while (getchar() != '\n');  // limpiar buffer
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
            puts("  \033[1m\033[31m¡Error! No puedes colocar el robot en una pared.\033[0m");
            continue;
        }

        break;  // Todo válido
    } while (1);

    matriz[p.x][p.y] = 2;  // Marco robot
    return p;
}

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

    matriz[p.x][p.y] = 5;  // Marco destino 
    return p;
}

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
        robot.ha_llegado = false;
    }
}

void reiniciar_robot() {
    robot.posicion_inicial = (Posicion){-1, -1};
    robot.posicion_actual = (Posicion){-1, -1};
    robot.posicion_destino = (Posicion){-1, -1};
    robot.ha_llegado = false;
}

bool robot_ha_llegado() {
    return robot.posicion_actual.x == robot.posicion_destino.x &&
           robot.posicion_actual.y == robot.posicion_destino.y;
}

void mover_segun_lista(int z) {
    //rastro de posiscion anterior
    matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 0;
    int x, y = 0;
    if (desencolar_lista(&x, &y)) {
        printf("  Nodo desapilado: (%d, %d)\n", x + 1, y + 1);
        //if (robot.posicion_actual.x != robot.posicion_inicial.x && robot.posicion_actual.y != robot.posicion_inicial.y) {
            robot.posicion_actual.x = x;
            robot.posicion_actual.y = y;
    //    }    
    } else {
        printf("  Pila vacía, no hay más nodos.\n");
        z++;
    }
    printf("\n  x: %d - Y: %d - iteracion %d", robot.posicion_actual.x, robot.posicion_actual.y, z);
    robot.ha_llegado = robot_ha_llegado();
}

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

void imprimir_rastro_del_robot() {
        if (robot.posicion_actual.x == -1) {
            puts("\n\033[33m\033[1m  ⚠️  El robot no ha sido inicializado.\033[0m\n");
        } else if (robot.posicion_actual.x != -1) {
            if (robot.posicion_actual.x == robot.posicion_inicial.x && robot.posicion_actual.y == robot.posicion_inicial.y) {
                puts("\n\033[32m\033[1m  ✅ El robot está listo para ser usado.\033[0m");
            }
            // agregar logica para lo recorrido
            //matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 3;
            // agregar logica para paradas intermedias
            //matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 4;

            // Marcar la posicion destino del robot con un 5
            if (robot.posicion_actual.x == robot.posicion_inicial.x && robot.posicion_actual.y == robot.posicion_inicial.y) {
                matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 5;
            }
            // Marcar la posición actual del robot con un 2
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 2;
        }
}