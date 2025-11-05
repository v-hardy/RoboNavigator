#include <stdio.h>
#include <stdbool.h>
#include "mapa.h" 
#include "camino.h" 

// ======== VARIABLES  =========
//extern int mapas2[FILAS][COLUMNAS];
Vertice grafo[MAX_NODOS];
int indiceVertice[FILAS][COLUMNAS];    // contendra el numero de vertice que corresponde al indice. SOBREDIMENSIONADO
int total_de_vertices = 0;

// Sera usado para encontrar vertice_adyacente del nodo...
// derecha, abajo, izquierda, arriba en cada una de las 4 iteraciones
const int adyacente_en_X[4] = {0, 1, 0, -1};  
const int adyacente_en_Y[4] = {-1, 0, 1, 0};

// ======== FUNCIONES PARA OPERAR LA VECINDAD =========
int esValido(int x, int y) {
    return (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS && (matriz[x][y] == 0 || matriz[x][y] == 2 || matriz[x][y] == 5));
}

void inicializarAlojamientos(Vecindad* c) {
    c->sacados = 0;
    c->ingresados = 0;
}

int alojamientosVacios(Vecindad* c) {
    return c->sacados == c->ingresados;
}

void alojar(Vecindad* c, int valor) {
    if (c->ingresados < MAX_NODOS)
        c->inquilino[c->ingresados++] = valor;
}

int desalojar(Vecindad* c) {
    return c->inquilino[c->sacados++];    // Siempre sale el primer inquilino en entrar, que ya se habia ingresado previamente.
}


// ======== CONSTRUIR GRAFO =========
void construirGrafo() {
    // Inicializo índices
    for (int x = 0; x < FILAS; x++) {
        for (int y = 0; y < COLUMNAS; y++) {
            indiceVertice[x][y] = -1;
        }
    }

    total_de_vertices = 0;
    // Creo vertices/nodos para celdas libres(0) de matriz
    for (int x = 0; x < FILAS; x++) {
        for (int y = 0; y < COLUMNAS; y++) {
            if (matriz[x][y] == 0 || matriz[x][y] == 2 || matriz[x][y] == 5 ) {
                // agrego un Vertice al grafo
                grafo[total_de_vertices].x = x;
                grafo[total_de_vertices].y = y;
                grafo[total_de_vertices].total_de_vertices_adyacentes = 0;
                // asocio el indice de coordenadas al numero de vertice asignado, y luego incremento el total_de_vertices
                indiceVertice[x][y] = total_de_vertices++;
            }
        }
    }

    // Conecto con vertice_adyacente
    for (int i = 0; i < total_de_vertices; i++) {
        int x = grafo[i].x;
        int y = grafo[i].y;
        for (int k = 0; k < 4; k++) {
            int nx = x + adyacente_en_X[k];
            int ny = y + adyacente_en_Y[k];
            if (esValido(nx, ny)) {
                grafo[i].vertice_adyacente[grafo[i].total_de_vertices_adyacentes++] = indiceVertice[nx][ny];
            } 
        }
    }
}

// Implemetacion de busqueda por anchura
int busqueda_camino(int inicio, int fin, int padre[MAX_NODOS]) {
    bool visitado[MAX_NODOS] = {false};
    Vecindad cola;
    inicializarAlojamientos(&cola);
    alojar(&cola, inicio);
    visitado[inicio] = true;
    padre[inicio] = -1;

    while (!alojamientosVacios(&cola)) {
        int actual = desalojar(&cola);
        if (actual == fin) return 1;

        for (int i = 0; i < grafo[actual].total_de_vertices_adyacentes; i++) {
            int vecino = grafo[actual].vertice_adyacente[i];
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                padre[vecino] = actual;
                alojar(&cola, vecino);
            }
        }
    }
    return 0;
}

// ======== camino =========
int mostrar_camino(int xInicio, int yInicio, int xFin, int yFin) {

    int inicio = indiceVertice[xInicio][yInicio]; //posicion inicial
    int fin    = indiceVertice[xFin][yFin]; //posicion destino
    int padre[MAX_NODOS]; //ARREGLO
    int cadena = 0;    // longitud de cadena elemental y sencilla  
    printf("Dentro de mostrar camino %d - %d - %d -  %d.\n",inicio, fin, padre, cadena);

    if (busqueda_camino(inicio, fin, padre)) {
        printf("Dentro de mostrar camino en el if.\n");
        // Reconstruir camino en un arreglo 'ruta' como antes
        int ruta[MAX_NODOS];
        
        for (int at = fin; at != -1; at = padre[at]) {
            ruta[cadena++] = at;
        }
        
        //  encolar los nodos del camino (de inicio a fin)
        // 'ruta' está en orden inverso (fin → inicio), así que apilamos al revés
        for (int i = cadena - 1; i >= 0; i--) {
            int nodo = ruta[i];
            // if (grafo[nodo].x != xInicio && grafo[nodo].y != yInicio) {
                encolar_lista(grafo[nodo].x, grafo[nodo].y);
            //}
        }
        
        // Marcar camino en el mapa (excepto inicio y fin)
        for (int i = 1; i < cadena - 1; i++) {
            int nodo = ruta[i];
            matriz[grafo[nodo].x][grafo[nodo].y] = 3;
        }

        // Mostrar el camino encontrado
        printf("  Camino encontrado (%d pasos):\n", cadena - 1);
        for (int i = cadena - 1; i >= 0; i--) {
            printf("(%d,%d) ", grafo[ruta[i]].x + 1, grafo[ruta[i]].y + 1);
        }
        printf("\n");

        // Si quieres, puedes verificar el contenido de la pila sin desalojar
        printf("\nContenido actual de la pila:\n");
        recorrer_lista();

    } else {
        printf("No se encontró un camino.\n");
        printf("Dentro de mostrar camino  %d - %d - %d -  %d.\n",inicio, fin, padre, cadena);

    }

    return cadena;
}

void imprimirGrafo() {
    // Recorremos todos los vértices del grafo
    for (int i = 0; i < total_de_vertices; i++) {
        // Imprimimos las coordenadas del vértice actual
        printf("Vértice %d: (%d, %d)\n", i, grafo[i].x, grafo[i].y);
        
        // Imprimimos los vértices adyacentes
        if (grafo[i].total_de_vertices_adyacentes > 0) {
            printf("  Adyacentes a (%d, %d): ", grafo[i].x, grafo[i].y);
            for (int j = 0; j < grafo[i].total_de_vertices_adyacentes; j++) {
                // Imprimimos las coordenadas de cada vértice adyacente
                int adyacente_idx = grafo[i].vertice_adyacente[j];
                printf("(%d, %d) ", grafo[adyacente_idx].x, grafo[adyacente_idx].y);
            }
            printf("\n");
        } else {
            printf("  No tiene vértices adyacentes.\n");
        }
    }
}