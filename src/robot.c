#include "robot.h"
#include "mapa.h"   
#include <stdio.h>

extern Robot robot;

// Captura posición inicial
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

// Captura posición destino 
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

// Inicializa el robot con posición y destino
void inicializar_robot() {
    puts("\033[1m\n  RECUERDE: Para establecer coordenadas, el valor de \n  la posicion osila de 1 a 20, en X e Y.\033[0m\n");
    robot.posicion_inicial = capturar_posiciones_iniciales_del_robot();
    robot.posicion_actual = robot.posicion_inicial;
    robot.posicion_destino = capturar_posiciones_destino_del_robot();
    robot.ha_llegado = false;
}

void reiniciar_robot() {
    robot.posicion_inicial = (Posicion){-1, -1};
    robot.posicion_actual = (Posicion){-1, -1};
    robot.posicion_destino = (Posicion){-1, -1};
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
    if (robot.posicion_destino.x > robot.posicion_actual.x) {
        delta.sentido_abscisa = POSITIVO;
        delta.abscisa = robot.posicion_destino.x - robot.posicion_actual.x;
    } else if (robot.posicion_destino.x == robot.posicion_actual.x) {
        delta.sentido_abscisa = CERO;
        delta.abscisa = 0; // deberia dar 0
    } else if (robot.posicion_destino.x < robot.posicion_actual.x) {
        delta.sentido_abscisa = NEGATIVO;
        delta.abscisa = robot.posicion_actual.x - robot.posicion_destino.x;
    } 

    if (robot.posicion_destino.y > robot.posicion_actual.y) {
        delta.sentido_ordenada = POSITIVO;
        delta.ordenada = robot.posicion_destino.y - robot.posicion_actual.y;
    } else if (robot.posicion_destino.y == robot.posicion_actual.y) {
        delta.sentido_ordenada = CERO;
        delta.ordenada = 0; // deberia dar 0
    } else if (robot.posicion_destino.y < robot.posicion_actual.y) {
        delta.sentido_ordenada = NEGATIVO;
        delta.ordenada = robot.posicion_actual.y - robot.posicion_destino.y;
    }
    return delta;
}

