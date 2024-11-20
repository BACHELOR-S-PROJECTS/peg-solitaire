#include "juego.h"
#include <vector>
#include <fstream> 

bool juegoFinalizado(const Juego j) {
  return j.bloqueado || j.ganado;
};

std::istream &operator>>(std::istream &in, Juego &j) {
  int fila;
  int columna;

  // Leer los dos primeros datos del flujo de entrada 'in'
  in >> fila;
  in >> columna;

  // Crear el tablero con las dimensiones leidas
  Celda misCeldas[fila][columna];
  // Leer el tablero
  for (int i = 0; i < fila; i++) {
    for (int j = 0; j < columna; j++) {
      int numeroLeido;
      in >> numeroLeido;
      if (numeroLeido == 0) {
        misCeldas[i][j].tipo = NULA;
      } else if (numeroLeido == 1) {
        misCeldas[i][j].tipo = VACIA;
      } else if (numeroLeido == 2) {
        misCeldas[i][j].tipo = FICHA;
      }
    }
  }

  // Crear el tablero con las dimensiones leidas
  j.tablero.filas = fila;
  j.tablero.columnas = columna;
  for (int m = 0; m < fila; m++) {
    for (int n = 0; n < columna; n++) {
      j.tablero.celdas[m][n] = misCeldas[m][n];
    }
  }

  int filaMeta;
  int columnaMeta;

  in >> filaMeta;
  in >> columnaMeta;

  j.tablero.celdas[filaMeta][columnaMeta].meta = true;

  return in;
};

void mostrar(const Juego j) {
  mostrar(j.tablero); // llama a la funcion mostrar de tablero.cpp
};

void siguienteTurno(Juego &j) {
  int filaEscogida, columnaEscogida;
  std::cout << "Escoja ficha: ";
  std::cin >> filaEscogida >> columnaEscogida;

  std::string posiblesDirecciones[4] ;
  int posiblesDireccionesCounter = 0;

  Posicion inicio = {filaEscogida, columnaEscogida};
  
  encontrarDireccionesPosibles(j,inicio,posiblesDirecciones,posiblesDireccionesCounter);

  if (posiblesDireccionesCounter == 0){
    std::cout << "Casilla no valida" << std::endl;
    return;
  }

  for (int m = 0; m < NUM_DIRECCIONES; m++) {
    if (posiblesDirecciones[m] != "") {
      std::cout << m << ".-" << posiblesDirecciones[m] << std::endl;
    }
  }

  std::cout << "Escoja una direccion (";
  for (int m = 0; m < NUM_DIRECCIONES; m++) {
    if (posiblesDirecciones[m] != "") {
      std::cout << m << ",";
    }
  }
  std::cout << "): ";

  int direccionEscogida;
  std::cin >> direccionEscogida;

  if (posiblesDirecciones[direccionEscogida] == "Arriba") {
    Direccion direccion = DIRECCIONES[0];
    Posicion posicionEscogida = {filaEscogida, columnaEscogida};
    Movimiento movimiento = {posicionEscogida, {-1, 0, "Arriba"}};
    aplicarMovimiento(j, movimiento);
  } else if (posiblesDirecciones[direccionEscogida] == "Abajo") {
    Direccion direccion = DIRECCIONES[1];
    Posicion posicionEscogida = {filaEscogida, columnaEscogida};
    Movimiento movimiento = {posicionEscogida, {1, 0, "Abajo"}};
    aplicarMovimiento(j, movimiento);
  } else if (posiblesDirecciones[direccionEscogida] == "Izquierda") {
    Direccion direccion = DIRECCIONES[2];
    Posicion posicionEscogida = {filaEscogida, columnaEscogida};
    Movimiento movimiento = {posicionEscogida, {0, -1, "Izquierda"}};
    aplicarMovimiento(j, movimiento);
  } else if (posiblesDirecciones[direccionEscogida] == "Derecha") {
    Direccion direccion = DIRECCIONES[3];
    Posicion posicionEscogida = {filaEscogida, columnaEscogida};
    Movimiento movimiento = {posicionEscogida, {0, 1, "Derecha"}};
    aplicarMovimiento(j, movimiento);
  } else {
    std::cout << "Direccion no valida" << posiblesDirecciones << std::endl;
    return;
  }

  //function que revisa todas las casillas y si todas tienen counterposibledirections == 0 
  //entonces se pone el juego.bloqueado = true
  chequearBloqueo(j);

  //funcion que revisa si hay solo una ficha y esa ficha es la meta
  chequearGanador(j);

};
  


