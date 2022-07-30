#pragma once

#include <cassert>
#include <cstdio>

#include "nodo_t.h"

template <class T>
class ListaT {

public:
  // constructor, constructor de copia y destructor
  ListaT(void);
  ListaT(const ListaT<T>&);
  ~ListaT(); 
  
  // opeardor de asignación
  ListaT<T>& operator=(const ListaT<T>&);
  
  // getters
  NodoT<T>* getCola(void) const;
  NodoT<T>* getCabeza(void) const;
  int getSize(void) const;
  bool Vacio(void) const;

  // operaciones
  void InsertarCabeza(NodoT<T>*);
  void InsertarCola(NodoT<T>*);

  NodoT<T>* ExtraerCabeza(void);
  NodoT<T>* ExtraerCola(void);

  void Eliminar(NodoT<T>*);

private:
  NodoT<T>* cabeza_;
  NodoT<T>* cola_;
  int       size_;
};



template <class T>
ListaT<T>::ListaT(void) :
cabeza_(NULL),
cola_(NULL),
size_(0)
{}



// constructor de copia
template<class T>
ListaT<T>::ListaT(const ListaT<T>& l)
{
  *this = l; // invocamos directamente al operator=
}



template <class T>
ListaT<T>::~ListaT(void)
{
  NodoT<T>* aux = NULL;

  while (cabeza_ != NULL) {
    aux = cabeza_;
    cabeza_ = cabeza_->getNext();
    delete aux;
    aux = NULL;
  }
  size_ = 0;
  cabeza_ = cola_ = NULL;
}



// operador de asignación
template<class T>
ListaT<T>&
ListaT<T>::operator=(const ListaT<T>& l)
{
  while (getSize())
    delete ExtraerCabeza();
  
  NodoT<T>* aux = l.cabeza_;

  while (aux != NULL) {
    NodoT<T>* nodo = new NodoT<T> (aux->getHash(), aux->getDato());
    assert(nodo != NULL);
    InsertarCola(nodo);
    aux = aux ->getNext();
  }
  return *this;
}



template <class T>
NodoT<T>*
ListaT<T>::getCabeza(void) const
{
  return cabeza_;
}



template <class T>
NodoT<T>*
ListaT<T>::getCola(void) const
{
  return cola_;
}


template <class T>
int
ListaT<T>::getSize(void) const
{
  return size_;
}



template <class T>
bool
ListaT<T>::Vacio(void) const
{
  if (cabeza_ == NULL) {
    assert(cola_ == NULL);
    assert(size_ == 0);
    return true;
  } else return false;
}



template <class T>
void
ListaT<T>::InsertarCabeza(NodoT<T>* nodo)
{
  assert(nodo != NULL);

  if (Vacio()) {
    cabeza_ = nodo;
    cola_ = cabeza_;
  } else {
    cabeza_->setPrev(nodo);
    nodo->setNext(cabeza_);
    cabeza_ = nodo;
  }
  size_++;
}



template <class T>
void
ListaT<T>::InsertarCola(NodoT<T>* nodo)
{
  assert(nodo != NULL);

  if (Vacio()) {
    cabeza_ = nodo;
    cola_ = cabeza_;
  } else {
    cola_->setNext(nodo);
    nodo->setPrev(cola_);
    cola_ = nodo;
  }

  size_++;
}



template <class T>
NodoT<T>*
ListaT<T>::ExtraerCola(void)
{
  assert(!Vacio());

  NodoT<T>* aux = cola_;

  cola_ = cola_->getPrev();
  
  if (cola_ != NULL) cola_->setNext(NULL);
  else               cabeza_ = NULL;

  size_--;
  
  aux->setNext(NULL);
  aux->setPrev(NULL);
  
  return aux;
}



template <class T>
NodoT<T>*
ListaT<T>::ExtraerCabeza(void)
{
  assert(!Vacio());

  NodoT<T>* aux = cabeza_;

  cabeza_ = cabeza_->getNext();

  if (cabeza_ != NULL) cabeza_->setPrev(NULL);
  else                 cola_ = NULL;

  size_--;

  aux->setNext(NULL);
  aux->setPrev(NULL);

  return aux;
}



template <class T>
void
ListaT<T>::Eliminar(NodoT<T>* nodo)
{
  assert(nodo != NULL);

  if (nodo->getPrev() != NULL)
    nodo->getPrev()->setNext(nodo->getNext());
  else
    cabeza_ = nodo->getNext();

  if (nodo->getNext() != NULL)
    nodo->getNext()->setPrev(nodo->getPrev());
  else
    cola_ = nodo->getPrev();

  delete nodo;

  size_--;

}