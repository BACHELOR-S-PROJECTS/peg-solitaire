#include "tablero.h"

void mostrar(const Tablero tablero) {
  std::cout << "   " ;
  for (int n = 0; n < tablero.columnas; n++) {
    std::cout << " " << n << " ";
  }
  std::cout << std::endl;
  for (int m = 0; m < tablero.filas; m++) {
    for (int n = 0; n < tablero.columnas; n++) {
      if (n == 0) {
        std::cout << " " << m << " ";
      }
      mostrar(tablero.celdas[m][n]);
    }
    std::cout << std::endl;
  }
};
bool hayFicha(const Tablero tablero, const Posicion pos) {
  return tablero.celdas[pos.fila][pos.columna].tipo == FICHA;
};
bool hayVacia(const Tablero tablero, const Posicion pos) {
  return tablero.celdas[pos.fila][pos.columna].tipo == VACIA;
};
bool esMeta(const Tablero tablero, const Posicion pos) {
  return tablero.celdas[pos.fila][pos.columna].meta;
};
int contarFichas(const Tablero tablero) {
  int counter = 0;
  for (int i = 0; i < tablero.filas; i++) {
    for (int j = 0; j < tablero.columnas; j++) {
      if (tablero.celdas[i][j].tipo == FICHA) {
        counter++;
      }
    }
  }
  return counter;
};
void quitarFicha(Tablero &tablero, const Posicion pos) {
  tablero.celdas[pos.fila][pos.columna].tipo = VACIA;
};
void ponerFicha(Tablero &tablero, const Posicion pos) {
  tablero.celdas[pos.fila][pos.columna].tipo = FICHA;
};