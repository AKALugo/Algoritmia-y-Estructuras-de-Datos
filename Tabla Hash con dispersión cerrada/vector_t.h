
#pragma once

#include <cassert>

#include <cstdio>
#include <vector>


template <class T>
class VectorT {

public:
  VectorT (int n=0);
  ~VectorT ();

  bool Buscar(unsigned&);
  bool Insertar (unsigned& X);
  bool Lleno() const;

  void Insertar (const unsigned& hash, T&);
  void Resize (unsigned n);

  void Devolver (unsigned hash, T&);
private:
  std::vector<std::pair<unsigned,T>> vector_;
  unsigned nSinonimos_{0};
};



template<class T>
VectorT<T>::VectorT (int n) {

  vector_.resize(n);
}



template<class T>
VectorT<T>::~VectorT () {}



template<class T>
bool
VectorT<T>::Buscar(unsigned& X) {

  for (unsigned aux = 0; aux < vector_.size(); aux++) 
    if (vector_[aux].first == X)
      return true;
  
  return false;
}



template<class T>
bool
VectorT<T>::Insertar (unsigned& X) {

  if (Buscar(X))
    return false;
  
  return true;
}



template<class T>
bool
VectorT<T>::Lleno() const {

  if (nSinonimos_ == vector_.size())
    return true;
  
  return false;
}


template<class T>
void 
VectorT<T>::Resize (unsigned n) {

  vector_.resize(n);
}


template<class T>
void
VectorT<T>::Insertar(const unsigned& hash, T& valor) {

  vector_[nSinonimos_].first = hash;
  vector_[nSinonimos_].second = valor;
  nSinonimos_++;
}



template<class T>
void
VectorT<T>::Devolver (unsigned hash, T& valor) {

  for (unsigned aux = 0; aux < nSinonimos_; aux++)
    if (vector_[aux].first == hash)
      valor = vector_[aux].second;
}