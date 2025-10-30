#include "robot.h"
#include "mapa.h"   // 👈 necesario para capturar_posiciones_iniciales_del_robot() y obtener_robot.posicion_destino.robot()
#include <stdio.h>

extern Robot robot;

Posicion capturar_posiciones_iniciales_del_robot() {
    Posicion p;
    do {
        printf("  Ingrese la posición inicial del robot (x y): ");
        if (scanf("%d %d", &p.x, &p.y) != 2) {
            fprintf(stderr, "Error de entrada.\n");
            p.x = -1;  // Indicar un valor inválido
            p.y = -1;  // Indicar un valor inválido
            return p;  // Devolver la posición inválida
        }
        // Restamos 1 a las coordenadas ingresadas
        p.x -= 1;
        p.y -= 1;
        if (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS) {
            puts("  \033[1m\033[31m¡Error! Las coordenadas están fuera de los límites del mapa.\033[0m\n");
        }
    } while (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS);  // Validar que esté dentro del rango
    
    matriz[p.x][p.y] = 2;  // Marcar el robot en la matriz
    return p;
}

Posicion obtener_destino_robot() {
    Posicion p;
    do {
        printf("  Ingrese la posición destino del robot (x y): ");
        if (scanf("%d %d", &p.x, &p.y) != 2) {
            fprintf(stderr, "Error de entrada.\n");
            p.x = -1;  // Indicar un valor inválido
            p.y = -1;  // Indicar un valor inválido
            return p;  // Devolver la posición inválida
        }
        // Restamos 1 a las coordenadas ingresadas
        p.x -= 1;
        p.y -= 1;
        if (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS) {
            puts("  \033[1m\033[31m¡Error! Las coordenadas están fuera de los límites del mapa.\033[0m\n");
        }
    } while (p.x < 0 || p.x >= FILAS || p.y < 0 || p.y >= COLUMNAS);  // Validar que esté dentro del rango
    return p;
}

