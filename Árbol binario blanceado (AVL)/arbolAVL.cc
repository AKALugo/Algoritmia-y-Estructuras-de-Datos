// g++ -g arbolAVL.cc -o arbol
// ./arbol

#include <iostream>

#include "arbolAVL_t.h"

int main(void) {

  int opcion;
  int valor;
  ArbolAVL_t<int> arbol;

  std::cout << "!!!MODO TRAZA DESACTIVADO POR DEFECTO!!!\n";
  do {
    std::cout << "[0] Salir\n[1] Insertar Clave\n[2] Buscar Clave\n[3] Eliminar Clave\n[4] Activar/Desactivar modo traza\n[5] Imprimir árbol\n";
    std::cin >> opcion;

    switch (opcion) {
      case 1:
        std::cout << "Introduzca la Clave a buscar:\n";
        std::cin >> valor;
        arbol.Insertar(valor);
        std::cout << arbol;
      break;
      case 2:
        std::cout << "Introduzca la Clave a buscar:\n";
        std::cin >> valor;
        if(arbol.BuscarC(valor)) std::cout << "\nValor encontrado\n";
        else                    std::cout << "\nValor NO encontrado\n";
      break;
      case 3:
        std::cout << "Introduzca la Clave a eliminar:\n";
        std::cin >> valor;
        arbol.Eliminar(valor);
        std::cout << arbol;
        break;
      case 4:
        if (!arbol.Traza) {
          std::cout << "ACTIVANDO MODO TRAZA\n";
          arbol.Traza = true;
        }
        else {
          std::cout << "DESACTIVANDO MODO TRAZA\n";
          arbol.Traza = false;
        }
        break;
      case 5:
        std::cout << arbol;
      break;
    }
  } while (opcion != 0);
}