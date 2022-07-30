
#pragma once

#include "exploracion_t.h"
#include "dispercion_t.h"
#include "vector_t.h"

#include <vector>

template <class Clave>
class TablaHash {

  public:
    TablaHash (const unsigned capacidad, const unsigned nSinonimo, 
               FuncionExploracion<unsigned>* fe, FuncionDispersion<unsigned>* fd);
    ~TablaHash ();

    bool Buscar(unsigned& hash, Clave& valor);
    bool Insertar(unsigned& hash, Clave& valor);

  private:
    unsigned capacidad_;
    unsigned nSinonimo_;
    std::vector<VectorT<Clave>> vector_;
    FuncionDispersion<unsigned>* fd_;
    FuncionExploracion<unsigned>* fe_;
};



template<class Clave>
TablaHash<Clave>::TablaHash(const unsigned capacidad, const unsigned nSinonimo, 
               FuncionExploracion<unsigned>* fe, FuncionDispersion<unsigned>* fd) {

  fd_ = fd;
  capacidad_ = capacidad;
  nSinonimo_ = nSinonimo_;
  fe_ = fe;
  vector_.resize (capacidad);

  for (unsigned aux = 0; aux < capacidad; aux++)
    vector_[aux].Resize(nSinonimo_);
}



template<class Clave>
TablaHash<Clave>::~TablaHash() {}



template<class Clave>
bool
TablaHash<Clave>::Buscar(unsigned& hash, Clave& valor) {
  
  unsigned fd_calculo = (*fd_)(hash);
  unsigned fe_calculo;
  unsigned contador = 1;

  if (vector_[fd_calculo].Buscar(hash)) {
    
    vector_[fd_calculo].Devolver(hash, valor);
    return true;
  }
  if (!vector_[fd_calculo].Lleno() && !vector_[fd_calculo].Buscar(hash))
    return false;

  while (contador < capacidad_) {
    fe_calculo = (*fe_)(hash, fd_calculo);

    if (vector_[(fe_calculo + fd_calculo) % capacidad_].Buscar(hash)) {
      vector_[(fe_calculo + fd_calculo) % capacidad_].Devolver(hash, valor);
      return true;
    }

    if (!vector_[(fe_calculo + fd_calculo) % capacidad_].Lleno() && !vector_[(fe_calculo + fd_calculo) % capacidad_].Buscar(hash))
      return false;

    fd_calculo ++;
    contador++;
  }
  return false;
}



template<class Clave>
bool
TablaHash<Clave>::Insertar(unsigned& hash, Clave& valor) {

  unsigned fd_calculo = (*fd_)(hash);
  unsigned fe_calculo;
  unsigned contador = 1;

  if (!vector_[fd_calculo].Lleno() && vector_[fd_calculo].Insertar(hash)) {
    vector_[fd_calculo].Insertar(hash, valor);
    return true;
  }

  if (vector_[fd_calculo].Buscar(hash))
    return false;

  while (contador < capacidad_) {
    fe_calculo = (*fe_)(hash, fd_calculo);

    if (!vector_[(fe_calculo + fd_calculo) % capacidad_].Lleno() && vector_[(fe_calculo + fd_calculo) % capacidad_].Insertar(hash)) {
      vector_[(fe_calculo + fd_calculo) % capacidad_].Insertar(hash, valor);
      return true;
    }
    
    if (vector_[(fe_calculo + fd_calculo) % capacidad_].Buscar(hash))
      return false;

    fd_calculo ++;
    contador++;
  }
  return false;
}