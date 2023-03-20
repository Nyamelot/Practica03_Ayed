// AUTOR: 
// FECHA: 
// EMAIL: 
// VERSION: 4.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef SPARSE_VECTORT_H_
#define SPARSE_VECTORT_H_

#include <iostream>
#include <math.h>  // fabs

#include "VectorT.h"
#include "PairT.h"

#define EPS 1.0e-6

typedef PairT<double> pair_double_t;
typedef VectorT<pair_double_t> pair_vector_t;

class SparseVectorT {
 public:
  // constructores
  SparseVectorT(const int = 0);
  SparseVectorT(const VectorT<double>&,
                const double = EPS); // constructor normal
  SparseVectorT(const SparseVectorT&);  // constructor de copia

  // operador de asignación
  SparseVectorT& operator=(const SparseVectorT&);

  // destructor
  ~SparseVectorT();
  
  // getters
  int get_nz(void) const;
  int get_n(void) const;

  // getters-setters
  pair_double_t& at(const int);
  pair_double_t& operator[](const int);
  
  // getters constantes
  const pair_double_t& at(const int) const;
  const pair_double_t& operator[](const int) const;

  // E/S
  void write(std::ostream& = std::cout) const;

 private:
  pair_vector_t pv_;  // valores + índices
  int nz_;            // nº de valores distintos de cero = tamaño del vector
  int n_;             // tamaño del vector original

  // bool IsNotZero(const double, const double = EPS) const;
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

SparseVectorT::SparseVectorT(const int n) : pv_(n), nz_(0), n_(n) {}

// FASE II
SparseVectorT::SparseVectorT(const VectorT<double>& v, const double eps)
    : pv_(), nz_(0), n_(0) {
  for (int i = 0; i < v.get_size(); i++) {
    if (IsNotZero(v.at(i))) {
      nz_++;
    }
  }
  pv_.resize(nz_);
  int j = 0;
  for (int i = 0; i < nz_; i++) {
    if (IsNotZero(v.at(i))) {
      pair_double_t pair{v[i], i};
      pv_[j] = pair;
      ++j;
    }
  }
}

// constructor de copia
SparseVectorT::SparseVectorT(const SparseVectorT& w) {
  *this = w;  // se invoca directamente al operator=
}

// operador de asignación
SparseVectorT& SparseVectorT::operator=(const SparseVectorT& w) {
  nz_ = w.get_nz();
  n_ = w.get_n();
  pv_ = w.pv_;

  return *this;
}

SparseVectorT::~SparseVectorT() {}

inline int SparseVectorT::get_nz() const {
  return nz_;
}

inline int SparseVectorT::get_n() const {
  return n_;
}

pair_double_t& SparseVectorT::at(const int i) {
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

pair_double_t& SparseVectorT::operator[](const int i) {
  return at(i);
}

const pair_double_t& SparseVectorT::at(const int i) const {
  assert(i >= 0 && i < get_nz());
  return pv_[i];
}

const pair_double_t& SparseVectorT::operator[](const int i) const {
  return at(i);
}

// E/S
void SparseVectorT::write(std::ostream& os) const {
  os << get_n() << "(" << get_nz() << "): [ ";
  for (int i = 0; i < get_nz(); i++)
    os << pv_[i] << " ";
	os << "]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SparseVectorT& sv) {
  sv.write(os);
  return os;
}


#endif  // SPARSE_VECTORT_H_
