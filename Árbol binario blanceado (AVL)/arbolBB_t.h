// g++ -g arbolAVL.cc -o arbol
// ./arbol

#pragma once

#include <iostream>

#include "queue_l_t.h"
#include "nodoBB_t.h"

template<class T>
class ArbolBB_t {

  public:
    ArbolBB_t () : raiz(NULL) {}
    ~ArbolBB_t() {Podar(raiz);} 

    virtual void Insertar(T clave_dada);
    bool BuscarC(T& clave);

    virtual void Eliminar (T clave_dada);

    void RecorridoN ();

  protected:
    NodoBB_t<T>* Buscar(T& clave_dada);
    NodoBB_t<T>* BuscarRama(NodoBB_t<T>* nodo, T clave_dada);

    void InsertarRama (NodoBB_t<T>* &nodo, T clave_dada);
    void EliminarRama (NodoBB_t<T>* &nodo, T clave_dada);

    virtual void Sustituye(NodoBB_t<T>* &eliminado, NodoBB_t<T>* &sust);



    void Podar (NodoBB_t<T>*);

    bool EsVacio(NodoBB_t<T> *nodo);
    bool EsHoja(NodoBB_t<T> *nodo);

    const int Tam();
    const int TamRama(NodoBB_t<T>* nodo);

    void Preorden(NodoBB_t<T> *nodo, T& clave, bool& aux);
    void Inorden(NodoBB_t<T> *nodo, T& clave, bool& aux);
    void Postorden(NodoBB_t<T> *nodo, T& clave, bool& aux);

    NodoBB_t<T> *raiz;
};



template<class T>
void ArbolBB_t<T>::Sustituye(NodoBB_t<T>* &eliminado, NodoBB_t<T>* &sust) {
  
  if (sust->der != NULL)
    Sustituye(eliminado, sust->der);
  else {
    eliminado->dato = sust->dato ;
    eliminado->clave = sust->clave ;
    eliminado = sust ;
    sust = sust->izq ;
  }
}



template<class T>
void ArbolBB_t<T>::EliminarRama (NodoBB_t<T>* &nodo, T clave_dada) {

  if (nodo == NULL) return;
  if (clave_dada < nodo->clave)
    EliminarRama(nodo->izq, clave_dada);
  else if (clave_dada > nodo->clave)
    EliminarRama(nodo->der, clave_dada);

  else { //clave_dada == nodo_clave
    NodoBB_t<T>* Eliminado = nodo;
    if (nodo->der == NULL) nodo = nodo->izq;
    else if (nodo->izq == NULL) nodo = nodo->der;
    else Sustituye(Eliminado, nodo->izq);
    delete (Eliminado);
  }
}



template<class T>
void ArbolBB_t<T>::Eliminar (T clave_dada) {

  EliminarRama(raiz, clave_dada);
}



template<class T>
void ArbolBB_t<T>::InsertarRama(NodoBB_t<T>* &nodo, T clave_dada) {

  if (nodo == NULL)
    nodo = new NodoBB_t<T>(clave_dada, clave_dada);
  else if (clave_dada < nodo->clave)
    InsertarRama(nodo->izq, clave_dada);
  else
    InsertarRama(nodo->der, clave_dada); 
}



template<class T>
void ArbolBB_t<T>::Insertar(T clave_dada) {

  InsertarRama(raiz, clave_dada);
}



template<class T>
bool
ArbolBB_t<T>::BuscarC(T& clave) {

  return Buscar(clave) != NULL;
}



template<class T>
NodoBB_t<T>* ArbolBB_t<T>::Buscar(T& clave_dada) {

  return BuscarRama(raiz, clave_dada);
}



template<class T>
NodoBB_t<T>* ArbolBB_t<T>::BuscarRama(NodoBB_t<T>* nodo, T clave_dada) {

  if (nodo == NULL)
    return NULL ;
  if (clave_dada == nodo->clave)
    return nodo ;
  if (clave_dada < nodo->clave )
    return BuscarRama(nodo->izq, clave_dada);
  return BuscarRama(nodo->der, clave_dada);
}




template<class T>
void ArbolBB_t<T>::Preorden(NodoBB_t<T> *nodo, T& clave, bool& aux) {

  if (nodo == NULL) return;
  std::cout << "Nodo a comprobar: " << nodo ->clave << std::endl;
  if (nodo ->clave == clave) {
    aux = true;
    std::cout << "¡¡¡ NODO ENCONTRADO !!!\n";
  }
  Preorden(nodo->izq, clave, aux);
  Preorden(nodo->der, clave, aux);
}



template<class T>
void ArbolBB_t<T>::Inorden(NodoBB_t<T> *nodo, T& clave, bool& aux) {

  if (nodo == NULL) return;
  Inorden(nodo->izq, clave, aux);
  std::cout << "Nodo a comprobar: " << nodo ->clave << std::endl;
  if (nodo ->clave == clave) {
    aux = true;
    std::cout << "¡¡¡ NODO ENCONTRADO !!!\n";
  }
  Inorden(nodo->der, clave, aux);
}



template<class T>
void ArbolBB_t<T>::Postorden(NodoBB_t<T> *nodo, T& clave, bool& aux) {

  if (nodo == NULL) return;
  Postorden(nodo->izq, clave, aux);
  Postorden(nodo->der, clave, aux);
  std::cout << "Nodo a comprobar: " << nodo ->clave << std::endl;
  if (nodo ->clave == clave) {
    aux = true;
    std::cout << "¡¡¡ NODO ENCONTRADO !!!\n";
  }
}



template<class T>
void ArbolBB_t<T>::RecorridoN () {
  
  std::cout << "\n";
  queue_l_t<NodoBB_t<T> *> cola;
  NodoBB_t<T> * nodo;
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
    if (nodo != NULL) std::cout << "[" << nodo->clave << "]";
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
operator <<(std::ostream& os, ArbolBB_t<T>& aux) {

  aux.RecorridoN();
  return os;
}



template<class T>
void 
ArbolBB_t<T>::Podar (NodoBB_t<T>* nodo) {

  if (nodo == NULL) return ;
    
  Podar(nodo->izq); // Podar subarbol izquierdo
  Podar(nodo->der); // Podar subarbol derecho

  delete nodo; // Eliminar nodo
  nodo = NULL;
}



template<class T>
bool 
ArbolBB_t<T>::EsVacio(NodoBB_t<T> *nodo) {
return nodo == NULL;
}



template<class T>
bool 
ArbolBB_t<T>::EsHoja(NodoBB_t<T> *nodo) {
return !nodo->der && !nodo->izq;
}



template<class T>
const int 
ArbolBB_t<T>::Tam() { return TamRama(raiz); }



template<class T>
const int 
ArbolBB_t<T>::TamRama(NodoBB_t<T>* nodo) {

  if (nodo == NULL) return 0 ;
  return (1 + TamRama(nodo->izq) + TamRama(nodo->der) );
}