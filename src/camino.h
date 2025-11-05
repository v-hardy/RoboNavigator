#ifndef CAMINO_H
#define CAMINO_H

#define MAX_NODOS (FILAS * COLUMNAS)

extern int matriz[FILAS][COLUMNAS];

typedef struct {
    int x, y;
    int vertice_adyacente[4];    // arreglo que contendra los posibles 4 Vertices adyacentes al vertice(x,y: que corresponde a la matriz en el mismo punto) 
    int total_de_vertices_adyacentes;
} Vertice;

typedef struct {
    int inquilino[MAX_NODOS];    // arreglo que contendra a los inquilinos: Vertices del grafo (resultado de convertir los 0 de nuestra matriz con el mapa cargado)
    int sacados;
    int ingresados;
} Vecindad;

void construirGrafo();    // Grafo simple, sin lazos ni aristas paralelas, es decir, hay una unica arista que conecta los Vertices adyacentes(o vertice_adyacente).
void imprimirGrafo();
int busqueda_camino(int inicio, int fin, int padre[MAX_NODOS]);
int mostrar_camino(int xInicio, int yInicio, int xFin, int yFin);

#endif