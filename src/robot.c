#include "robot.h"
#include "mapa.h"   // 👈 necesario para capturar_posiciones_iniciales_del_robot() y obtener_robot.posicion_destino.robot()
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

    printf("posicion robot X %d", robot.posicion_actual.x+1);
    printf(" posicion robot Y %d", robot.posicion_actual.y+1);
    //Esto imprime el valor que representa a los obstaculos que hay en la matriz junto al robot
    if (verificado == 1) {
        printf("\n Habia obstaculo hacia arriba.");
    } else if (verificado == 2) {
        printf("\n Habia obstaculo hacia la derecha.");
    } else if (verificado == 3) {
        printf("\n Habia obstaculo hacia arriba y hacia la derecha.");
    } else if (verificado == 4) {
        printf("\n Habia obstaculo hacia abajo.");
    } else if (verificado == 5) {
        printf("\n Habia obstaculo hacia arriba y hacia abajo.");
    } else if (verificado == 6) {
        printf("\n Habia obstaculo hacia la derecha y hacia abajo.");
    } else if (verificado == 7) {
        printf("\n Habia obstaculo hacia arriba, derecha y abajo.");
    } else if (verificado == 8) {
        printf("\n Habia obstaculo hacia la izquierda.");
    } else if (verificado == 9) {
        printf("\n Habia obstaculo hacia arriba y hacia la izquierda.");
    } else if (verificado == 10) {
        printf("\n Habia obstaculo hacia la derecha y hacia la izquierda.");
    } else if (verificado == 11) {
        printf("\n Habia obstaculo hacia arriba, derecha y hacia la izquierda.");
    } else if (verificado == 12) {
        printf("\n Habia obstaculo hacia abajo y hacia la izquierda.");
    } else if (verificado == 13) {
        printf("\n Habia obstaculo hacia arriba, abajo y hacia la izquierda.");
    } else if (verificado == 14) {
        printf("\n Habia obstaculo hacia la derecha, abajo y hacia la izquierda.");
    } else if (verificado == 15) {
        printf("\n Habia obstaculo hacia arriba, derecha, abajo y hacia la izquierda.");
    } else {
        printf("\n No habia obstáculos.");
    }

    printf("\n Valor de sumatoria: %d!!!", verificado);
    return verificado;
}

int prioridad_de_sentido() {
    int prioridad = 0;
    if (robot.posicion_actual.x > robot.posicion_destino.x && robot.posicion_actual.y < robot.posicion_destino.y) {
        // sentido hacia 2: NE
        prioridad = 2;
    }
    else if (robot.posicion_actual.x > robot.posicion_destino.x && robot.posicion_actual.y == robot.posicion_destino.y) {
        // sentido hacia 1: N
        prioridad = 1;
    }
    else if (robot.posicion_actual.x > robot.posicion_destino.x && robot.posicion_actual.y > robot.posicion_destino.y) {
        // sentido hacia 128: NO
        prioridad = 128;
    }
    else if (robot.posicion_actual.x == robot.posicion_destino.x && robot.posicion_actual.y < robot.posicion_destino.y) {
        // sentido hacia 4: E
        prioridad = 4;
    }
    else if (robot.posicion_actual.x == robot.posicion_destino.x && robot.posicion_actual.y == robot.posicion_destino.y) {
        // ESTA EN EL DESTINO EL WUACHIN
        // si actual = destino --> el bicho esta en el destino no se debe mover
        prioridad = 0;
    }
    else if (robot.posicion_actual.x == robot.posicion_destino.x && robot.posicion_actual.y > robot.posicion_destino.y) {
        // sentido hacia 64: O
        prioridad = 64;
    }
    else if (robot.posicion_actual.x < robot.posicion_destino.x && robot.posicion_actual.y < robot.posicion_destino.y) {
        // sentido hacia 8: SE
        prioridad = 8;
    }
    else if (robot.posicion_actual.x < robot.posicion_destino.x && robot.posicion_actual.y == robot.posicion_destino.y) {
        // sentido hacia 16: S
        prioridad = 16;
    }
    else if (robot.posicion_actual.x < robot.posicion_destino.x && robot.posicion_actual.y > robot.posicion_destino.y) {
        // sentido hacia 32: SO
        prioridad = 32;
    }
    else {
        puts("\n ACA NO DEBERIA LLEGAR NUNCA");
    }

    return prioridad;
}

void movimiento(Desplazamiento desplazar){
    if (robot.ha_llegado == true) return;  

    if (desplazar.arriba == 1 && desplazar.derecha == 0 && desplazar.abajo == 0 && desplazar.izquierda == 0) {
        // Acción cuando desplazar es {1, 0, 0, 0}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("Movimiento hacia arriba.\n");
        robot.posicion_actual.x--;
    } else if (desplazar.arriba == 0 && desplazar.derecha == 2 && desplazar.abajo == 0 && desplazar.izquierda == 0) {
        // Acción cuando desplazar es {0, 2, 0, 0}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("Movimiento hacia la derecha.\n");
        robot.posicion_actual.y++;
    } else if (desplazar.arriba == 0 && desplazar.derecha == 0 && desplazar.abajo == 4 && desplazar.izquierda == 0) {
        // Acción cuando desplazar es {0, 0, 4, 0}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("Movimiento hacia la abajo.\n");
        robot.posicion_actual.x++;
    } else if (desplazar.arriba == 0 && desplazar.derecha == 0 && desplazar.abajo == 0 && desplazar.izquierda == 8) {
        // Acción cuando desplazar es {0, 0, 0, 8}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("Movimiento hacia la izquierda.\n");
        robot.posicion_actual.x--;
    }
}

