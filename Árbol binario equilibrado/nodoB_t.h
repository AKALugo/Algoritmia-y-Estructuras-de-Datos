// g++ -g arbolB.cc -o arbol
// ./arbol

#pragma once

template<class T>
class NodoB_t {

  public:
  // Constructor:
      NodoB_t (const T dat, NodoB_t<T> *izqu = NULL, NodoB_t<T> *dere = NULL) : dato(dat), izq(izqu), der(dere) {}

  // Miembros:
  T dato;
  NodoB_t<T> *izq;
  NodoB_t<T> *der;
};
