// g++ -g arbolAVL.cc -o arbol
// ./arbol

#include "arbolBB_t.h"
#include "nodoBB_t.h"

template<class T>
class ArbolAVL_t : public ArbolBB_t<T> {
  
  public:
    void Insertar(T ClaveDada);
    void Eliminar(T clave_dada);

    bool Traza{false};

  private:
    void Eliminar_re_balancea_dcha (NodoBB_t<T>* &nodo, bool& decrece);
    void Eliminar_re_balancea_izda (NodoBB_t<T>* &nodo, bool& decrece);

    void Sustituye(NodoBB_t<T>* &eliminado, NodoBB_t<T>* &sust, bool &decrece);

    void Elimina_rama(NodoBB_t<T>* &nodo, T ClaveDada, bool& decrece);

    void Inserta_bal(NodoBB_t<T>*  &nodo, NodoBB_t<T>*  nuevo, bool& crece);

    void Insert_re_balancea_izda(NodoBB_t<T>* &nodo, bool& crece);
    void Insert_re_balancea_dcha(NodoBB_t<T>* &nodo, bool& crece);

    void Rotacion_II (NodoBB_t<T>* &nodo);
    void Rotacion_DD (NodoBB_t<T>* &nodo);
    void Rotacion_ID (NodoBB_t<T>* &nodo);
    void Rotacion_DI (NodoBB_t<T>* &nodo);
};


template<class T>
void ArbolAVL_t<T>::Eliminar_re_balancea_dcha (NodoBB_t<T>* &nodo, bool& decrece) {

  switch (nodo->bal) {
    case 1:
      {
      if (Traza) {
        std::cout<< "Desbalanceado:\n";
        this->RecorridoN();
      }
      NodoBB_t<T>* nodo1 = nodo->izq;
      if (nodo1->bal < 0) Rotacion_ID(nodo);
      else
        if (nodo1->bal == 0) decrece = false;
        Rotacion_II(nodo);
      }
    break ;
    case 0: nodo->bal = 1;
      decrece = false;
      break;
    case -1: nodo->bal = 0;
  }
}



template<class T>
void ArbolAVL_t<T>::Eliminar_re_balancea_izda (NodoBB_t<T>* &nodo, bool& decrece) {

  switch (nodo->bal) {
    case -1: {
    std::cout<< "Desbalanceado:\n";
    this->RecorridoN();
    NodoBB_t<T>* nodo1 = nodo->der;
    if (nodo1->bal > 0) Rotacion_DI(nodo);
    else {
      if (nodo1->bal == 0) decrece = false;
      Rotacion_DD(nodo);
    }
    }
    break;
    case 0:
      nodo->bal = -1;
      decrece = false;
    break;
    case 1: nodo->bal = 0;
  }
}



template<class T>
void ArbolAVL_t<T>::Sustituye(NodoBB_t<T>* &eliminado, NodoBB_t<T>* &sust, bool &decrece) {

  if (sust->der != NULL) {
    Sustituye(eliminado, sust->der, decrece);
    if (decrece) Eliminar_re_balancea_dcha(sust, decrece);
  }
  else {
    eliminado->dato = sust->dato;
    eliminado->clave = sust->clave;
    eliminado = sust;
    sust = sust->izq;
    decrece = true;
  }
}



template<class T>
void ArbolAVL_t<T>::Elimina_rama(NodoBB_t<T>* &nodo, T clave_dada, bool& decrece) {

  if (nodo == NULL) return;
  if (clave_dada < nodo->clave) {
    Elimina_rama(nodo->izq,clave_dada,decrece);
    if (decrece)
    Eliminar_re_balancea_izda(nodo,decrece);
  }
  else if (clave_dada > nodo->clave) {
    Elimina_rama(nodo->der,clave_dada,decrece);
    if (decrece)
    Eliminar_re_balancea_dcha(nodo,decrece);
  }
  else { // nodo->clave == clave_dada(encontrado)
    NodoBB_t<T>* eliminado = nodo;
    if (nodo->izq == NULL) {
      nodo = nodo->der;
      decrece = true;
    }
    else if (nodo->der == NULL) {
      nodo = nodo->izq;
      decrece = true;
    }
    else {
      Sustituye(eliminado,nodo->izq,decrece);
      if (decrece) Eliminar_re_balancea_izda(nodo,decrece);
    }
  delete eliminado; 
  }
}



template<class T>
void ArbolAVL_t<T>::Eliminar(T clave_dada) {

  bool decrece = false;
  Elimina_rama(this->raiz, clave_dada, decrece);
}



