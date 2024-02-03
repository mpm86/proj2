#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <initializer_list>
#include <list>
#include "term.h"

class Polynomial {
public:
    // Constructors
    Polynomial();
    Polynomial(int b, int a = 0);
    Polynomial(std::initializer_list<Term> terms);

    // Accessors
    int getCoeff(int power) const;
    int getDegree() const;

    // Arithmetic operations
    Polynomial operator+(const Polynomial& p) const;
    Polynomial operator*(int scale) const;
    Polynomial operator*(Term term) const;
    void operator*=(int scale);
    Polynomial operator/(const Polynomial& p) const;
    bool operator==(const Polynomial& p) const;

    // Iterator declarations
    using iterator = std::list<Term>::iterator;
    using const_iterator = std::list<Term>::const_iterator;

    // Iterator functions
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    std::list<Term> terms; // List of terms, in ascending order of power

    void normalize(); // Utility function to maintain polynomial in normal form

    // Friend declaration for output operator
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);

    // For use by instructor only
    bool sanityCheck() const;
};

// Output operator declaration
std::ostream& operator<<(std::ostream&, const Polynomial&);

#endif // POLYNOMIAL_H
