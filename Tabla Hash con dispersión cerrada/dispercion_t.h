
#pragma once

#include <cstdlib>

template<class Clave>
class FuncionDispersion {

  public:
    virtual unsigned operator()(const Clave& k) const = 0;
};



template<class Clave>
class fdModulo: public FuncionDispersion<Clave> {

  public:
    fdModulo (const unsigned n): cantidad_datos_(n){}

    virtual unsigned operator()(const Clave& k) const {

      return k % cantidad_datos_;
    }

  private:
    unsigned cantidad_datos_;
};



template<class Clave>
class fdPseudoAleatoria: public FuncionDispersion<Clave> {

  public:
    fdPseudoAleatoria (const unsigned n): cantidad_datos_(n){}

    virtual unsigned operator()(const Clave& k) const {

      srand(k);
      return rand() % cantidad_datos_;
    }

  private:
    unsigned cantidad_datos_;
};
