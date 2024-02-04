#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <initializer_list>
#include <list>
#include "term.h"

class Polynomial {
public:
    Polynomial();
    Polynomial(int b, int a = 0);
    Polynomial(std::initializer_list<Term> terms);
    Polynomial(int nC, int coeff[]);
    int getCoeff(int power) const;
    int getDegree() const;
    Polynomial operator+ (const Polynomial& p) const;
    Polynomial operator* (int scale) const;
    Polynomial operator* (Term term) const;
    void operator*= (int scale);
    Polynomial operator/ (const Polynomial& denominator) const;
    bool operator== (const Polynomial& p) const;

private:
    int degree;
    std::list<Term> terms;
    void normalize();
    friend std::ostream& operator<< (std::ostream&, const Polynomial&);
    bool sanityCheck() const;
};

std::ostream& operator<< (std::ostream&, const Polynomial&);

inline Polynomial operator* (int by, const Polynomial& p) {
    return p * by;
}

inline bool operator!= (const Polynomial& p, const Polynomial& q) {
    return !(p == q);
}

#endif
