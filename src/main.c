#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "mapa.h"
#include "interfaz.h"
#include "robot.h" 

Robot robot;  // Aquí defines tu robot global

void mostrar_menu() {
    // Para el encoding en Windows
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    int opcion = 0;

    do {
        puts("\n++++++++++++++++++++++++++++++++++++");
        puts(" Bienvenido al sistema de control!! ");
        puts("++++++++++++++++++++++++++++++++++++");
        puts("  1.- Ingresar coordenadas de desplazamiento del robot");
        puts("  2.- Imprimir matriz");
        puts("  3.- Mapa ASCII con simuilacion de robot");
        puts("  4.- Salir");
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                opcion_uno(&robot);
                break;
            case 2:
                opcion_dos(&robot);
                break;
            case 3:
                opcion_tres(&robot);
                break;
            case 4:
                puts("Saliendo del programa... ¡Hasta luego!");
                break;
            default:
                puts("Opcion invalida. Intente nuevamente.");
                break;
        }
    } while(opcion != 4);
}

// Menú de opciones
// =======================================
//    SISTEMA DE NAVEGACIÓN DEL ROBOT
// =======================================
// Seleccione una opción:

// 1. Establecer destino manualmente
// 2. Mostrar mapa actual
// 3. Planificar ruta hacia el destino
// 4. Mover robot hacia el destino
// 5. Mostrar ruta calculada
// 6. Reconfigurar mapa (resetear obstáculos)
// 7. Ver estado del robot
// 8. Salir
// =======================================

int main() {

    // Inicializar la semilla del generador aleatorio
    srand(time(NULL));
    mostrar_menu();
    
    return 0;
}

