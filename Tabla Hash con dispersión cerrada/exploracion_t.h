
#pragma once

#include "dispercion_t.h"

#include <cstdlib>

template<class Clave>
class FuncionExploracion {

  public:
    virtual unsigned operator()(const Clave& k, unsigned i) const = 0;
};



template<class Clave>
class feLineal: public FuncionExploracion<Clave> {
  
  public:
    feLineal () {};

    unsigned operator()(const Clave& k, unsigned i) const {
      return i;
    }
};



template<class Clave>
class feCuadratica: public FuncionExploracion<Clave> {
  
  public:
    feCuadratica () {};

    unsigned operator()(const Clave& k, unsigned i) const {
      return i * i;
    }
};



template<class Clave>
class feDobleDispersion: public FuncionExploracion<Clave> {
  
  public:
    feDobleDispersion (FuncionDispersion<unsigned>* fd) {fd_ = fd;}

    unsigned operator()(const Clave& k, unsigned i) const {
      return i * (*fd_)(k);
    }
  
  private:
    FuncionDispersion<unsigned>* fd_;
};



template<class Clave>
class feReDispersion: public FuncionExploracion<Clave> {
  
  public:
    feReDispersion (unsigned nSinonimo) { nSinonimo_ = nSinonimo;}

    unsigned operator()(const Clave& k, unsigned i) const {
      srand(k);

      unsigned aux;
      for (unsigned recorrido = 0; recorrido < i; recorrido++)
        aux = rand() % nSinonimo_;

      return aux;
    }

  private:
    unsigned nSinonimo_;
};