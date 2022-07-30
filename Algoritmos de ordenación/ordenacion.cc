// g++ -g ordenacion.cc -o ordenacion
// ./ordenacion

#include<stdlib.h>

#include <iostream>
#include <vector>

#include "ordenacion.h"


bool algoritmo;

int main (void) {

  unsigned metodo, size, manual;
  char traza;

  do {
    std::cout << "Seleccione el algoritmo a ejecutar:\n1.Insercion.\n2.QuickSort."
                << "\n3.SellSort.\n4.Selección.\n5.MergeSort.\n6.HeapSort\n";
    std::cin >> metodo;
  } while (metodo < 1 || metodo > 6);
  do {
    std::cout << "Introduzca el tamaño del vector:\n";
    std::cin >> size;
  } while (size <= 0);
  do {
    std::cout << "Desea ver la traza a realizar por el algoritmo:\n";
    std::cin >> traza;
  } while (traza != 's' && traza != 'n');

  if (traza == 'n')
    algoritmo = false;
  else 
    algoritmo = true;

  do {
    std::cout << "Cómo desea introducir los valores del vector:\n1.Manual.\n"
              << "2.Automaticamente.\n";
    std::cin >> manual;
  } while (manual < 1 || manual > 2);

  std::vector<int> vector;
  vector.resize(size);

  srand(time(NULL));

  for (auto i = 0; i < vector.size(); i++) {
    if (manual == 1) {
      std::cout << "Introduzca el valor Nº" << i + 1 << " : ";
      std::cin >> vector[i];
    }
    else {
      vector[i] = 1+rand()%(1001-1);
    }
  }

  Mostrar<int>(vector);

  switch (metodo) {
  case 1:
    Insercion<int>(vector, vector.size());
    break;
  case 2:
    QuickSort<int>(vector, vector.size());
    break;
  case 3:
    ShellSort<int> (vector, vector.size());
    break;
  case 4:
    Seleccion<int> (vector, vector.size());
    break;
  case 5:
    MergeSort<int> (vector, vector.size());
    break;
  case 6:
    HeapSort<int> (vector, vector.size());
    break;
  }
  if (!algoritmo)
    Mostrar<int>(vector);
}