#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <list>
#include <initializer_list>
#include "term.h" // Assuming Term is defined in this header

class Polynomial {
public:
    Polynomial();
    explicit Polynomial(int constant);
    Polynomial(std::initializer_list<Term> terms);

    // Additional functionality
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const; // If needed
    Polynomial operator/(const Term& divisor) const; // For division by a Term, not a full Polynomial
    bool operator!=(const Polynomial& other) const;

    int getCoeff(int power) const;
    int getDegree() const;

    // Iterator access
    using iterator = std::list<Term>::iterator;
    using const_iterator = std::list<Term>::const_iterator;

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    std::list<Term> terms;
    void normalize(); // Combine like terms and remove zero-coefficient terms
};

#endif // POLYNOMIAL_H
