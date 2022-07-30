// g++ -g arbolAVL.cc -o arbol
// ./arbol

#pragma once

template<class T>
class NodoBB_t {

  public:
    // Constructor:
    NodoBB_t (T dat, T cl, NodoBB_t<T> *iz=NULL, NodoBB_t<T> *de=NULL) : dato(dat),
           clave(cl), izq(iz), der(de) {}
  // Miembros:
    T dato;
    T clave;
    int bal = 0;
    NodoBB_t<T> *izq;
    NodoBB_t<T> *der;
};
