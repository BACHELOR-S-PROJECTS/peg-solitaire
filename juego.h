#ifndef JUEGO_H
#define JUEGO_H
#include "tablero.h"
#include <vector>

struct Juego {
  Tablero tablero;
  bool ganado = false;
  bool bloqueado = false;
};

/**
 * Esta función retorna si el juego se ha finalizada ya sea porque se ha ganado o porque se ha bloqueado.
 * @param j el un paso por valor del juego.
 * @return boolean de si el juego esta finalizado o no.
 */
bool juegoFinalizado(const Juego j);

/**
 * Esta función es para cambiar la implementacion del operador de lectura de un tablero.
 * @param &in El flujo de lectura.
 * @param &j Es la referencia del juego.
 * @return una sobrecarga o implementacion de un operador.
 */
std::istream &operator>>(std::istream &in, Juego &j);

/**
 * Esta función llama a la funcion mostrar del tablero.
 * @param j el un paso por valor del juego.
 * @return vacio porque llama a otra funcion que tambien retorna vacio.
 */
void mostrar(const Juego j);

/**
 * Esta función les la encargada de pedir info al usuario y de llamar a las funciones encargadas de la logica.
 * @param j el un paso por referencia del juego.
 * @return vacio porque usa funciones de impresion en la consola y logica.
 */
void siguienteTurno(Juego &j);

/**
 * Esta función les la encargada de pedir info al usuario y de llamar a las funciones encargadas.
 * @param j el un paso por valor del juego.
 * @return string que es un resumen de porque el juego ha finalizado.
 */
std::string motivoFinPartida(const Juego j);

/**
 * Esta función es la encargada de editar el array de direcciones posibles y el contador de direcciones posilbes.
 * @param juego el un paso por valor del juego.
 * @param origen es la posicion de la cual se van a hallar las posiciones posibles.
 * @param &direccionesPosibles el un paso por referencia del array de direcciones posibles.
 * @param &n es el paso por referencia del contador de direcciones posibles. 
 * @return nada, solo cambia los valores de direccionesPosibles y el contador de direcciones posibles.
 */
void encontrarDireccionesPosibles(const Juego juego, Posicion origen,std::string (&direccionesPosibles)[4],int &n);



/**
 * Esta función es la encargada de la logica de moverse.
 * se quita la ficha de la pos origen, y la siguiente en direccion
 * por ultimo se pone ficha que se da despues de moverse 2 veces en dir desde la pos origen
 * @param juego el un paso por referencia del juego.
 * @param mov es el movimiento que se va a hacer (tiene un origen y un destino).
 * @return nada, solo cambia los valores del tablero.
 */
void aplicarMovimiento(Juego& juego, const Movimiento mov);

/**
 * Esta función es la de chequear si la unica ficha que queda es la meta
 * @param juego el un paso por referencia del juego.
 * @return nada, solo cambia el estado de ganado del juego.
 */
void chequearGanador(Juego& juego);

/**
 * Esta función es la de chequear si ya no hay movimientos posibles
 * o que es lo mismo si ninguna ficha tiene movimientos posibles
 * @param juego el un paso por referencia del juego.
 * @return nada, solo cambia el estado de bloqueado del juego.
 */
void chequearBloqueo(Juego& juego);

/**
 * Esta función retorna la direccion en string que se elije de forma aleatoria
 * @param la celda a mirar la direccion aleatoria
 * @param vector del tablero
 * @param dimension del tablero
 * @return "Arriba" | "Abajo" | "Izquierda" | "Derecha" | "No hay direccion posible"
 */
std::string direccionAleatoria(const std::vector<int> celda, std::vector<std::vector<int>> tableroArr,int dim);

/**
 * Esta funcion escribe el nuevo tablero aleatorio en el .txt
 * @param dimension del tablero
 * @return el numero de pasos que se usa para llegar al tablero / es la complejidad
 * @nada
 */
void generarTablero(int dimension, int pasos);


#endif // JUEGO_H