std::string motivoFinPartida(const Juego j) {
  if (j.ganado){
    return "Fin de la partida, ganaste";
  }
  else if (j.bloqueado) {
    return "Has perdido. Es imposible realizar ningun movimiento";
  }
  return "La partida no ha terminado";
};

void aplicarMovimiento(Juego &juego, const Movimiento mov) {
  Posicion posicionEscogida = mov.origen;
  Posicion unaPosicionMas = posicionEscogida + mov.dir;
  Posicion dosPosicionesMas = unaPosicionMas + mov.dir;
  quitarFicha(juego.tablero, posicionEscogida);
  quitarFicha(juego.tablero, unaPosicionMas);
  ponerFicha(juego.tablero, dosPosicionesMas);
};

void encontrarDireccionesPosibles(const Juego juego, Posicion origen,std::string (&direccionesPosibles)[4],int &n){
  int index = 0;
  for (int m = 0; m < NUM_DIRECCIONES; m++) {
    Posicion posicionEscogida = {origen.fila, origen.columna};
    Posicion unaPosicionMas = posicionEscogida + DIRECCIONES[m];
    Posicion dosPosicionesMas = unaPosicionMas + DIRECCIONES[m];

    if (unaPosicionMas.fila >= 0 && unaPosicionMas.fila < MAXDIM &&
        unaPosicionMas.columna >= 0 && unaPosicionMas.columna < MAXDIM) {
      if (dosPosicionesMas.fila >= 0 && dosPosicionesMas.fila < MAXDIM &&
          dosPosicionesMas.columna >= 0 && dosPosicionesMas.columna < MAXDIM) {
        if (hayFicha(juego.tablero, posicionEscogida)) {
          if (hayFicha(juego.tablero, unaPosicionMas)) {
            if (hayVacia(juego.tablero, dosPosicionesMas)) {
              direccionesPosibles[index] = DIRECCIONES[m].nombre;
              n++;
              index++;
            }
          }
        }
      }
    }
  }
};


void chequearGanador(Juego& juego){
  bool celdaMetaEsFicha = false;
  int counterFichas = 0;
  for (int m = 0; m < juego.tablero.filas; m++){
    for (int n = 0; n < juego.tablero.columnas; n++){
      if (juego.tablero.celdas[m][n].meta == true){
        if (juego.tablero.celdas[m][n].tipo == FICHA){
          celdaMetaEsFicha = true;
        }
      }
      if (juego.tablero.celdas[m][n].tipo == FICHA){
        counterFichas++;
      }
    }
  }
  if (celdaMetaEsFicha == true && counterFichas == 1){
    juego.ganado = true;
  }
};

void chequearBloqueo(Juego& juego){
  juego.bloqueado = true;
  for (int m = 0; m < juego.tablero.filas; m++){
    for (int n = 0; n < juego.tablero.columnas; n++){
      std::string posiblesDirecciones[4];
      int posiblesDireccionesCounter = 0;
      Posicion inicio = {m, n};
      encontrarDireccionesPosibles(juego,inicio,posiblesDirecciones,posiblesDireccionesCounter);
      if (posiblesDireccionesCounter > 0){
        juego.bloqueado = false;
      }
    }
  }
};