// Inicializa el robot con posición y destino
void inicializar_robot() {
    puts("\033[1m\n  RECUERDE: Para establecer coordenadas, el valor de \n  la posicion osila de 1 a 20, en X e Y.\033[0m\n");
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

Delta calcular_modulos_sentidos() {
    Delta delta;
    if (robot.posicion_destino.x >= robot.posicion_actual.x) {
        delta.sentido_abscisa = POSITIVO;
        delta.abscisa = robot.posicion_destino.x - robot.posicion_actual.x;
    } else if (robot.posicion_destino.x > robot.posicion_actual.x) {
        delta.sentido_abscisa = NEGATIVO;
        delta.abscisa = robot.posicion_actual.x - robot.posicion_destino.x;
    }

    if (robot.posicion_destino.y >= robot.posicion_actual.y) {
        delta.sentido_ordenada = POSITIVO;
        delta.abscisa = robot.posicion_destino.y - robot.posicion_actual.y;
    } else if (robot.posicion_destino.y > robot.posicion_actual.y) {
        delta.sentido_ordenada = NEGATIVO;
        delta.abscisa = robot.posicion_actual.y - robot.posicion_destino.y;
    }
    return delta;
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
    if (robot.ha_llegado == true || robot.posicion_actual.x == -1 ||robot.posicion_actual.y == -1) return;

    int obstaculos = verificar_todos_adyacentes();
    int direccion = prioridad_de_sentido();
    Desplazamiento desplazar = { 0, 0, 0, 0 };
    //LOGICA PARA VOLVER
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
    //FIN DE LOGICA PARA VOLVER

    //ELECCION INTELIGENTE SEGUN POSICION COSMO(VERDE) O WANDA(ROSA)
    
    //LAS POSICIONES COSMO ESTAN OCUPADAS? SI SOLO 1 (UNA) --> AVANZO POR COSMO X O Y
    // SEGUN EL SENTIDO DE PRIORIDAD DETERMINO CUADRANTES A ANALIZAR
    // EJEMPLO SI -SE-> CUANDO LA SUMA DE OBSTACULOS ROBOT(X,Y+1) Y  ROBOT(X+1,Y) == SE * 2 + SE div 2
    // Combinaciones con 2 obstáculos  = 2 movimientos posibles // deberia escoger el camino mas conveniente segun prioridad de sentido
    
        Delta delta = {0, 0, POSITIVO, POSITIVO};
        delta = calcular_modulos_sentidos();


    if (direccion ==  1) { //PUNTO CARDINAL N (norte)
        if ((obstaculos % 2) != 1 ) {
            printf("\nAccionar movimiento hacia arriba.");
            desplazar.arriba = 1;
            movimiento(desplazar);
        } else if (obstaculos == 3) {
            printf("\nAccionar movimiento hacia izquierda.");
            desplazar.izquierda = 8;
            movimiento(desplazar);
        } else if (obstaculos == 9) {
            printf("\nAccionar movimiento hacia derecha.");
            desplazar.derecha = 2;
            movimiento(desplazar);
        }
    } else if (direccion == 2) {
        //PUNTO INTERCARDINAL ¿hace falta un calculo del modulo aca??
        // analizo obstaculos en 1 y 2 -- 
        
        


        if (delta.abscisa >= delta.ordenada) {
            // debe x++ o x-- hasta chocar con un obstaculo
            if (delta.sentido_abscisa == POSITIVO)
                if (robot.posicion_actual.x+1 != 1){
                    printf("\nAccionar movimiento hacia abajo.");
                    desplazar.abajo = 4;
                    movimiento(desplazar);
                } 
            if (delta.sentido_abscisa == NEGATIVO) {
                if (robot.posicion_actual.x-1 != 1) {
                    printf("\nAccionar movimiento hacia arriba.");
                    desplazar.arriba = 1;
                    movimiento(desplazar);
                }
            }
        } else if (delta.abscisa < delta.ordenada) {
            // debe  y++ o y--
            if (delta.sentido_ordenada == POSITIVO) {
                if (robot.posicion_actual.y+1 != 1){
                    printf("\nAccionar movimiento hacia derecha.");
                    desplazar.derecha = 2;
                    movimiento(desplazar);
                }
            }
            if (delta.sentido_ordenada == NEGATIVO) {
                if (robot.posicion_actual.y-1 != 1){
                    printf("\nAccionar movimiento hacia izquierda.");
                    desplazar.izquierda = 8;
                    movimiento(desplazar);
                }
        
            }
        }


    } else if (direccion == 4) { //PUNTO CARDINAL E (este)
        if (obstaculos != 2 && obstaculos != 3 && obstaculos != 6 ) {
            printf("\nAccionar movimiento hacia derecha.");
            desplazar.derecha = 2;
            movimiento(desplazar);
        } else if (obstaculos == 3) {
            printf("\nAccionar movimiento hacia abajo.");
            desplazar.abajo = 4;
            movimiento(desplazar);
        } else if (obstaculos == 6) {
            printf("\nAccionar movimiento hacia arriba.");
            desplazar.arriba = 1;
            movimiento(desplazar);
        } else if (obstaculos == 2) {

            // USUARIO ELIGE MOVIMIENTO POR AHORA
            int eleccion = 0;
            printf("Ingrese hacia donde mover: ");
            if ((scanf("%d", &eleccion)) != 2) {
                fprintf(stderr, "Error de entrada.\n");
                return;  // O lo que sea necesario en caso de error
            }
            if (eleccion == 4) {
                printf("\nAccionar movimiento hacia abajo.");
                desplazar.abajo = 4;
                movimiento(desplazar);
            } else if (eleccion == 1) {
                printf("\nAccionar movimiento hacia arriba.");
                desplazar.arriba = 1;
                movimiento(desplazar);
            }

        }
    } else if (direccion == 8) {
        if (delta.abscisa >= delta.ordenada) {
            // debe x++ o x-- hasta chocar con un obstaculo
            if (delta.sentido_abscisa == POSITIVO)
                if (robot.posicion_actual.x+1 != 1){
                    printf("\nAccionar movimiento hacia abajo.");
                    desplazar.abajo = 4;
                    movimiento(desplazar);
                } 
            if (delta.sentido_abscisa == NEGATIVO) {
                if (robot.posicion_actual.x-1 != 1) {
                    printf("\nAccionar movimiento hacia arriba.");
                    desplazar.arriba = 1;
                    movimiento(desplazar);
                }
            }
        } else if (delta.abscisa < delta.ordenada) {
            // debe  y++ o y--
            if (delta.sentido_ordenada == POSITIVO) {
                if (robot.posicion_actual.y+1 != 1){
                    printf("\nAccionar movimiento hacia derecha.");
                    desplazar.derecha = 2;
                    movimiento(desplazar);
                }
            }
            if (delta.sentido_ordenada == NEGATIVO) {
                if (robot.posicion_actual.y-1 != 1) {
                    printf("\nAccionar movimiento hacia izquierda.");
                    desplazar.izquierda = 8;
                    movimiento(desplazar);
                }
        
            }
        }

    } else if (direccion == 16) { //PUNTO CARDINAL S (sur)
        if (obstaculos != 4 && obstaculos != 6 && obstaculos != 12 ) {
            printf("\nAccionar movimiento hacia abajo.");
            desplazar.abajo = 4;
            movimiento(desplazar);
        } else if (obstaculos == 6) {
            printf("\nAccionar movimiento hacia izquierda.");
            desplazar.izquierda = 8;
            movimiento(desplazar);
        } else if (obstaculos == 12) {
            printf("\nAccionar movimiento hacia derecha.");
            desplazar.derecha = 2;
            movimiento(desplazar);
        } else if (obstaculos == 4) {
            
            // USUARIO ELIGE MOVIMIENTO POR AHORA
            int eleccion = 0;
            printf("Ingrese hacia donde mover: ");
            if ((scanf("%d", &eleccion)) != 2) {
                fprintf(stderr, "Error de entrada.\n");
                return;  // O lo que sea necesario en caso de error
            }
            if (eleccion == 2) {
                printf("\nAccionar movimiento hacia derecha.");
                desplazar.derecha = 2;
                movimiento(desplazar);
            } else if (eleccion == 8) {
                printf("\nAccionar movimiento hacia izquierda.");
                desplazar.izquierda = 8;
                movimiento(desplazar);
            }

        }
    } else if (direccion == 32) {
        //PUNTO INTERCARDINAL
        ;
    } else if (direccion == 64) { //PUNTO CARDINAL O (oeste)
        if (obstaculos != 8 && obstaculos != 9 && obstaculos != 12 ) {
            printf("\nAccionar movimiento hacia derecha.");
            desplazar.derecha = 2;
            movimiento(desplazar);
        } else if (obstaculos == 9) {
            printf("\nAccionar movimiento hacia abajo.");
            desplazar.abajo = 4;
            movimiento(desplazar);
        } else if (obstaculos == 12) {
            printf("\nAccionar movimiento hacia arriba.");
            desplazar.arriba = 1;
            movimiento(desplazar);
        } if (obstaculos == 4) {
            
            // USUARIO ELIGE MOVIMIENTO POR AHORA
            int eleccion = 0;
            printf("Ingrese hacia donde mover: ");
            if ((scanf("%d", &eleccion)) != 2) {
                fprintf(stderr, "Error de entrada.\n");
                return;  // O lo que sea necesario en caso de error
            }
            if (eleccion == 4) {
                printf("\nAccionar movimiento hacia abajo.");
                desplazar.abajo = 4;
                movimiento(desplazar);
            } else if (eleccion == 1) {
                printf("\nAccionar movimiento hacia arriba.");
                desplazar.arriba = 1;
                movimiento(desplazar);
            }

        }
    } else if (direccion == 128) {
        //PUNTO INTERCARDINAL
        ;
    }

    if (obstaculos == 3) {
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
              
        //calcular_modulos_sentidos();

        
    }

        if (delta.abscisa >= delta.ordenada) {
            // debe x++ o x-- hasta chocar con un obstaculo
            if (delta.sentido_abscisa == POSITIVO) {

                if (robot.posicion_actual.x+1 != 1){
                    printf("\nAccionar movimiento hacia abajo.");
                    desplazar.abajo = 4;
                    movimiento(desplazar);
                } 
            }
            if (delta.sentido_abscisa == NEGATIVO) {

                if (robot.posicion_actual.x-1 != 1) {
                    printf("\nAccionar movimiento hacia arriba.");
                    desplazar.arriba = 1;
                    movimiento(desplazar);
                }
            }
        } else if (delta.abscisa < delta.ordenada) {
            // debe  y++ o y--
            if (delta.sentido_ordenada == POSITIVO) {
                if (robot.posicion_actual.y+1 != 1) {
                    printf("\nAccionar movimiento hacia derecha.");
                    desplazar.derecha = 2;
                    movimiento(desplazar);
                }
            }
            if (delta.sentido_ordenada == NEGATIVO) {
                if (robot.posicion_actual.y-1 != 1) {
                    printf("\nAccionar movimiento hacia izquierda.");
                    desplazar.izquierda = 8;
                    movimiento(desplazar);
                }
        
            }
        }

    // else if (obstaculos == 3) {
    //     printf("\nPuede moverse hacia abajo o hacia la izquierda.");

    // } else if (obstaculos == 5) {
    //     printf("\nPuede moverse hacia la derecha o hacia la izquierda.");

    // } else if (obstaculos == 6) {
    //     printf("\nPuede moverse hacia arriba o hacia abajo.");

    // } else if (obstaculos == 9) {
    //     printf("\nPuede moverse hacia la derecha o hacia abajo.");

    // } else if (obstaculos == 10) {
    //     printf("\nPuede moverse hacia arriba o hacia la izquierda.");

    // } else if (obstaculos == 12) {
    //     printf("\nPuede moverse hacia arriba o hacia la derecha.");

    // } 
    // // Combinaciones con 1 obstáculo =  = 3 movimientos posibles
    // else if (obstaculos == 1) {
    //     printf("\nPuede moverse hacia abajo, hacia la derecha o hacia la izquierda.");
    // } else if (obstaculos == 2) {
    //     printf("\nPuede moverse hacia arriba, hacia abajo o hacia la izquierda.");
    // } else if (obstaculos == 4) {
    //     printf("\nPuede moverse hacia arriba, hacia la derecha o hacia la izquierda.");
    // } else if (obstaculos == 8) {
    //     printf("\nPuede moverse hacia arriba, hacia la derecha o hacia abajo.");
    // } 
    // // Caso sin obstáculos = 4 movimientos posibles
    // else {
    //     printf("\nNo hay obstáculos, puede moverse en todas las direcciones.");
    // }
    //ELECCION INTELIGENTE SEGUN POSICION COSMO(VERDE) O WANDA(ROSA)

    robot.ha_llegado = robot_ha_llegado();
}

// Imprime el estado actual del robot
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
            matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 5;
            // Marcar la posición actual del robot con un 2
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 2;
        }
}