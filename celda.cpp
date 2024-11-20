#include "celda.h"
#include <iostream>
#include "colores.h"
const std::string ANSI_COLOR_RED = "\033[31m";
const std::string ANSI_COLOR_GREEN = "\033[32m";
const std::string ANSI_COLOR_YELLOW = "\033[33m";
const std::string ANSI_COLOR_BLUE = "\033[34m";
const std::string ANSI_COLOR_MAGENTA = "\033[35m";
const std::string ANSI_COLOR_CYAN = "\033[36m";
const std::string ANSI_COLOR_RESET = "\033[0m";

void mostrar(const Celda c) {
  if (c.meta && c.tipo == VACIA) {
    std::cout << BG_YELLOW << " * " << BG_BLACK ;
  }
  else if (c.meta && c.tipo == FICHA) {
    std::cout << BG_BLUE << " * " << BG_BLACK;
  } else if (c.tipo == NULA) {
    std::cout << BG_BLACK << "   " << BG_BLACK;
  } else if (c.tipo == VACIA) {
    std::cout << BG_YELLOW "   " << BG_BLACK;
  } else if (c.tipo == FICHA) {
    std::cout << BG_BLUE << "   " << BG_BLACK;
  }
};