#include <stdio.h>
#include <stdbool.h>
#include "mapa.h" 
#include "camino.h"
#include "robot.h"
#include "windows.h"
#include "lista.h"

// aca saque el extern y puse prim
Nodo Prim;
extern Robot robot;
extern int matriz[FILAS][COLUMNAS];

int row, col;

void actualizar_posicion(int x, int y) {

    row=x;
    col=y;
  
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// mira arriba, abajo, izquierda y derecha del objeto al que se le pasan los parametros y verifica si encontro el morron sino marca los lugares vacios el camino a seguir

int marcarAdyacentes(int row, int col, int value, int robot_encontrado){

    int izq = matriz[row][col-1];
    int der = matriz[row][col+1];
    int top = matriz[row-1][col];
    int bot = matriz[row+1][col];

   /*
    printf("Izquierda hay un: %d\n", izq);
    printf("Derecha hay un: %d\n", der);
    printf("Arriba hay un: %d\n", top);
    printf("Abajo hay un: %d\n", bot);
  */

    if(izq == 0){
        
        matriz[row][col-1]= value+1;
    }
    if(der == 0){
        
        matriz[row][col+1]= value+1;
    }
    if(top == 0){
        
        matriz[row-1][col]= value+1;
    }
    if(bot == 0){
          
        matriz[row+1][col]= value+1;
    }
    
    if (izq == -2 || der == -2 || top == -2 || bot == -2) {
        robot_encontrado = 1;
    }
    
    return robot_encontrado;
}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// llama a "marcarAdyacente()"" para que marque el camino hasta que se encuentre con el destino
// n es una variable de control para el bucle, condicion captura si se encontro o no el destino en "marcarAdyacente()"

void explorador(){

    int n=0;
    int condicion=0;    

    while(condicion == 0 && n < 500){

        for(int i=0; i < FILAS; i++){
            for(int j=0; j < COLUMNAS; j++){

                if(matriz[i][j] == n+1 && condicion == 0){

                    condicion = marcarAdyacentes(i, j, n+1, condicion);
                }
                
            }
        }

        //printf("valor de n: %d \n", n);
        n++;
        //printf("valor de condicion: %d \n", condicion);

    }

}

// <======================================= SEPARADOR DE BAJO PRESUPUESTO =======================================>

// mueve a robot por el mapa siguiendo el numero menor de los que tiene a su alrededor
Posicion encontrar_camino(int mov){
    
    //Nota se puede tratar izq, der, top bot como objetos ya que los mismos poseen coordenadas y valor (en marcarAdyacente tambien se podria)
    //struct objeto izq;

    int izq = matriz[row][col-1];
    int der = matriz[row][col+1];
    int top = matriz[row-1][col];
    int bot = matriz[row+1][col];

    int min= 9999;
    int i, j;

    if(min > izq && izq != -1 && izq != 0) {
        min= izq;
        i=row;
        j=col-1;
    }
    if(min > der && der != -1 && der != 0){
        min= der;
        i=row;
        j=col+1;
    } 
    if(min > top && top != -1 && top != 0){
        min= top;
        i=row-1;
        j=col;
    } 
    if(min > bot && bot != -1 && bot != 0){
        min= bot;
        i=row+1;
        j=col;
    }
    
    Posicion pos;
    //if (min != 9999){ ya ni me acuerdo por que queria poner esta condicion :(
    //printf(" MINIMO: %d - I: %d / J: %d", min, i, j);
    matriz[row][col]=999;
    //printf("En la posicion [%d, %d] dejamos un 999\n", row+1, col+1);
    encolar_lista(i, j);
    actualizar_posicion(i, j);
        
    //}

    pos.x=i;
    pos.y=j;

    return pos;
}