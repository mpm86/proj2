#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <initializer_list>
#include <list>

#include "term.h"

class Polynomial {
public:
  using iterator = std::list<Term>::iterator;
  using const_iterator = std::list<Term>::const_iterator;

  Polynomial();
  Polynomial(int b, int a = 0);
  Polynomial(std::initializer_list<Term> terms);
  Polynomial(int nCoeff, int coeff[]);
  int getCoeff(int power) const;
  int getDegree() const;
  Polynomial operator+ (const Polynomial& p) const;
  Polynomial operator* (int scale) const;
  Polynomial operator* (Term term) const;
  void operator*= (int scale);
  Polynomial operator/ (const Polynomial& p) const;
  bool operator== (const Polynomial& p) const;

  iterator begin() { return terms.begin(); }
  iterator end() { return terms.end(); }
  const_iterator begin() const { return terms.begin(); }
  const_iterator end() const { return terms.end(); }

private:
  int degree;
  std::list<Term> terms;
  void normalize();
  friend std::ostream& operator<< (std::ostream&, const Polynomial&);

public:
  bool sanityCheck() const;
};

std::ostream& operator<< (std::ostream&, const Polynomial&);
inline Polynomial operator* (int by, const Polynomial& p) { return p * by; }
inline bool operator!= (const Polynomial& p, const Polynomial& q) { return !(p == q); }

#endif
