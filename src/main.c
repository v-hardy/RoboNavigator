#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#endif


#include "mapa.h"
#include "interfaz.h"
#include "robot.h" 

Robot *robot = NULL;  // Puntero a Robot, inicializado a NULL

void mostrar_menu() {
        puts(" ==============================================");
        puts("  Bienvenido al SISTEMA DE CONTROL DEL ROBOT!! ");
        puts(" ==============================================");
        puts("  Seleccione una opción:\n");
        puts("  1.- Cargar mapa actual");
        puts("  2.- Establecer coordenadas del robot");
        puts("  3.- Mostrar Mapa+Robot ASCII ");
        puts("  4.- Planificar ruta hacia el destino");
        puts("  5.- Mover robot hacia el destino");
        puts("  6.- Mostrar ruta calculada");
        puts("  7.- Reconfigurar mapa (resetear obstáculos)");
        puts("  8.- Ver estado del robot");
        puts("  0.- Salir");
        puts(" ==============================================");
}


int main() {

    // Para el encoding en Windows
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    // Inicializar la semilla del generador aleatorio
    srand(time(NULL));

    int opcion = 0;

    do {
        limpiarPantalla(); 
        mostrar_menu();
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion);
        
        limpiarPantalla();   
        mostrar_menu();

        switch(opcion) {
            case 1:
                opcion_uno(&robot);
                break;
            case 2:
                opcion_dos(&robot);
                break;
            case 3:
                if (robot == NULL) {
                    printf("⚠️  No se puede mostrar el mapa porque el robot no fue inicializado.\n");
                } else {
                    opcion_tres(&robot);
                }
                break;
            case 4:
                opcion_cuatro(&robot);
                break;
            case 5:
                puts("Opcion Numero 5!");
                break;
            case 6:
                puts("Opcion Numero 6!");
                break;
            case 7:
                puts("Opcion Numero 7!");
                break;
            case 8:
                puts("Opcion Numero 8!");
                break;
            case 0:
                puts("Saliendo del programa... ¡Hasta luego!");
                break;
            default:
                puts("Opcion invalida. Intente nuevamente.");
                break;
        }

        if (opcion != 0) {
            puts("\nPresione ENTER para continuar...");
            getchar(); getchar(); // Espera antes de refrescar pantalla
        }

    } while(opcion != 0);
    
    
    return 0;
}

