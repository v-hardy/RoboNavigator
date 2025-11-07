#include <stdio.h>
#include "robot.h"
#include "mapa.h"
#include "posicion.h"  
#include "windows.h"
#include "lista.h"

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

// Función segura para limpiar el buffer
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Posicion capturar_posiciones_iniciales_del_robot() {
    Posicion p;
    do {
        printf("  Ingrese la posicion inicial del robot (x y): ");
        
        if (scanf("%d %d", &p.x, &p.y) != 2) {
            fprintf(stderr, "  \033[1m\033[31m¡Error! Entrada invalida. Use numeros.\033[0m\n");
            limpiar_buffer();  // ← ¡AQUÍ ESTÁ LA CORRECCIÓN!
            continue;
        }

        p.x -= 1;  // x = fila (0-based)
        p.y -= 1;  // y = columna (0-based)

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

    matriz[p.x][p.y] = -2;  // ← ¡CORREGIDO: ahora es -2, no 2!
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

    matriz[p.x][p.y] = 1;  // Marco destino 
    return p;
}

void inicializar_robot() {
    puts("\033[1m\n  RECUERDE: Para establecer coordenadas, el valor de \n  la posicion osila de 1 a 20, en X e Y.\033[0m\n");
    if (robot.ha_llegado == true) {
        robot.posicion_inicial = robot.posicion_actual;    
        robot.posicion_destino = capturar_posiciones_destino_del_robot();
        robot.ha_llegado = false;
    } else {
        //robot.circuito = NULL;
        //int opc; 

        robot.posicion_inicial = capturar_posiciones_iniciales_del_robot();
        robot.posicion_actual = robot.posicion_inicial;

        //Posicion p = robot.posicion_inicial;
        //encolar_circular(&robot.circuito, p.x, p.y);

        robot.posicion_destino = capturar_posiciones_destino_del_robot();
        robot.posicion_destinoB = capturar_posiciones_destino_del_robot();
        /*
        while(true){

            printf("  ¿Desea agregar un destino mas?...\n");
            printf("  1: SI...\n");
            printf("  2: NO...\n");
      
            if (scanf("%d", &opc) != -1 && (opc < 1 || opc > 2)) {
                fprintf(stderr, "  \033[1m\033[31m¡Error! Entrada invalida. Use numeros.\033[0m\n");
                while (getchar() != '\n');
                continue;
            }
            if (opc < 1 || opc > 2) {
                printf("Error: Opcion invalida. Debe ser 1 o 2.\n");
            }

           if (opc == 2) break;

            // opc == 1
            Posicion p = capturar_posiciones_destino_del_robot();
            encolar_circular(&robot.circuito, p.x, p.y);
            printf("  Destino agregado: (%d, %d)\n", p.x, p.y);
        }
      
        */
        robot.ha_llegado = false;
    }
    //printf("\n");
    //mostrar_circular(&robot.circuito);
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

        // Marcar la posicion destino del robot con un 1
        if (robot.posicion_actual.x == robot.posicion_inicial.x && robot.posicion_actual.y == robot.posicion_inicial.y) {
            matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 1;
        }
        // Marcar la posición actual del robot con un -2
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = -2;
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

void mover_robot(){

    int row, col;
    while (desencolar_lista(&row, &col)){

        robot.posicion_actual.x = row;
        robot.posicion_actual.y = col;
        borrar_rastros_del_mapa();
        Sleep(800);
        system("cls");
        imprimir_rastro_del_robot();
        imprimir_mapa_ascii();
        robot.ha_llegado = robot_ha_llegado();
    }

}