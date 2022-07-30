// g++ -g arbolB.cc -o arbol
// ./arbol

#pragma once

#include <iostream>

#include "queue_l_t.h"
#include "nodoB_t.h"

template<class T>
class ArbolB_t {

  public:
    ArbolB_t () : raiz(NULL) {}
    ~ArbolB_t() {Podar(raiz);} 

    void InsertaEquil(const T dato);
    bool Buscar(T& clave);

    void RecorridoN ();

  private:
    void Podar (NodoB_t<T>*);

    bool EsVacio(NodoB_t<T> *nodo);
    bool EsHoja(NodoB_t<T> *nodo);
    const bool Equilibrado();
    const bool EquilibrioRama(NodoB_t<T> *nodo);

    const int Tam();
    const int TamRama(NodoB_t<T>* nodo);

    void InsertaEquilRama (const T dato, NodoB_t<T>* nodo);
    void Preorden(NodoB_t<T> *nodo, T& dato, bool& aux);
    void Inorden(NodoB_t<T> *nodo, T& dato, bool& aux);
    void Postorden(NodoB_t<T> *nodo, T& dato, bool& aux);

    NodoB_t<T> *raiz;

};



template<class T>
void ArbolB_t<T>::Preorden(NodoB_t<T> *nodo, T& dato, bool& aux) {

  if (nodo == NULL) return;
  std::cout << "Nodo a comprobar: " << nodo ->dato << std::endl;
  if (nodo ->dato == dato) {
    aux = true;
    std::cout << "¡¡¡ NODO ENCONTRADO !!!\n";
  }
  Preorden(nodo->izq, dato, aux);
  Preorden(nodo->der, dato, aux);
}



template<class T>
void ArbolB_t<T>::Inorden(NodoB_t<T> *nodo, T& dato, bool& aux) {

  if (nodo == NULL) return;
  Inorden(nodo->izq, dato, aux);
  std::cout << "Nodo a comprobar: " << nodo ->dato << std::endl;
  if (nodo ->dato == dato) {
    aux = true;
    std::cout << "¡¡¡ NODO ENCONTRADO !!!\n";
  }
  Inorden(nodo->der, dato, aux);
}



template<class T>
void ArbolB_t<T>::Postorden(NodoB_t<T> *nodo, T& dato, bool& aux) {

  if (nodo == NULL) return;
  Postorden(nodo->izq, dato, aux);
  Postorden(nodo->der, dato, aux);
  std::cout << "Nodo a comprobar: " << nodo ->dato << std::endl;
  if (nodo ->dato == dato) {
    aux = true;
    std::cout << "¡¡¡ NODO ENCONTRADO !!!\n";
  }
}



template<class T>
void ArbolB_t<T>::RecorridoN () {
  
  std::cout << "\n";
  queue_l_t<NodoB_t<T> *> cola;
  NodoB_t<T> * nodo;
  int nivel, nivel_actual = 0;

  cola.push(raiz, 0);
  std::cout << "\nNivel " << 0 << ": ";

  while (!cola.empty()) {
    nodo = cola.front1();
    nivel = cola.front2();
    cola.pop();

    if (nivel > nivel_actual) {
      nivel_actual = nivel;
      std::cout << "\nNivel " << nivel_actual << ": ";
    }
    if (nodo != NULL) std::cout << "[" << nodo->dato << "]";
    else              std::cout << "[.]";
    
    if (nodo != NULL) {
      cola.push(nodo->izq, nivel+1);
      cola.push(nodo->der, nivel+1);
    }
  }
  std::cout << "\n\n";
}



template<class T>
std::ostream& 
operator <<(std::ostream& os, ArbolB_t<T>& aux) {

  aux.RecorridoN();
  return os;
}



template<class T>
void 
ArbolB_t<T>::Podar (NodoB_t<T>* nodo) {

  if (nodo == NULL) return ;
    
  Podar(nodo->izq); // Podar subarbol izquierdo
  Podar(nodo->der); // Podar subarbol derecho

  delete nodo; // Eliminar nodo
  nodo = NULL;
}



template<class T>
bool 
ArbolB_t<T>::EsVacio(NodoB_t<T> *nodo) {
return nodo == NULL;
}



template<class T>
bool 
ArbolB_t<T>::EsHoja(NodoB_t<T> *nodo) {
return !nodo->dcho && !nodo->izdo;
}



template<class T>
const bool ArbolB_t<T>::Equilibrado() {return EquilibrioRama(raiz);}



template<class T>
const bool ArbolB_t<T>::EquilibrioRama(NodoB_t<T> *nodo) {

  if (nodo == NULL) return true ;

  int eq = TamRama(nodo->izdo) - TamRama(nodo->dcho);
  switch (eq) {
    case -1:
    case 0:
    case 1:
      return EquilibrioRama(nodo->izdo) && EquilibrioRama(nodo->dcho);
    default: return false;
  }
}



template<class T>
const int 
ArbolB_t<T>::Tam() { return TamRama(raiz); }



template<class T>
const int 
ArbolB_t<T>::TamRama(NodoB_t<T>* nodo) {

  if (nodo == NULL) return 0 ;
  return (1 + TamRama(nodo->izq) + TamRama(nodo->der) );
}



template<class T>
void 
ArbolB_t<T>::InsertaEquil(const T dato) {

  if (raiz == NULL)
    raiz = new NodoB_t<T>(dato, NULL, NULL);
  else InsertaEquilRama(dato, raiz);
}



template<class T>
void ArbolB_t<T>::InsertaEquilRama(const T dato, NodoB_t<T>* nodo) {

  if (TamRama(nodo->izq) <= TamRama(nodo->der)) {
    if (nodo->izq != NULL)
      InsertaEquilRama(dato, nodo->izq);
    else
      nodo->izq = new NodoB_t<T>(dato, NULL, NULL);
  }

  else {
    if (nodo->der != NULL)
      InsertaEquilRama(dato, nodo->der);
    else
      nodo->der = new NodoB_t<T>(dato, NULL, NULL);
  }
}



template<class T>
bool
ArbolB_t<T>::Buscar(T& clave) {

  bool aux = false;

  Preorden(raiz, clave, aux);
  if (!aux)
  std::cout << "¡¡¡ VALOR NO ENCONTRADO !!!\n";
  return aux;
}
