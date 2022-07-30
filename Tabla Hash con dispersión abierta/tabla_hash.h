
#pragma once

#include "dispercion_t.h"
#include "lista_t.h"

#include <vector>

template <class Clave>
class TablaHash {

  public:
    TablaHash (const unsigned capacidad, FuncionDispersion<unsigned>* fd);
    ~TablaHash ();

    bool Buscar(unsigned& hash);
    bool Insertar(unsigned& hash);
    void Insertar(unsigned& hash, Clave& valor);
    Clave& Retornar (unsigned& hash);
    int Contador ();

  private:
    unsigned capacidad_;
    std::vector<ListaT<Clave>> vector_;
    FuncionDispersion<unsigned>* fd_;
};



template<class Clave>
TablaHash<Clave>::TablaHash(const unsigned capacidad, FuncionDispersion<unsigned>* fd) {

  capacidad_ = capacidad;
  fd_ = fd;
  vector_.resize (capacidad);
}



template<class Clave>
TablaHash<Clave>::~TablaHash() {}



template<class Clave>
bool
TablaHash<Clave>::Buscar(unsigned& hash) {

  unsigned aux = (*fd_)(hash);
  return vector_[aux].Buscar(hash);
}



template<class Clave>
bool
TablaHash<Clave>::Insertar(unsigned& hash) {

  unsigned aux = (*fd_)(hash);
  return vector_[aux].Insertar(hash);
}


template<class Clave>
void
TablaHash<Clave>::Insertar(unsigned& hash, Clave& valor) {

  if (Insertar(hash)) {
    unsigned aux = (*fd_)(hash);
    NodoT<Clave>* aux_ins = new NodoT<Clave> (hash, valor);
    vector_[aux].InsertarCola(aux_ins);
  }
}


template<class Clave>
Clave&
TablaHash<Clave>::Retornar(unsigned& hash) {

  unsigned aux;
  aux = (*fd_)(hash);
  return vector_[aux].Devolver(hash);
}



template<class Clave>
int 
TablaHash<Clave>::Contador () {

  int aux=0;

  for (unsigned i = 0; i < vector_.size(); i++)
    if (vector_[i].getSize() > aux)
      aux = vector_[i].getSize();

  return aux;

}