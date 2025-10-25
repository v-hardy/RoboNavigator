#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "mapa.h"
#include "interfaz.h"
#include "robot.h" 

// Robot *robot = NULL;  // Puntero a Robot, inicializado a NULL
Robot robot = {-1, -1, -1, false};

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

    // mostrar_menu();
    // printf("Ingrese una opcion valida: ");
    
    do {
        // limpiarPantalla(); 
        mostrar_menu();
        printf("Ingrese una opcion valida: ");
        if (opcion == 0) {
            scanf("%d", &opcion);
        }
        //limpiarPantalla();   
        //mostrar_menu();

        switch(opcion) {
            case 1:
                opcion_uno();
                break;
            case 2:
                opcion_dos();
                break;
            case 3:
                if (robot.posicion_actual.x == -1) {
                    printf("⚠️ \033[33m\033[1m No se puede mostrar el mapa porque. Robot no inicializado.\033[0m\n");
                } else {
                    opcion_tres();
                }
                break;
            case 4:
                opcion_cuatro();
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
            printf("Ingrese una opcion valida: ");
            // Usar secuencias de escape ANSI para mover el cursor hacia la línea donde empieza el mensaje de "Ingrese una opción válida: "
            // Esto depende de dónde se encuentra el mensaje exacto en tu terminal, en este caso, estamos usando una aproximación.
            printf("\033[F");  // Mueve el cursor hacia arriba (al inicio de la línea donde se mostró "Ingrese una opcion valida:")
            // Ahora, podemos borrar todo el contenido de esa línea con espacios o simplemente imprimir en blanco:
            
            scanf("%d", &opcion);
            printf("\033[K");  // Borra la línea desde el cursor hasta el final            
            

            limpiarPantalla(); 
        }

    } while(opcion != 0);
    
    
    return 0;
}

