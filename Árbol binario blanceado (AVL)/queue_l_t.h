// g++ -g arbolAVL.cc -o arbol
// ./arbol

#pragma once

#include <iostream>
#include <cassert>

#include "dll_t.h"



template <class T>
class queue_l_t {
private:
	dll_t<T>    l_;

public:
	// constructor y destructor
	queue_l_t(void);
	~queue_l_t(void);

	bool empty(void) const;
	int size(void) const;

	// operaciones
	void push(const T& dato, int);
	void pop(void);
	const T& front1(void) const;
	const int front2(void) const;
	const T& back1(void) const;
	const int back2(void) const;

	void write(std::ostream& os = std::cout) const;
};



template<class T>
queue_l_t<T>::queue_l_t(void):
l_()
{}



template<class T>
queue_l_t<T>::~queue_l_t(void)
{}



template<class T>
bool
queue_l_t<T>::empty(void) const
{
	return l_.empty();
}


template<class T>
int
queue_l_t<T>::size(void) const
{
	return l_.get_size();		
}


template<class T>
void
queue_l_t<T>::push(const T& dato1, int dato2)
{
  dll_node_t<T>* node = new dll_node_t<T>(dato1, dato2);
  assert(node != NULL);
	l_.insert_head(node);
}



template<class T>
void
queue_l_t<T>::pop(void)
{
	assert(!empty());
	delete l_.extract_tail();
}



template<class T>
const T&
queue_l_t<T>::front1(void) const
{
	assert(!empty());
	return (l_.get_tail()->get_data1());
}



template<class T>
const int
queue_l_t<T>::front2(void) const
{
	assert(!empty());
	return (l_.get_tail()->get_data2());
}



template<class T>
const T&
queue_l_t<T>::back1(void) const
{
	assert(!empty());
	return (l_.get_head()->get_data1());
}



template<class T>
const int
queue_l_t<T>::back2(void) const
{
	assert(!empty());
	return (l_.get_head()->get_data2());
}