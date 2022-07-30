
#include "tabla_hash.h"
#include "dispercion_t.h"
#include "exploracion_t.h"

#include <iostream>

int main (void) {

  unsigned aux, aux2;
  int aux1;
  std::cout << "Indica el SIZE de la tabla de Hash:" << std::endl;
  std::cin >> aux;

  std::cout << "Indica el SIZE de la celda de la tabla:" << std::endl;
  std::cin >> aux2;

  std::cout << "Indique el tipo de DISPERSIÓN, 1 para fd.Módulo y 2 para fd.PSEUDOALEATORIA:" << std::endl;
  std::cin >> aux1;

  FuncionDispersion<unsigned>* fd_aux;
  if (aux1 == 2)
    fd_aux = new fdPseudoAleatoria<unsigned> (aux);
  else
    fd_aux = new fdModulo<unsigned> (aux);

  std::cout << "Indique el tipo de EXPLORACIÓN, 1 para fe.LINEAL, 2 para fe." <<
               "CUADRATICA, 3 para fe.DOBLEDISPERSIÓN y 4 para fe.REDISPRESION:\n";
  std::cin >> aux1;

  FuncionExploracion<unsigned>* fe_aux;
  if (aux1 == 1)
    fe_aux = new feLineal<unsigned>;
  if (aux1 == 2)
    fe_aux = new feCuadratica<unsigned>;
  if (aux1 == 3)
    fe_aux = new feDobleDispersion<unsigned> (fd_aux);
  else
    fe_aux = new feReDispersion<unsigned> (aux2);


  TablaHash<int> hash (aux, aux2, fe_aux, fd_aux);

  bool salir = false;
  while (!salir) {

    std::cout << "/////////////////////////////////////////////////////////\n";
    std::cout << "1. Insertar elemento\n";
    std::cout << "2. Devolver elemento\n";
    std::cout << "3. Salir\n";
    std::cin >> aux1;

    switch (aux1) {
      case 1:
        std::cout << "Hash:\n";
        std::cin >> aux;
        std::cout << "Valor:\n";
        std::cin >> aux1;
        
        if (hash.Insertar(aux, aux1)) {
          std::cout << "Se ha insertado el VALOR " << aux1 << " con HASH " << aux << " con EXITO\n";
        }
        else
          std::cout << "Ha ocurrido un ERROR ya que ya existía un valor con ese HASH, pruebe con otro HASH\n";
        break;
      case 2:
        std::cout << "Hash:\n";
        std::cin >> aux;

        if (hash.Buscar(aux, aux1))
          std::cout << "VALOR:\n" << aux1 << "\n";
        else 
          std::cout << "Ha ocurrido un ERROR, no hay ningún VALOR con ese HASH\n";
        break;
      default:
        salir = true;
        break;
    }
  }
  std::cout << "/////////////////////////////////////////////////////////\n";
  return 0;
}