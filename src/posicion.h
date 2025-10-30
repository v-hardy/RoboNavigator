#ifndef POSICION_H
#define POSICION_H

typedef struct {
    int x;
    int y;
} Posicion;

// LO USAMOS PARA LOS DELTAs DE FILA Y COLUMNA
typedef enum {
    NEGATIVO = -1,
    POSITIVO = 1
} Sentido;

typedef struct {
    int abscisa;              // delta en X
    int ordenada;             // delta en Y
    Sentido sentido_abscisa;  // 1 para positivo, -1 para negativo
    Sentido sentido_ordenada; // 1 para positivo, -1 para negativo
} Delta;

#endif