std::string direccionAleatoria(const std::vector<int> celda, std::vector<std::vector<int>> tableroArr,int dim){
  for (size_t i = 0; i < 4; i++) {
      int m = rand()%4; //elijo una direccion aleatoria
      if (celda[0] + DIRECCIONES[m].difFila*2 >= 0 && celda[0] + DIRECCIONES[m].difFila*2 < dim ){
        if (celda[1] + DIRECCIONES[m].difColumna*2 >= 0 && celda[1] + DIRECCIONES[m].difColumna*2 < dim ){
          //reviso si la celda un paso despues en direccion no es una ficha
          if (tableroArr[celda[0] + DIRECCIONES[m].difFila][celda[1] + DIRECCIONES[m].difColumna] != 2){
            //reviso si la celda dos pasos despues en direccion no es una ficha
            if (tableroArr[celda[0] + DIRECCIONES[m].difFila*2][celda[1] + DIRECCIONES[m].difColumna*2] != 2){
              //reviso si esta celda es una ficha
              if (tableroArr[celda[0]][celda[1]] == 2){
                return DIRECCIONES[m].nombre;
              }
            }
          }
        }
      }
  }
  return "No hay direccion posible";
};

void generarTablero(int dimension, int pasos){
  std::ofstream archivoSalida("tablero.txt");
  // Verifica si el archivo se abrió correctamente
  if (!archivoSalida) {
      std::cerr << "Error al abrir el archivo." << std::endl;
      return;
  }


  // Crear e inicializar el tablero con ceros
  std::vector<std::vector<int>> tableroArr(dimension, std::vector<int>(dimension, 0));

  //elegir el punto meta
  int puntoMetaX = rand() % dimension;
  int puntoMetaY = rand() % dimension;

  tableroArr[puntoMetaX][puntoMetaY] = 2;

  //array de todas las celdas no nulas
  std::vector<std::vector<int>> celdasNoNulas = {{puntoMetaX,puntoMetaY}};



  int numeroDeIteraciones = 0;
  int maxNumeroDeIteraciones = pasos;
  while (numeroDeIteraciones < maxNumeroDeIteraciones){
    numeroDeIteraciones++;

    int celdasNoNulasSize = celdasNoNulas.size();

    int randomCeldaNoNula = rand() % celdasNoNulasSize;

    std::string direccionRandom = direccionAleatoria(celdasNoNulas[randomCeldaNoNula],tableroArr, dimension);

    if (direccionRandom == "Arriba"){
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1]] = 1;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0] - 1][celdasNoNulas[randomCeldaNoNula][1]] = 2;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0] - 2][celdasNoNulas[randomCeldaNoNula][1]] = 2;
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0] - 1,celdasNoNulas[randomCeldaNoNula][1]});
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0] - 2,celdasNoNulas[randomCeldaNoNula][1]});
    }
    else if(direccionRandom == "Abajo"){
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1]] = 1;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0] + 1][celdasNoNulas[randomCeldaNoNula][1]] = 2;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0] + 2][celdasNoNulas[randomCeldaNoNula][1]] = 2;
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0] + 1,celdasNoNulas[randomCeldaNoNula][1]});
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0] + 2,celdasNoNulas[randomCeldaNoNula][1]});
    }
    else if(direccionRandom == "Izquierda"){
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1]] = 1;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1] - 1] = 2;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1] - 2] = 2;
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0],celdasNoNulas[randomCeldaNoNula][1] - 1});
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0],celdasNoNulas[randomCeldaNoNula][1] - 2});
    }
    else if(direccionRandom == "Derecha"){
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1]] = 1;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1] + 1] = 2;
      tableroArr[celdasNoNulas[randomCeldaNoNula][0]][celdasNoNulas[randomCeldaNoNula][1] + 2] = 2;
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0],celdasNoNulas[randomCeldaNoNula][1] + 1});
      celdasNoNulas.push_back({celdasNoNulas[randomCeldaNoNula][0],celdasNoNulas[randomCeldaNoNula][1] + 2});
    }

  }

  for (size_t i = 0; i < tableroArr.size(); ++i) {
      for (size_t j = 0; j < tableroArr[i].size(); ++j) {
          //std::cout << tableroArr[i][j] << " ";
      }
      //std::cout << std::endl;
  }

  //escribir
  archivoSalida << dimension << " " << dimension << std::endl;
  //escribir sobre el archivo .txt
  for(int i = 0; i < dimension; i++){
    for(int j = 0; j < dimension; j++){
      archivoSalida << tableroArr[i][j] << " ";
    }
    archivoSalida<<std::endl;
  }

  archivoSalida << puntoMetaX << " " << puntoMetaY << std::endl;

  // Cierra el archivo  
  archivoSalida.close();
}