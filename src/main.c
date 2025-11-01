#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "mapa.h"
#include "interfaz.h"
#include "robot.h" 

Robot robot = {{-1,-1},{-1,-1},{-1,-1}, false}; // La primera {} es para la estructura completa, la segunda para los miembros. SIEMPRE ASI

void mostrar_menu() {
        puts(" ==============================================");
        puts("  Bienvenido al SISTEMA DE CONTROL DEL ROBOT!! ");
        puts(" ==============================================");
        puts("  Seleccione una opción:\n");
        puts("  1.- Cargar mapa actual");
        puts("  2.- Establecer coordenadas del robot");
        puts("  3.- Mostrar Mapa+Robot ASCII ");
        puts("  4.- Planificar ruta más corta hacia el destino");
        puts("  5.- Mover robot hacia el destino");
        puts("  6.- Mostrar ruta calculada");
        puts("  7.- Reconfigurar mapa (resetear obstáculos)");
        puts("  8.- Ver estado del robot");
        puts("  0.- Salir");
        puts(" ==============================================");
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ingresar_y_validar_opcion() {
    int opcion;
    int valido = 0;

    do {
        printf(" Ingrese una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            // Entrada inválida
            limpiarBuffer();  // Limpia el buffer
            printf("\033[1A"); // Sube una línea
            printf("\033[K");  // Borra la línea
            printf("Ingrese una opcion valida: ");
        } else {
            limpiarBuffer();  // Limpia el \n restante
            // Validar rango de opcion aquí
            if (opcion >= 0 && opcion <= 8) {  
                valido = 1;
            } else {
                printf("\033[1A\033[K"); // Borra línea anterior
                printf("Ingrese una opcion valida: ");
            }
        }
    } while (!valido);

    return opcion;
}

int main() {
    // Para el encoding en Windows
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    srand(time(NULL));    // Inicializar la semilla del generador aleatorio
 
    int iteracion = 1;
    int opcion_validada = 0;

    do {
        mostrar_menu();       
        opcion_validada = ingresar_y_validar_opcion();

        limpiarPantalla(); 

        switch(opcion_validada) {
            case 1:
                opcion_uno();
                break;
            case 2:
                opcion_dos();
                break;
            case 3:
                opcion_tres();
                break;
            case 4:
                opcion_cuatro();
                break;
            case 5:
                opcion_cinco();   
                break;
            case 6:
                puts("Opcion Numero 6!");
                break;
            case 7:
                puts("Opcion Numero 7!");
                opcion_siete();
                break;
            case 8:
                opcion_ocho();
                break;
            case 0:
                puts("Saliendo del programa... ¡Hasta luego!");
                break;
            default:
                puts("Opcion invalida. Intente nuevamente.");
                break;
        }

        puts("\n \033[35m\033[1m═══════════════════════════════════");
        printf("    ⏩ Iteracion del menú Nº: %d\n", iteracion);
        iteracion++;
        puts(" ═══════════════════════════════════\n\n\033[0m");
        // if (opcion_validada != 0) {
        //     // printf("Ingrese una opcion valida: ");
          
        //     // scanf("%d", &opcion);
        //     // //Si el usuario escribió algo no numérico (ej: "abc"), scanf falla, no consume la entrada, y opcion queda sin cambiar.
        //     // //Esto es la raíz del bucle infinito si no limpias el buffer.


        //     // printf("\033[1A\033[2K");  // Sube y borra toda la línea anterior          
            
        //     opcion_validada = ingresar_y_validar_opcion();
        //     //limpiarPantalla(); 
        // }

    } while(opcion_validada != 0);
    
    
    return 0;
}

