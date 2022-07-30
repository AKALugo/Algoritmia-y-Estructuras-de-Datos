// g++ -g arbolB.cc -o arbol
// ./arbol

#include <iostream>

#include "arbolB_t.h"

int main(void) {

  int opcion;
  int valor;
  ArbolB_t<int> arbol;

  do {
    std::cout << "[0] Salir\n[1] Insertar Clave\n[2] Buscar Clave\n[3] Imprimir árbol\n";
    std::cin >> opcion;

    switch (opcion) {
      case 1:
        std::cout << "Introduzca la Clave a buscar:\n";
        std::cin >> valor;
        arbol.InsertaEquil(valor);
        std::cout << arbol;
      break;
      case 2:
        std::cout << "Introduzca la Clave a buscar:\n";
        std::cin >> valor;
        if(arbol.Buscar(valor)) std::cout << "Valor encontrado\n";
        else                    std::cout << "Valor NO encontrado\n";
      break;
      case 3:
        std::cout << arbol;
      break;
    }
  } while (opcion != 0);
}