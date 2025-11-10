#include "stdio.h"
#include "stdlib.h"
#include "mapa.h"
#include "robot.h"
#include "interfaz.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

extern int matriz[FILAS][COLUMNAS];
extern Robot robot;

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// Ve que sistema operativo se esta utilizando para limpiar la pantalla con la funcion correspondiente

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        int _ = system("clear");
        (void)_;
    #endif
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 1.- Cargar mapa

void opcion_uno() {

    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      seleccionar_mapa();
      imprimir_mapa_ascii();
      
    } else {
    puts("\n\033[1m  🗺️  Ya hay un mapa cargado. ¿Desea reemplazarlo?​\033[0m");
        seleccionar_mapa();
  }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

//  2.- Establecer coordenadas del robot

void opcion_dos() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
      puts("\n\033[33m\033[1m  ⚠️  No se puede establecer coordenadas debe cargar el mapa antes.\033[0m");
    } else {
      imprimir_mapa_ascii();
      inicializar_robot();
      imprimir_estado_robot();
      imprimir_rastro_del_robot();
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 3.- Mostrar Mapa+Robot ASCII

void opcion_tres() {
    bool vacia = matriz_vacia(matriz);
    if (vacia) {
        puts("\n\033[33m\033[1m  ⚠️  Mapa no cargado. 🤖 Robot no inicializado.\033[0m");
    } else if (robot.posicion_actual.x == -1) {
      puts("\n\033[33m\033[1m  ⚠️  Robot no inicializado.\033[0m");
      imprimir_mapa_ascii();
    } else { 
      imprimir_rastro_del_robot();
      imprimir_mapa_ascii();
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 4.- Agregar Obstaculo

void opcion_cuatro(){

    // 1. Validar mapa
    if (matriz_vacia(matriz)) {
        printf("\n  \033[33m\033[1mAdvertencia: Debe cargar un mapa primero.\033[0m\n\n");
        return;
    }

    int fila, columna;
    int resultado;

    imprimir_mapa_ascii();

    printf("\n  Ingrese coordenadas del obstáculo (fila columna, 1-20): ");

    // Leer entrada
    if (scanf("%d %d", &fila, &columna) != 2) {
   
        limpiarPantalla();
        printf("\n  \033[1m\033[31mError: Formato inválido. Use: fila columna\033[0m\n\n");
        return;
    }

    resultado = agregar_obstaculo(fila, columna);

    limpiarPantalla();

    if (resultado == 0) {
        printf("\n  \033[32m\033[1mÉxito: Obstáculo agregado en (%d, %d)\033[0m\n", fila, columna);
        imprimir_mapa_ascii();

    } else {
        imprimir_mapa_ascii();
        // Errores
        if (resultado == -1) {
            printf("\033[1m\033[31m  Error: Coordenadas fuera de rango o ya hay obstáculo.\033[0m\n\n");
        } else if (resultado == -2) {
            printf("\033[1m\033[31m  Error: No puedes colocar un obstáculo sobre el robot.\033[0m\n\n");
        } else if (resultado == 1) {
            printf("\033[1m\033[31m  Error: No puedes colocar un obstáculo en el destino.\033[0m\n\n");
        } else {
            printf("\033[1m\033[31m  Error: Casilla ocupada (valor: %d).\033[0m\n\n", resultado);
        }
        printf("  Mapa sin cambios:\n");
    }
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 5.- Mover robot hacia el destino

void opcion_cinco(){


    // 1. Validar que haya un mapa cargado
    if (matriz_vacia(matriz)) {
        puts("\n\033[33m\033[1m  ¡Error! Debe cargar un mapa antes de mover el robot.\033[0m");
        puts("\n  Use la opción 1 para cargar un mapa.\n");
        return;
    }

    // 2. Validar que el robot esté inicializado
    if (!robot_esta_inicializado()) {
        puts("\n\033[33m\033[1m  ¡Error! Debe inicializar el robot con coordenadas.\033[0m");
        puts("\n  Use la opción 2 para establecer posición inicial y destinos.\n");
        return;
    }

    automatizar_robot();

    if (robot_ha_llegado()) { 
        if (robot.posicion_actual.x == robot.posicion_destinoB.x &&
            robot.posicion_actual.y == robot.posicion_destinoB.y) {
            
            printf("\n\033[32m\033[1m  Llegó al destino B. Ingrese nuevos destinos.\033[0m\n");

        } else {
            printf("\n  \033[36m\033[1mEl Robot llegó al punto A. Ahora va al B.\033[0m\n");
            intercambiar_destinos(); 
            automatizar_robot(); 
        }
    }

}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 6.- Reiniciar mapa COMPLETAMENTE (robot, mapa, todo)
void opcion_seis() {
    limpiarPantalla();
    puts("\n\033[1m\033[33m  Reiniciando todo el sistema...\033[0m\n");

    // 1. Reiniciar robot
    reiniciar_robot();

    // 2. Limpiar cola de camino
    while (!lista_vacia()) {
        int x, y;
        desencolar_lista(&x, &y);
    }
    PRIM = ULT = NULL;

    // 3. Recargar el último mapa usado
    if (ultimo_mapa_seleccionado == 0) {
        puts("  No se ha cargado ningún mapa aún.");
        puts("  Debe seleccionar un mapa desde la opción 1.\n");
    } else {
        switch (ultimo_mapa_seleccionado) {
            case 1:
                cargar_matriz(mapa1);
                break;
            case 2:
                cargar_matriz(mapa2);
                break;
            case 3:
                cargar_matriz(mapa3);
                break;
        }
    }

    // 4. Borrar rastros (por si quedó algo)
    borrar_rastros_del_mapa();

    // 5. Mostrar resultado
    puts("\n\033[1m\033[32m  Sistema reiniciado correctamente.\033[0m");
    if (ultimo_mapa_seleccionado != 0) {
        printf("  Se ha restaurado el Mapa %d.\n", ultimo_mapa_seleccionado);
    }

    imprimir_mapa_ascii();

}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// 7.- Ver estado de la matriz

void opcion_siete(){
    puts("\n  \033[1m\033[4mEstado actual del mapa y robot:\033[0m");
    imprimir_estado_robot();
    imprimir_rastro_del_robot();
    imprimir_matriz();
}