void movimiento(Desplazamiento desplazar){
    if (robot.ha_llegado == true) return;  

    if (desplazar.arriba == 1 && desplazar.derecha == 0 && desplazar.abajo == 0 && desplazar.izquierda == 0) {
        // Acción cuando desplazar es {1, 0, 0, 0}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("\n  🤖 El robot se movio hacia arriba.");
        robot.posicion_actual.x--;
    } else if (desplazar.arriba == 0 && desplazar.derecha == 2 && desplazar.abajo == 0 && desplazar.izquierda == 0) {
        // Acción cuando desplazar es {0, 2, 0, 0}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("\n  🤖 El robot se movio  hacia la derecha.");
        robot.posicion_actual.y++;
    } else if (desplazar.arriba == 0 && desplazar.derecha == 0 && desplazar.abajo == 4 && desplazar.izquierda == 0) {
        // Acción cuando desplazar es {0, 0, 4, 0}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("\n  🤖 El robot se movio  hacia la abajo.");
        robot.posicion_actual.x++;
    } else if (desplazar.arriba == 0 && desplazar.derecha == 0 && desplazar.abajo == 0 && desplazar.izquierda == 8) {
        // Acción cuando desplazar es {0, 0, 0, 8}
        matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 3;
        printf("\n  🤖 El robot se movio hacia la izquierda.");
        robot.posicion_actual.y--;
    }
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
        desplazar.derecha = 2;
        movimiento(desplazar);
    }               // CAMINOS SIN SALIDA --> REGISTRAR EN LISTA DE CAMINOS SIN SALIDA
    //FIN DE LOGICA PARA VOLVER

    //ELECCION INTELIGENTE SEGUN POSICION COSMO(VERDE) O WANDA(ROSA)

    Delta delta = {0, 0, POSITIVO, POSITIVO};
    delta = calcular_modulos_sentidos();

    printf("\n Modulos calculados: %d, %d; Sentidos: %d, %d \n", delta.abscisa, delta.ordenada, delta.sentido_abscisa, delta.sentido_ordenada);
    if ( 1 == 0 ) {
        ;

    } else {
    // SE MUEVE POR EJE X POR SE MAYOR QUE VALOR DELTA.Y
        if (delta.abscisa > delta.ordenada) {
            // debe x++ o x-- hasta chocar con un obstaculo
            if (delta.sentido_abscisa == POSITIVO)
                if (matriz[robot.posicion_actual.x+1][robot.posicion_actual.y] != 1){
                    printf("\nAccionar movimiento hacia abajo.");
                    desplazar.abajo = 4;
                    movimiento(desplazar);
                } else{

                    if (obstaculos == 6) {
                        printf("\nAccionar movimiento hacia izquierda.");
                        desplazar.izquierda = 8;
                        movimiento(desplazar);
                    } else if (obstaculos == 12) {
                        printf("\nAccionar movimiento hacia derecha.");
                        desplazar.derecha = 2;
                        movimiento(desplazar);
                    } else if (obstaculos == 4 || obstaculos == 5) {
                        printf("\nAccionar movimiento hacia derecha PREDEFINIDO.");
                        desplazar.derecha = 2;
                        movimiento(desplazar);
                    }

                }
            //PRUEBA
            if (delta.sentido_abscisa == CERO) {
                
                if (matriz[robot.posicion_actual.x][robot.posicion_actual.y+1] != 1) {
                    printf("\nAccionar movimiento hacia derecha.");
                    desplazar.derecha = 2;
                    movimiento(desplazar);
                
                } else {
    //PRUEBA
                    if (obstaculos == 3) {
                        printf("\nAccionar movimiento hacia izquierda.");
                        desplazar.izquierda = 8;
                        movimiento(desplazar);
                    } else if (obstaculos == 9) {
                        printf("\nAccionar movimiento hacia derecha.");
                        desplazar.derecha = 2;
                        movimiento(desplazar);
                    } else if (obstaculos == 3) {
                        printf("\nAccionar movimiento hacia izquierda PREDEFINIDO.");
                        desplazar.izquierda = 8;
                        movimiento(desplazar);
                    } 

                }

            }


            if (delta.sentido_abscisa == NEGATIVO) {
                if (matriz[robot.posicion_actual.x-1][robot.posicion_actual.y] != 1) {
                    printf("\nAccionar movimiento hacia arriba.");
                    desplazar.arriba = 1;
                    movimiento(desplazar);
                } else {

                    if (obstaculos == 3) {
                        printf("\nAccionar movimiento hacia izquierda.");
                        desplazar.izquierda = 8;
                        movimiento(desplazar);
                    } else if (obstaculos == 9) {
                        printf("\nAccionar movimiento hacia derecha.");
                        desplazar.derecha = 2;
                        movimiento(desplazar);
                    } else if (obstaculos == 3) {
                        printf("\nAccionar movimiento hacia izquierda PREDEFINIDO.");
                        desplazar.izquierda = 8;
                        movimiento(desplazar);
                    } 

                }
            }
        
    // SE MUEVE POR EJE Y POR SE MAYOR QUE VALOR DELTA.X
        } else if (delta.abscisa <= delta.ordenada) {
            // debe  y++ o y--
            if (delta.sentido_ordenada == POSITIVO) {
                
                if (matriz[robot.posicion_actual.x][robot.posicion_actual.y+1] != 1){
                    printf("\nAccionar movimiento hacia derecha.");
                    desplazar.derecha = 2;
                    movimiento(desplazar);
                } else {

                    if (obstaculos == 3) {
                        printf("\nAccionar movimiento hacia abajo.");
                        desplazar.abajo = 4;
                        movimiento(desplazar);
                    } else if (obstaculos == 6) {
                        printf("\nAccionar movimiento hacia arriba.");
                        desplazar.arriba = 1;
                        movimiento(desplazar);
                    } else if (obstaculos == 2 || obstaculos == 10 ) {

                        if (delta.sentido_abscisa == POSITIVO) {
                            printf("\nAccionar movimiento hacia abajo.");
                            desplazar.abajo = 4;
                            movimiento(desplazar);
                        } else if (delta.sentido_abscisa == NEGATIVO) {
                            printf("\nAccionar movimiento hacia arriba.");
                            desplazar.arriba = 1;
                            movimiento(desplazar);
                        } else if (delta.sentido_abscisa == CERO) {
                            if (matriz[robot.posicion_actual.x-1][robot.posicion_actual.y] == 3){
                                printf("\nAccionar movimiento hacia abajo.");
                                desplazar.abajo = 4;
                                movimiento(desplazar);
                            } else if (matriz[robot.posicion_actual.x+1][robot.posicion_actual.y] == 3){
                                printf("\nAccionar movimiento hacia arriba.");
                                desplazar.arriba = 1;
                                movimiento(desplazar);
                            }
                        }

                    }
                }
            }
            
            if (delta.sentido_ordenada == CERO) { // NO TOMA CERO PORQUE LA  FUNCION QUE CALCULA EL DELTA NO ASIGNA CERO, HABRIA QUE TOMAR EL VALOR QUE SI QUEDA EN 0
            
                if(obstaculos == 0){
                    printf("\nAccionar movimiento hacia derecha.");
                    desplazar.derecha = 2;
                    movimiento(desplazar);
                }// ESTO HABRIA QUE AGREGAR A LOS OTROS CASOS

            }
            
            if (delta.sentido_ordenada == NEGATIVO) {
                if (matriz[robot.posicion_actual.x][robot.posicion_actual.y-1] != 1){
                    printf("\nAccionar movimiento hacia izquierda.");
                    desplazar.izquierda = 8;
                    movimiento(desplazar);
                } else {

                    if (obstaculos == 9) {
                        printf("\nAccionar movimiento hacia abajo.");
                        desplazar.abajo = 4;
                        movimiento(desplazar);
                    } else if (obstaculos == 12) {
                        printf("\nAccionar movimiento hacia arriba.");
                        desplazar.arriba = 1;
                        movimiento(desplazar);
                    } if (obstaculos == 8) {
                        printf("\nAccionar movimiento hacia arriba PREDEFINIDO.");
                        desplazar.arriba = 1;
                        movimiento(desplazar);
                    }

                }       
            }

        
        } 
    }

    printf("  \nDesplazamiendo: %d %d %d %d", desplazar.arriba, desplazar.derecha, desplazar.abajo, desplazar.izquierda);
    // SE MUEVE POR EJE X POR SI VALOR DELTA.Y ES CERO 

    // SE MUEVE POR EJE Y POR SI VALOR DELTA.X ES CERO 

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
    }

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
            if (robot.posicion_actual.x == robot.posicion_inicial.x && robot.posicion_actual.y == robot.posicion_inicial.y) {
                matriz[robot.posicion_destino.x][robot.posicion_destino.y] = 5;
            }
            // Marcar la posición actual del robot con un 2
            matriz[robot.posicion_actual.x][robot.posicion_actual.y] = 2;
        }
}