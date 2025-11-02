#include <stdio.h>
#include <stdbool.h>
#include "mapa.h" 
#include "camino.h" 

// ======== VARIABLES  =========
//extern int mapas2[FILAS][COLUMNAS];


Nodo grafo[MAX_NODOS];
int indiceNodo[FILAS][COLUMNAS];
int totalNodos = 0;

// Sera usado para encontrar vecinos del nodo...
// derecha, abajo, izquierda, arriba
const int movX[4] = {0, 1, 0, -1};  
const int movY[4] = {-1, 0, 1, 0};

// ======== FUNCIONES AUXILIARES =========
int esValido(int x, int y) {
    //printf("%d", matriz[x][y]);
    return (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS && mapa2[x][y] == 0);
}

void inicializarCola(Cola* c) {
    c->frente = 0;
    c->fondo = 0;
}

int colaVacia(Cola* c) {
    return c->frente == c->fondo;
}

void encolar(Cola* c, int valor) {
    if (c->fondo < MAX_NODOS)
        c->datos[c->fondo++] = valor;
}

int desencolar(Cola* c) {
    return c->datos[c->frente++];
}

// ======== CONSTRUIR GRAFO =========
void construirGrafo() {
    // Inicializar índices
    for (int x = 0; x < FILAS; x++) {
        for (int y = 0; y < COLUMNAS; y++) {
            indiceNodo[x][y] = -1;
        }
    }

    totalNodos = 0;
    // Crear nodos para celdas libres
    for (int x = 0; x < FILAS; x++) {
        for (int y = 0; y < COLUMNAS; y++) {
            if (mapa2[x][y] == 0) {
                grafo[totalNodos].x = x;
                grafo[totalNodos].y = y;
                grafo[totalNodos].num_vecinos = 0;
                indiceNodo[x][y] = totalNodos++;
            }
        }
    }

    // Conectar vecinos
    for (int i = 0; i < totalNodos; i++) {
        int x = grafo[i].x;
        int y = grafo[i].y;
        for (int k = 0; k < 4; k++) {
            int nx = x + movX[k];
            int ny = y + movY[k];
            if (esValido(nx, ny)) {
                grafo[i].vecinos[grafo[i].num_vecinos++] = indiceNodo[nx][ny];
            }
        }
    }
}

// Implemetacion de busqueda por anchura
int busqueda_camino(int inicio, int fin, int padre[MAX_NODOS]) {
    bool visitado[MAX_NODOS] = {false};
    Cola cola;
    inicializarCola(&cola);
    encolar(&cola, inicio);
    visitado[inicio] = true;
    padre[inicio] = -1;

    while (!colaVacia(&cola)) {
        int actual = desencolar(&cola);
        if (actual == fin) return 1;

        for (int i = 0; i < grafo[actual].num_vecinos; i++) {
            int vecino = grafo[actual].vecinos[i];
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                padre[vecino] = actual;
                encolar(&cola, vecino);
            }
        }
    }
    return 0;
}

// ======== camino =========
int mostrar_camino(int xInicio, int yInicio, int xFin, int yFin) {

    int inicio = indiceNodo[xInicio][yInicio]; //posicion inicial
    int fin    = indiceNodo[xFin][yFin]; //posicion destino
    int padre[MAX_NODOS]; //ARREGLO
    int len = 0;
   
    if (busqueda_camino(inicio, fin, padre)) {
        // Reconstruir camino en un arreglo 'ruta' como antes
        int ruta[MAX_NODOS];
        
        for (int at = fin; at != -1; at = padre[at]) {
            ruta[len++] = at;
        }
        
        // encolar los nodos del camino (de inicio a fin)
        // 'ruta' está en orden inverso (fin → inicio), así que apilamos al revés
        for (int i = len - 1; i >= 0; i--) {
            int nodo = ruta[i];
            // if (grafo[nodo].x != xInicio && grafo[nodo].y != yInicio) {
                encolar_lista(grafo[nodo].x, grafo[nodo].y);
            //}
        }
        
        // Marcar camino en el mapa (excepto inicio y fin)
        for (int i = 1; i < len - 1; i++) {
            int nodo = ruta[i];
            matriz[grafo[nodo].x][grafo[nodo].y] = 3;
        }

        // Mostrar el camino encontrado
        printf("  Camino encontrado (%d pasos):\n", len - 1);
        for (int i = len - 1; i >= 0; i--) {
            printf("(%d,%d) ", grafo[ruta[i]].x + 1, grafo[ruta[i]].y + 1);
        }
        printf("\n");

        // Si quieres, puedes verificar el contenido de la pila sin desencolar
        printf("\nContenido actual de la pila:\n");
        recorrer_lista();

    } else {
        printf("No se encontró un camino.\n");
    }

    return len;
}
