#include <stdio.h>
#include <stdbool.h>
#include "mapa.h" 
#include "camino.h" 


//RE NOMBRAR MAPA1


// ======== VARIABLES GLOBALES =========
extern int mapa1[20][20];

Nodo grafo[MAX_NODOS];
int indiceNodo[FILAS][COLUMNAS];
int totalNodos = 0;
const int movX[4] = {0, 1, 0, -1};  // derecha, abajo, izquierda, arriba
const int movY[4] = {-1, 0, 1, 0};

// ======== FUNCIONES AUXILIARES =========
int esValido(int x, int y) {
    return (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS && mapa1[x][y] == 0);
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
            if (mapa1[x][y] == 0) {
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

// ======== BFS =========
int bfs(int inicio, int fin, int padre[MAX_NODOS]) {
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

    // Validar rango
    if (xInicio < 0 || xInicio >= FILAS || yInicio < 0 || yInicio >= COLUMNAS ||
        xFin < 0 || xFin >= FILAS || yFin < 0 || yFin >= COLUMNAS) {
        printf("\n  \033[1m\033[31m¡Error! Coordenadas fuera del mapa.\033[0m %d %d %d %d\n", xInicio, yInicio, xFin, yFin);
        return 1;
    }


    int inicio = indiceNodo[xInicio][yInicio]; //posicion inicial
    int fin    = indiceNodo[xFin][yFin]; //posicion destino
   
    int padre[MAX_NODOS];
    if (bfs(inicio, fin, padre)) {
        // Reconstruir camino
        int ruta[MAX_NODOS];
        int len = 0;
        for (int at = fin; at != -1; at = padre[at]) {
            ruta[len++] = at;
        }

        // Marcar camino en mapa (excepto inicio y fin)
        for (int i = 1; i < len - 1; i++) {
            int nodo = ruta[i];
            matriz[grafo[nodo].x][grafo[nodo].y] = 3;
        }

        printf("  Camino encontrado (%d pasos):\n", len - 1);
        for (int i = len - 1; i >= 0; i--) {
            printf("(%d,%d) ", grafo[ruta[i]].x + 1, grafo[ruta[i]].y + 1);
        }
        printf("\n");

    } else {
        printf("No se encontró un camino.\n");
    }

    return 0;
}
