// AUTOR: José Ángel Portillo García
// FECHA: 18/03/2023
// EMAIL: alu0101568232@ull.edu.es
// VERSION: 1.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 3
// ESTILO: Google C++ Style Guide
// COMENTARIOS:
// 

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "VectorT.h"
#include "SparseVectorT.h"

// Clase para polinomios basados en vectores densos de doubles
class Polynomial : public VectorT<double> {
 public:
  // constructores
  Polynomial(const int n = 0) : VectorT<double>(n) {};
  Polynomial(const Polynomial& pol)
      : VectorT<double>(pol) {}; // constructor de copia

  // destructor
  ~Polynomial() {};

  // E/S
  void Write(std::ostream& = std::cout, const double eps = EPS) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
 };


// Clase para polinomios basados en vectores dispersos
class SparsePolynomial : public SparseVectorT {
 public:
  // constructores
  SparsePolynomial(const int n = 0) : SparseVectorT(n) {};
  SparsePolynomial(const Polynomial& pol) : SparseVectorT(pol) {};
  SparsePolynomial(const SparsePolynomial&);  // constructor de copia

  // destructor
  ~SparsePolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SparsePolynomial&, const double = EPS) const;
  bool IsEqual(const Polynomial&, const double = EPS) const;
};

// E/S
void Polynomial::Write(std::ostream& os, const double eps) const {
  os << get_size() << ": [ ";
  bool first{true};
  for (int i{0}; i < get_size(); i++)
    if (IsNotZero(at(i), eps)) {
      os << (!first ? " + " : "") << at(i)
	 << (i > 1 ? " x^" : (i == 1) ? " x" : "");
      if (i > 1)
	os << i;
      first = false;
    }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
  p.Write(os);
  return os;
}

// Operaciones con polinomios

// Evaluación de un polinomio representado por vector denso
double Polynomial::Eval(const double x) const {
  double result{0.0};
  for (int i = 0; i < get_size(); i++) {
    result += at(i) * pow(x, i);
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por vectores densos
bool Polynomial::IsEqual(const Polynomial& pol, const double eps) const {
  bool differents = false;
  SparsePolynomial true_pol_1(*this);
  SparsePolynomial true_pol_2(pol);
  if (true_pol_1.get_nz() != true_pol_2.get_nz()) return differents;
  for (int i = 0; i < true_pol_1.get_nz(); i++) {
    if (!(fabs(true_pol_1.at(i).get_val() - true_pol_2.at(i).get_val()) < eps)
      && true_pol_1.at(i).get_inx() != true_pol_2.at(i).get_inx()) {
      return differents;
    }
  }
  return !differents;
}

// constructor de copia
SparsePolynomial::SparsePolynomial(const SparsePolynomial& spol) {
  *this = spol;   // se invoca directamente al operator=
}

// E/S
void SparsePolynomial::Write(std::ostream& os) const {
  os << get_n() << "(" << get_nz() << "): [ ";
  bool first{true};
  for (int i{0}; i < get_nz(); i++) {
    int inx{at(i).get_inx()};
    os << (!first ? " + " : "") << at(i).get_val()
       << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SparsePolynomial& p) {
  p.Write(os);
  return os;
}

// Operaciones con polinomios

// Evaluación de un polinomio representado por vector disperso
double SparsePolynomial::Eval(const double x) const {
  double result{0.0};
  for (int i = 0; i < get_nz(); i++) {
    result += at(i).get_val() * pow(x, at(i).get_inx());
  }
  return result;
}



// Comparación si son iguales dos polinomios representados por vectores dispersos
bool SparsePolynomial::IsEqual(const SparsePolynomial& spol
			       , const double eps) const {
  bool differents = false;
  if(get_nz() != spol.get_nz()) return differents;
  for (int i = 0; i < get_nz(); i++) {
    if (!(fabs(at(i).get_val() - spol.at(i).get_val()) < eps) && at(i).get_inx() != spol.at(i).get_inx()) {
      return differents;
    }
  }
  return !differents;
}

// Comparación si son iguales dos polinomios representados por
// vector disperso y vector denso
bool SparsePolynomial::IsEqual(const Polynomial& pol, const double eps) const {
  bool differents = false;
  SparsePolynomial real_pol (pol);
  if(get_nz() != real_pol.get_nz()) return differents;
  for (int i = 0; i < get_nz(); i++) {
    if (!(fabs(at(i).get_val() - real_pol.at(i).get_val()) < eps) && at(i).get_inx() != real_pol.at(i).get_inx()) {
      return differents;
    }
  }
  return !differents;
}

// Modificacion
void PotenciasPares(const SparsePolynomial& spar) {
  for (int i = 0; i < spar.get_nz(); i++) {
    if (spar.at(i).get_inx() % 2 == 0) {
      std::cout << spar.at(i).get_val() << std::endl;
    }
  }
}


#endif  // POLYNOMIAL_H_