template<class T>
void ArbolAVL_t<T>::Insert_re_balancea_izda(NodoBB_t<T>* &nodo, bool& crece) {

  switch (nodo->bal) {
    case -1: nodo->bal = 0;
      crece = false;
    break;
    case 0: nodo->bal = 1 ;
    break;
    case 1: 
      if (Traza) {
        std::cout<< "Desbalanceado:\n";
        this->RecorridoN();
      }
      NodoBB_t<T>* nodo1 = nodo->izq;
      if (nodo1->bal == 1) Rotacion_II(nodo);
      else Rotacion_ID(nodo);
      crece = false;
  }
}



template<class T>
void ArbolAVL_t<T>::Insert_re_balancea_dcha(NodoBB_t<T>* &nodo, bool& crece) {

  switch (nodo->bal) {
    case 1: nodo->bal = 0;
      crece = false;
    break;
    case 0: nodo->bal = -1;
    break;
    case -1:
      if (Traza) {
        std::cout<< "Desbalanceado:\n";
        this->RecorridoN();
      }
      NodoBB_t<T>* nodo1 = nodo->der;
      if (nodo1->bal == -1) Rotacion_DD(nodo);
      else Rotacion_DI(nodo);
      crece = false;
  }
}



template<class T>
void ArbolAVL_t<T>::Inserta_bal(NodoBB_t<T>*  &nodo,NodoBB_t<T>*  nuevo, bool& crece) {

  if (nodo == NULL) {
    nodo = nuevo;
    crece = true;
  }
  else if (nuevo->clave < nodo->clave) {
    Inserta_bal(nodo->izq,nuevo,crece);
    if (crece) Insert_re_balancea_izda(nodo, crece);
  }
  else {
    Inserta_bal(nodo->der,nuevo,crece);
    if (crece) Insert_re_balancea_dcha(nodo, crece);
  }
}



template<class T>
void 
ArbolAVL_t<T>::Insertar(T ClaveDada) {

  NodoBB_t<T>* nuevo = new NodoBB_t<T> (ClaveDada, ClaveDada);
  bool crece = false;
  Inserta_bal(this->raiz, nuevo, crece); 
}



template<class T>
void 
ArbolAVL_t<T>::Rotacion_II (NodoBB_t<T>* &nodo) {

  if (Traza)
    std::cout << "Rotacion II [" << nodo->clave << "]\n";

  NodoBB_t<T>* nodo1 = nodo->izq;
  nodo->izq = nodo1->der;
  nodo1->der = nodo;
  if (nodo1->bal == 1) {
    nodo->bal = 0;
    nodo1->bal = 0;
  }
  else { // nodo1->bal == 0
    nodo->bal = 1;
    nodo1->bal = -1;
  }
  nodo = nodo1;
}



template<class T>
void 
ArbolAVL_t<T>::Rotacion_DD (NodoBB_t<T>* &nodo) {

  if (Traza)
    std::cout << "Rotacion DD [" << nodo->clave << "]\n";

  NodoBB_t<T>* nodo1 = nodo->der;
  nodo->der = nodo1->izq;
  nodo1->izq = nodo ;
  if (nodo1->bal == -1) {
    nodo->bal = 0;
    nodo1->bal = 0;
  }
  else { // nodo1->bal == 0
    nodo->bal = -1;
    nodo1->bal = 1;
  }
  nodo = nodo1; 
}



template<class T>
void 
ArbolAVL_t<T>::Rotacion_ID (NodoBB_t<T>* &nodo) {

  if (Traza)
    std::cout << "Rotacion ID [" << nodo->clave << "]\n";

  NodoBB_t<T>* nodo1 = nodo->izq;
  NodoBB_t<T>* nodo2 = nodo1->der;
  nodo->izq = nodo2->der;
  nodo2->der = nodo;
  nodo1->der = nodo2->izq;
  nodo2->izq = nodo1;

  if (nodo2->bal == -1) nodo1->bal = 1;
  else nodo1->bal = 0;
  if (nodo2->bal == 1) nodo->bal = -1;
  else nodo->bal = 0;

  nodo2->bal = 0;
  nodo = nodo2;
}



template<class T>
void 
ArbolAVL_t<T>::Rotacion_DI (NodoBB_t<T>* &nodo) {

  if (Traza)
    std::cout << "Rotacion DI [" << nodo->clave << "]\n";

  NodoBB_t<T>* nodo1 = nodo->der;
  NodoBB_t<T>* nodo2 = nodo1->izq;
  nodo->der = nodo2->izq;
  nodo2->izq = nodo;
  nodo1->izq = nodo2->der;
  nodo2->der = nodo1;

  if (nodo2->bal == 1) nodo1->bal = -1;
  else nodo1->bal = 0;
  if (nodo2->bal == -1) nodo->bal = 1;
  else nodo->bal = 0;

  nodo2->bal = 0;
  nodo = nodo2;
}



template<class T>
std::ostream& 
operator <<(std::ostream& os, ArbolAVL_t<T>& aux) {

  aux.RecorridoN();
  return os;
}