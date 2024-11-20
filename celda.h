#ifndef CELDA_H
#define CELDA_H
#include <iostream>

enum tipoCelda { NULA, VACIA, FICHA };

struct Celda {
  tipoCelda tipo;
  bool meta = false;
};

/**
 * Esta función muestra el tablero. Pinta una celda dada segun su tipo
 * @param c Es la celda.
 * @return vacio.
 */
void mostrar(const Celda c);

#endif // CELDA_H