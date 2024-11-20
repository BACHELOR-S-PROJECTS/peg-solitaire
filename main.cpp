#include "celda.h"
#include "juego.h"
#include <fstream> // Added
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
/**
 * Esta función la que le pregunta al jugador si quiere volver a jugar despues de perder o ganar
 * @return respuesta en bool del jugador
 */
bool quiereVolverAJugar() {
  bool respuesta;
  std::string respuestaStr;
  std::cout << "Nueva partida (s/n): ";
  std::cin >> respuestaStr;
  while (true) {
    if (respuestaStr == "s") {
      respuesta = true;
      return respuesta;
    } else if (respuestaStr == "n") {
      respuesta = false;
      return respuesta;
    } else {
      std::cout << std::endl;
      std::cout << "Respuesta invalida" << std::endl;
      std::cout << "Nueva partida (s/n): ";
    }
  }
}

// Función principal
//Se corre con:
//g++ -o miSolitaio.exe main.cpp celda.cpp juego.cpp  movimiento.cpp tablero.cpp
int main() {
  srand(time(nullptr));//inicializar el rand() con la fecha
  bool seguirJugando = true;
  while (seguirJugando) { // quiere seguir jugando
    //llamar a la funcion para randomizar el tablero.txt
    std::cout << "--- Comienza el SOLITARIO --- " << std::endl;
    // leer tablero
    Juego juego;
    generarTablero(6,6);
    std::ifstream fichero;
    fichero.open("tablero.txt");
    fichero >> juego;
    fichero.close();

    while (!juegoFinalizado(juego)) { // partida no finalizado
      mostrar(juego);
      siguienteTurno(juego);
    }
    mostrar(juego);
    std::cout << motivoFinPartida(juego) << std::endl;
    seguirJugando = quiereVolverAJugar();
  }
  return 0;
}
