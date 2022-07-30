
#pragma once

#include "termcolor.hpp"

#include <iostream>
#include <vector>

extern bool algoritmo;



template <class T>
void
Mostrar (std::vector<T>& vector) {
  
  std::cout << "El vector actualmente :\n";
  for (auto i = 0; i < vector.size(); i++) {
    std::cout << termcolor::blue << vector[i] << termcolor::reset << 
    termcolor::magenta << "[" << i << "]  " << termcolor::reset;
  }
  std::cout << "\n";
}



template <class T>
void
Insercion (std::vector<T>& vector, unsigned size) {
  
  T aux;
  int j;
  for (auto i = 1; i < size; i++) {
    aux = vector[i];
    j = i;

    while ((aux < vector[j - 1]) && (j > 0)) {
      vector[j] = vector[j - 1];
      j--;
    }
    vector[j] = aux;
  }
}



template <class T>
void
AuxQuickSort (std::vector<T>& vector, unsigned ini, unsigned fin) {
  
  unsigned i = ini, f = fin;
  T pivote = vector[(i + f) / 2];

  while (i <= f) {
    while (vector[i] < pivote) i++;
    while (vector[f] > pivote) f--;
    if (i <= f) {
        T aux = vector[i];
        vector[i] = vector[f];
        vector[f] = aux;

        if (algoritmo) {
          std::cout << "\n///COLOCAMOS EL VALOR " << termcolor::blue << vector[i]
          << termcolor::reset <<" EN LA POSICION " << termcolor::magenta << i << 
          termcolor::reset << " Y EL VALOR " << termcolor::blue << vector[f] << 
          termcolor::reset <<" EN LA POSICION " << termcolor::magenta << f << 
          termcolor::reset << "\n";
          Mostrar<T>(vector);
        }

        i++;
        f--; 
    }
  }
  if (ini < f) AuxQuickSort<T> (vector, ini, f);
  if (i < fin) AuxQuickSort<T> (vector, i, fin);
}



template <class T>
void
QuickSort (std::vector<T>& vector, unsigned size) {

  AuxQuickSort<T>(vector, 0, size -1);
}



template <class T>
void
AuxShellSort (int d, std::vector<T>& vector, unsigned size) {
  
  T aux;
  int j;
  for (int i = d; i < size ; i++) {
    aux = vector[i];
    j = i;
    while ((j >= d) && (aux < vector[j-d])) {
      vector[j] = vector[j-d];
      if (algoritmo) {
        std::cout << "\n///COLOCAMOS EL VALOR " << termcolor::blue << vector[j] <<
        termcolor::reset << " EN LA POSICION " << termcolor::magenta << j 
        << termcolor::reset << "\n";

      }
      j = j - d;
    }
    vector[j] = aux;
    if (algoritmo) {
      std::cout << "\n///COLOCAMOS EL VALOR " << termcolor::blue << vector[j] <<
      termcolor::reset << " EN LA POSICION " << termcolor::magenta << j 
      << termcolor::reset << "\n";
      Mostrar<T>(vector);
    }
  }
}



template <class T>
void
ShellSort (std::vector<T>& vector, unsigned size) {

  int landa = size * 0.45454;
  AuxShellSort<T> (landa, vector, size);
  while (landa > 1) {

    landa = landa * 0.45454;
    AuxShellSort<T> (landa, vector, size);
  }
}



template<class T>
void
Seleccion (std::vector<T>& vector, unsigned size) {

  unsigned min;
  T aux;
  for (auto i = 0; i < size -1 ; i++) {
    min = i;
    for (auto j = i+1; j < size; j++)
      if (vector[j] < vector[min])
        min = j;

    aux = vector[min];
    vector[min] = vector[i];
    vector[i] = aux;

    if (algoritmo) {
      std::cout << "\n///COLOCAMOS EL VALOR " << termcolor::blue << aux <<
      termcolor::reset <<" EN LA POSICION " << termcolor::magenta << i
      << termcolor::reset << " Y COLOCAMOS EL VALOR " << termcolor::blue <<
      vector[min] << termcolor::reset << " EN LA POSICION " << termcolor::magenta
      << min << std::endl;
      Mostrar<T>(vector);
    }
  }
}



template <class T>
void
Mezcla (std::vector<T>& vector, unsigned ini, unsigned cent, unsigned fin) {

  unsigned i = ini, j = cent + 1, k = ini;
  std::vector<T> aux;
  aux.resize(vector.size());

  while (i <= cent && j <= fin) {
    if (vector[i] < vector[j]) {
        aux[k] = vector[i];
        i++;
    }
    else {
      aux[k] = vector[j];
      j++;
    }
  k ++;
  }
  if (i > cent)
    while (j <= fin) {
      aux[k] = vector[j];
      j++; k++;
    }
  else 
    while (i <= cent) {
      aux[k] = vector[i];
      i++; k++;
    }
  k = ini;
  for (; k <= fin; k++)
    vector[k] = aux[k];
}



template <class T>
void
AuxMergeSort (std::vector<T>& vector, unsigned ini, unsigned fin) {

  if (ini < fin) {
    unsigned cent = (ini + fin) / 2;
    AuxMergeSort<T> (vector, ini, cent);
    AuxMergeSort<T> (vector, cent+1, fin);
    Mezcla<T> (vector, ini, cent, fin);
  }
}



template <class T>
void
MergeSort (std::vector<T>& vector, unsigned size) {

  AuxMergeSort<T>(vector, 0, size -1);
}



template <class T>
void
Baja (int i, std::vector<T>& vector, int n) {

  unsigned h1, h2, h;
  while (2*i +1 <= n) {

    h1 = 2*i +1;
    h2 = 2*i +2;

    if (h1 == n || vector[h1] > vector[h2])
      h = h1;

    else 
      h = h2;

    if (vector[h] <= vector[i])
      break;

    else {
      T aux = vector[i];
      vector[i] = vector[h];
      vector[h] = aux;
      i = h;
    }
  }
}



template<class T>
void
HeapSort (std::vector<T>& vector, unsigned size) {

  for (int i = size/2; i >= 0; i--)
    Baja (i, vector, size -1);
  for (int i = size - 1; i > 0; i--) {
    T aux = vector[0];
    vector[0] = vector[i];
    vector[i] = aux;
    Baja (0, vector, i -1);
  }
}



/*
template <class T>
void
Baja (int i, std::vector<T>& vector, int n) {

  unsigned larg = i, h1 = 2*i +1, h2 = 2*i + 2;

  if(h1 < n && vector[h1] > vector[larg])
        larg = h1;

    if(h2 < n && vector[h2] > vector[larg])
        larg = h2;

    if(larg != i){
        T x = vector[i];
        vector[i] = vector[larg];
        vector[larg] = x;
        
        Baja(larg,vector,n);
    }
}



template<class T>
void
HeapSort (std::vector<T>& vector, unsigned size) {

  for (int i = (size/2) -1; i >= 0; i--)
    Baja (i, vector, size);

  for (int i = size - 1; i > 0; i--) {
    T aux = vector[0];
    vector[0] = vector[i];
    vector[i] = aux;
    Baja (0, vector, i);
  }
}
*/