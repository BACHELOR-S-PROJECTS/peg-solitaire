#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H
#include <iostream>

struct Posicion {
  int fila = -1;
  int columna = -1;
};

struct Direccion {
  int difFila = 0;
  int difColumna = 0;
  std::string nombre;
};

const int NUM_DIRECCIONES = 4;

const Direccion DIRECCIONES[] = {{-1, 0, "Arriba"},
                                 {1, 0, "Abajo"},
                                 {0, -1, "Izquierda"},
                                 {0, 1, "Derecha"}};

struct Movimiento {
  Posicion origen;
  Direccion dir;
};

/**
 * Esta función implementa el operador + para sumar posiciones
 * @param posicion que se quiere sumar.
 * @param direccion en la que se quiere sumar.
 * @return nada, solo edita la implementacion del operador +.
 */
Posicion operator+ (const Posicion p, const Direccion d);

#endif // MOVIMIENTO_H