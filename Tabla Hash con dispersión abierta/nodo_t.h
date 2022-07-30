
#pragma once

#include <cassert>
#include <cstdio>
#include <utility> 

template <class T>
class NodoT
{
public:
  NodoT ();
  NodoT (const unsigned, const T&);

  ~NodoT (void);

  // getters & setters
  const T& getDato(void) const;
  const unsigned& getHash(void) const;
  T& getDato(void);
  unsigned& getHash(void);
  NodoT<T>* getNext(void) const;
  NodoT<T>* getPrev(void) const;

  void setDato(const T&);
  void setHash(const unsigned&);
  void setNext(NodoT<T>*);
  void setPrev(NodoT<T>*);

private:
  NodoT<T>* previo_;
  T  dato_;
  unsigned hash_;
  NodoT<T>* siguiente_;
};



template <class T>
NodoT<T>::NodoT():
previo_(NULL),
dato_(),
siguiente_(NULL)
{}



template <class T>
NodoT<T>::NodoT(const unsigned hash, const T& data):
previo_(NULL),
dato_(data),
hash_(hash),
siguiente_(NULL)
{}



template <class T>
NodoT<T>::~NodoT(void)
{
  previo_ = NULL;
  siguiente_ = NULL;
}



template <class T>
const T&
NodoT<T>::getDato(void) const
{
  return dato_;
}



template <class T>
const unsigned&
NodoT<T>::getHash(void) const
{
  return hash_;
}



template <class T>
T&
NodoT<T>::getDato(void) {

  return dato_;
}



template <class T>
unsigned&
NodoT<T>::getHash(void) {

  return hash_;
}



template <class T>
NodoT<T>*
NodoT<T>::getNext(void) const
{
  return siguiente_;
}



template <class T>
NodoT<T>*
NodoT<T>::getPrev(void) const
{
  return previo_;
}



template <class T>
void
NodoT<T>::setDato(const T& dato)
{
  dato_= dato;
}



template <class T>
void
NodoT<T>::setHash(const unsigned& hash)
{
  hash_= hash;
}



template <class T>
void
NodoT<T>::setNext(NodoT<T>* siguiente)
{
  siguiente_ = siguiente;
}



template <class T>
void
NodoT<T>::setPrev(NodoT<T>* previo)
{
  previo_ = previo;
}