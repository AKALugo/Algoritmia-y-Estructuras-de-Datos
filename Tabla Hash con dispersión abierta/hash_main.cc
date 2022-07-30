
#include "tabla_hash.h"
#include "dispercion_t.h"

#include <iostream>

int main (void) {

  unsigned aux, aux1;
  std::cout << "Indica el SIZE de la tabla de Hash:" << std::endl;
  std::cin >> aux;

  std::cout << "Indique el tipo de DISPERSIÓN, 1 para fd.Módulo y 2 para fd.PSEUDOALEATORIA:" << std::endl;
  std::cin >> aux1;

  FuncionDispersion<unsigned>* aux2;
  if (aux1 == 2)
    aux2 = new fdPseudoAleatoria<unsigned> (aux);
  else
    aux2 = new fdModulo<unsigned> (aux);

  TablaHash<unsigned> hash (aux,aux2);

  bool salir = false;
  while (!salir) {

    std::cout << "/////////////////////////////////////////////////////////\n";
    std::cout << "1. Insertar elemento\n";
    std::cout << "2. Devolver elemento\n";
    std::cout << "3. Random\n";
    std::cout << "4. Salir\n";
    std::cin >> aux1;

    switch (aux1) {
      case 1:
        std::cout << "Hash:\n";
        std::cin >> aux;

        if (hash.Insertar(aux)) {
          std::cout << "Valor:\n";
          std::cin >> aux1;
          
          hash.Insertar(aux, aux1);
          std::cout << "Se ha insertado el VALOR " << aux1 << " con HASH " << aux << " con EXITO\n";
        }
        else
          std::cout << "Ha ocurrido un ERROR ya que ya existía un valor con ese HASH, pruebe con otro HASH\n";
        break;
      case 2:
        std::cout << "Hash:\n";
        std::cin >> aux;

        if (hash.Buscar(aux))
          std::cout << "VALOR:\n" << hash.Retornar(aux) << "\n";
        else 
          std::cout << "Ha ocurrido un ERROR, no hay ningún VALOR con ese HASH\n";
        break;
      case 3:
        srand(time(NULL));
        unsigned numeros;

        for(unsigned recorrido = 0; recorrido < 10000; recorrido ++) {

          numeros = rand() % 100000;
          if (hash.Insertar(numeros))
            hash.Insertar(numeros, numeros);
        }
        std::cout << "El mayor número de COLISIONES ES: " << hash.Contador() << "\n";
      break;
      default:
        salir = true;
        break;
    }
  }
  std::cout << "/////////////////////////////////////////////////////////\n";
  return 0;
}