#include <iostream>
#include "movimiento.h"

Posicion operator+ (const Posicion p, const Direccion d){
  return {p.fila + d.difFila, p.columna + d.difColumna};
};