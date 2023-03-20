// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef PAIRT_H_
#define PAIRT_H_

#include <iostream>


template<class T> class PairT {
 public:
  // constructores
  PairT(void);
  PairT(T, int);

  // destructor
  ~PairT(void);

  // getters & setters
  T get_val(void) const;
  int get_inx(void) const;
  void set(T, int);

  // E/S
  std::istream& read(std::istream& is = std::cin);
  std::ostream& write(std::ostream& os = std::cout) const;

 private:
  T val_;
  int inx_;
};


template<class T> PairT<T>::PairT() : val_(), inx_(-1) {}

template<class T> PairT<T>::PairT(T val, int inx) : val_(val), inx_(inx) {}

template<class T> PairT<T>::~PairT() {}

template<class T> void PairT<T>::set(T val, int inx) {
  val_ = val;
  inx_ = inx;
}

template<class T> int PairT<T>::get_inx() const {
  return inx_;
}

template<class T> T PairT<T>::get_val() const {
  return val_;
}

template<class T> std::istream& PairT<T>::read(std::istream& is) {
  return is >> inx_ >> val_;
}

template<class T> std::ostream& PairT<T>::write(std::ostream& os) const {
  return os << "(" << inx_ << ":" << val_ << ")";
}

template<class T> std::ostream& operator<<(std::ostream& os,
					   const PairT<T>& p) {
  p.write(os);
  return os;
}

#endif  // PAIRT_H_
