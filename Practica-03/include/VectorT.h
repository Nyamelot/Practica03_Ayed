// AUTOR: José Ángel Portillo García
// FECHA: 18/03/2023
// EMAIL: alu0101568232@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef VECTORT_H_
#define VECTORT_H_

#include <iostream>
#include <cassert>

template<class T> class VectorT {
 public:
  // constructores
  VectorT(const int = 0);
  VectorT(const VectorT&); // constructor de copia

  // operador de asignación
  VectorT<T>& operator=(const VectorT<T>&);

  // destructor
  ~VectorT();
  
  // getters
  T get_val(const int) const;
  int get_size(void) const;
  
  // setters
  void set_val(const int, const T);
  
  // getters-setters
  T& at(const int);
  T& operator[](const int);
  
  // getters constantes
  const T& at(const int) const;
  const T& operator[](const int) const;

  // Redimensionado
  void resize(const int);
  
  // E/S
  void read(std::istream& = std::cin);
  void write(std::ostream& = std::cout) const;

 private:
  T *v_;
  int sz_;
  
  void build(void);
  void destroy(void);
};


template<class T> VectorT<T>::VectorT(const int n) : v_(NULL), sz_(n) {
  build();
}

// constructor de copia
template<class T> VectorT<T>::VectorT(const VectorT<T>& w)
    : v_(NULL), sz_(0) {
  *this = w; // se invoca directamente al operator=
}

// operador de asignación
template<class T> VectorT<T>& VectorT<T>::operator=(const VectorT<T>& w) {
  resize(w.get_size());
  for (int i = 0; i < get_size(); i++)
    at(i) = w.at(i);
  
  return *this;
}

template<class T> VectorT<T>::~VectorT() {
  destroy();
}

template<class T> void VectorT<T>::build() {
  v_ = NULL;
  if (sz_ != 0) {
    v_ = new T[sz_];
    assert(v_ != NULL);
  }
}

template<class T> void VectorT<T>::destroy() {
  if (v_ != NULL) {
    delete[] v_;
    v_ = NULL;
  }
  sz_ = 0;
}

template<class T> void VectorT<T>::resize(const int n) {
  destroy();
  sz_ = n;
  build();
}

template<class T> inline T VectorT<T>::get_val(const int i) const {
  assert(i >= 0 && i < get_size());
  return v_[i];
}

template<class T> inline int VectorT<T>::get_size() const {
  return sz_;
}

template<class T> void VectorT<T>::set_val(const int i, const T d) {
  assert(i >= 0 && i < get_size());
  v_[i] = d;
}

template<class T> T& VectorT<T>::at(const int i) {
  assert(i >= 0 && i < get_size());
  return v_[i];
}

template<class T> T& VectorT<T>::operator[](const int i) {
  return at(i);
}

template<class T> const T& VectorT<T>::at(const int i) const {
  assert(i >= 0 && i < get_size());
  return v_[i];
}

template<class T> const T& VectorT<T>::operator[](const int i) const {
  return at(i);
}

template<class T> void VectorT<T>::read(std::istream& is) {
  is >> sz_;
  resize(sz_);
  for (int i = 0; i < sz_; i++)
    is >> at(i);
}

template<class T> void VectorT<T>::write(std::ostream& os) const {
  os << get_size() << ": [ ";
  for (int i = 0; i < get_size(); i++)
    os << at(i) << (i != get_size() - 1 ? "\t" : "");
  os << " ]" << std::endl;
}

template<class T> std::istream& operator>>(std::istream& is, VectorT<T>& v) {
  v.read(is);
  return is;
}

template<class T> std::ostream& operator<<(std::ostream& os,
					   const VectorT<T>& v) {
  v.write(os);
  return os;
}

#endif  // VECTORT_H_
