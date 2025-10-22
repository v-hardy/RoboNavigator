#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#include "mapa.h"
#include "interfaz.h"

void mostrar_menu() {
    int opcion = 0;
    
    do {
        puts("\n++++++++++++++++++++++++++++++++++++");
        puts(" Bienvenido al sistema de control!! ");
        puts("++++++++++++++++++++++++++++++++++++");
        puts("  1.- Generar Matriz Aleatoria");
        puts("  2.- Imprimir matriz");
        puts("  3.- Mapa ASCII con simuilacion de robot");
        puts("  4.- Salir");
        printf("Ingrese una opcion valida: ");
        scanf("%d", &opcion);

        switch(opcion) {
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
                puts("Saliendo del programa... ¡Hasta luego!");
                break;
            default:
                puts("Opcion invalida. Intente nuevamente.");
                break;
        }
    } while(opcion != 4);
}


int main() {

    // Inicializar la semilla del generador aleatorio
    srand(time(NULL));
    mostrar_menu();
    
    return 0;
}

