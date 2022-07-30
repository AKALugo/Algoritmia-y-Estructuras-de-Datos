// g++ -g arbolB.cc -o arbol
// ./arbol

#pragma once

#include <cassert>
#include <iostream>
#include <cstdio>


template <class T>
class dll_node_t
{
public:
  dll_node_t();         // constructor por defecto
  dll_node_t(const T&, int); // constructor

  ~dll_node_t(void);    // destructor

  // getters & setters
  const T& get_data1(void) const;
  const int get_data2(void) const;
  dll_node_t<T>* get_next(void) const;
  dll_node_t<T>* get_prev(void) const;

  void set_data(const T&, int);
  void set_next(dll_node_t<T>*);
  void set_prev(dll_node_t<T>*);

  // E/S
  std::ostream& write(std::ostream& = std::cout) const;

private:
  dll_node_t<T>* prev_;
  T              data1_;
  int            data2_;
  dll_node_t<T>* next_;
};



template <class T>
dll_node_t<T>::dll_node_t():
prev_(NULL),
data1_(),
data2_(),
next_(NULL)
{}



template <class T>
dll_node_t<T>::dll_node_t(const T& data1, int data2) :
prev_(NULL),
data1_(data1),
data2_(data2),
next_(NULL)
{}



template <class T>
dll_node_t<T>::~dll_node_t(void)
{
  prev_ = NULL;
  next_ = NULL;
}



template <class T>
const T&
dll_node_t<T>::get_data1(void) const
{
  return data1_;
}



template <class T>
const int
dll_node_t<T>::get_data2(void) const
{
  return data2_;
}



template <class T>
dll_node_t<T>*
dll_node_t<T>::get_next(void) const
{
  return next_;
}



template <class T>
dll_node_t<T>*
dll_node_t<T>::get_prev(void) const
{
  return prev_;
}



template <class T>
void
dll_node_t<T>::set_data(const T& data1, int data2)
{
  data1_ = data1;
  data2_ = data2;
}



template <class T>
void
dll_node_t<T>::set_next(dll_node_t<T>* next)
{
  next_ = next;
}



template <class T>
void
dll_node_t<T>::set_prev(dll_node_t<T>* prev)
{
  prev_ = prev;
}