void mover_robot() {
    if (robot.ha_llegado == true) return;

    int obstaculos = verificar_todos_adyacentes();
    int direccion = prioridad_de_sentido();
    Desplazamiento desplazar = { 0, 0, 0, 0 };

                    // CAMINOS SIN SALIDA --> REGISTRAR EN LISTA DE CAMINOS SIN SALIDA
    // Combinaciones con 3 obstáculos = 1 movimiento posible
    if (obstaculos == 14) {
        printf("\nPuede VOLVER hacia arriba.");
        desplazar.arriba = 1;
        movimiento(desplazar);
    } else if (obstaculos == 7) {
        printf("\nPuede VOLVER hacia la izquieda.");
        desplazar.izquierda = 8;
        movimiento(desplazar);
    } else if (obstaculos == 11) {
        printf("\nPuede VOLVER hacia abajo.");
        desplazar.abajo = 4;
        movimiento(desplazar);
    } else if (obstaculos == 13) {
        printf("\nPuede VOLVER hacia derecha.");
        desplazar.izquierda = 2;
        movimiento(desplazar);
    }               // CAMINOS SIN SALIDA --> REGISTRAR EN LISTA DE CAMINOS SIN SALIDA

    // Combinaciones con 2 obstáculos  = 2 movimientos posibles // deberia escoger el camino mas conveniente segun prioridad de sentido
    else if (obstaculos == 3) {
        printf("\nPuede moverse hacia abajo o hacia la izquierda.");

    } else if (obstaculos == 5) {
        printf("\nPuede moverse hacia la derecha o hacia la izquierda.");

    } else if (obstaculos == 6) {
        printf("\nPuede moverse hacia arriba o hacia abajo.");

    } else if (obstaculos == 9) {
        printf("\nPuede moverse hacia la derecha o hacia abajo.");

    } else if (obstaculos == 10) {
        printf("\nPuede moverse hacia arriba o hacia la izquierda.");

    } else if (obstaculos == 12) {
        printf("\nPuede moverse hacia arriba o hacia la derecha.");

    } 
    // Combinaciones con 1 obstáculo =  = 3 movimientos posibles
    else if (obstaculos == 1) {
        printf("\nPuede moverse hacia abajo, hacia la derecha o hacia la izquierda.");
    } else if (obstaculos == 2) {
        printf("\nPuede moverse hacia arriba, hacia abajo o hacia la izquierda.");
    } else if (obstaculos == 4) {
        printf("\nPuede moverse hacia arriba, hacia la derecha o hacia la izquierda.");
    } else if (obstaculos == 8) {
        printf("\nPuede moverse hacia arriba, hacia la derecha o hacia abajo.");
    } 
    // Caso sin obstáculos = 4 movimientos posibles
    else {
        printf("\nNo hay obstáculos, puede moverse en todas las direcciones.");
    }

    // //Separar en eje 'x' e 'y'    
    // //Opcion 1 Priorizar un eje sobre otro (ejemplo 'x' primero, luego 'y')
    // int s_casillero;
    // if (robot.posicion_actual.x < robot.posicion_destino.x) {
    //     // robot.posicion_actual.x++; //ver original
    //     s_casillero = matriz[robot.posicion_actual.x+1][robot.posicion_actual.y];
    //     printf("\n caseillero x++ %d", s_casillero);
    //     if(s_casillero == 0 || s_casillero == 5){
    //         matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
    //         robot.posicion_actual.x++;
    //     }

    // } else if (robot.posicion_actual.x > robot.posicion_destino.x) {
    //     // robot.posicion_actual.x--; 
    //     s_casillero = matriz[robot.posicion_actual.x-1][robot.posicion_actual.y];
    //     printf("\n caseillero x-- %d", s_casillero);

    //     if(s_casillero == 0 || s_casillero == 5){
    //         matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
    //         robot.posicion_actual.x--;
    //     }
    // }
        
    // if (robot.posicion_actual.y < robot.posicion_destino.y) {
    //     // robot.posicion_actual.x++; //ver original
    //     s_casillero = matriz[robot.posicion_actual.x][robot.posicion_actual.y+1];
    //     printf("\n caseillero x++ %d", s_casillero);
    //     if(s_casillero == 0 || s_casillero == 5){
    //         matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
    //         robot.posicion_actual.y++;
    //     }

    // } else if (robot.posicion_actual.y > robot.posicion_destino.y) {
    //     // robot.posicion_actual.x--; 
    //     s_casillero = matriz[robot.posicion_actual.x][robot.posicion_actual.y-1];
    //     printf("\n caseillero x-- %d", s_casillero);

    //     if(s_casillero == 0|| s_casillero == 5){
    //         matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3; //dejar rastro
    //         robot.posicion_actual.y--;
    //     }
    // }
    //     //  matriz[robot.posicion_actual.x][robot.posicion_actual.y];
    // //Opcion 2 50%50 de probabilidad de mover en 'x' o en 'y'


    robot.ha_llegado = robot_ha_llegado();
}

// Imprime el estado actual del robot
void imprimir_estado_robot() {
    //if (robot == -1) return;
    printf("Posición actual: (%d, %d)\n", robot.posicion_actual.x+1, robot.posicion_actual.y+1);
    printf("Destino: (%d, %d)\n", robot.posicion_destino.x+1, robot.posicion_destino.y+1);
    printf("¿Ha llegado?: %s\n", robot.ha_llegado ? "Sí" : "No");
}

