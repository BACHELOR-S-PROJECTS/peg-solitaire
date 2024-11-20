#ifndef TABLERO_H
#define TABLERO_H
#include "celda.h"
#include "movimiento.h"

const int MAXDIM = 10;

struct Tablero {
  Celda celdas[MAXDIM][MAXDIM];
  int filas, columnas;
};

/**
 * Esta función muestra el tablero en la consola
 * @param tablero a pintar
 * @return nada
 */
void mostrar (const Tablero tablero);

/**
 * Esta función revisa si hay una ficha en la posicion dada
 * @param tablero de juego
 * @param posicion de interes
 * @return bool de si la posicion es una ficha
 */
bool hayFicha(const Tablero tablero, const Posicion pos);

/**
 * Esta función revisa si la celda dada esta vacia
 * @param tablero de juego
 * @param posicion de interes
 * @return bool de si la posicion esta vacia
 */
bool hayVacia(const Tablero tablero, const Posicion pos);

/**
 * Esta función revisa si la celda dada es una meta
 * @param tablero de juego
 * @param posicion de interes
 * @return bool de si la posicion es la meta
 */
bool esMeta(const Tablero tablero, const Posicion pos);

/**
 * Esta función cuenta cuantas fichas hay en el tablero
 * @param tablero de juego
 * @return int del numero de celdas que son fichas
 */
int contarFichas(const Tablero tablero);

/**
 * Esta función convierte una celda que es una ficha a una celda vacia
 * @param referencia al tablero de juego
 * @param pos a editar
 * @return nada, solo cambia el tablero
 */
void quitarFicha(Tablero& tablero, const Posicion pos);

/**
 * Esta función convierte una celda que es una celda vacia a una celda que es una ficha
 * @param referencia al tablero de juego
 * @param pos a editar
 * @return nada, solo cambia el tablero
 */
void ponerFicha(Tablero& tablero, const Posicion pos);


#endif // TABLERO_H