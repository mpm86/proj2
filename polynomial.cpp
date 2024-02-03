#include "polynomial.h"
#include <algorithm>

using namespace std;

// Normalize the polynomial
void Polynomial::normalize() {
    terms.remove_if([](const Term& term) { return term.coefficient == 0; });
    if (!terms.empty()) {
        terms.sort([](const Term& a, const Term& b) { return a.power < b.power; });
    }
}

// Default constructor
Polynomial::Polynomial() {
    // Intentionally left empty
}

// Constructor for a linear or constant polynomial
Polynomial::Polynomial(int b, int a) {
    if (a != 0) terms.push_back(Term(a, 1));
    if (b != 0) terms.push_back(Term(b, 0));
    normalize();
}

// Constructor with an initializer list of terms
Polynomial::Polynomial(initializer_list<Term> termsList) : terms(termsList) {
    normalize();
}

// Get the coefficient of a term with a given power
int Polynomial::getCoeff(int power) const {
    auto it = find_if(terms.begin(), terms.end(), [power](const Term& term) { return term.power == power; });
    return it != terms.end() ? it->coefficient : 0;
}

// Get the degree of the polynomial
int Polynomial::getDegree() const {
    return terms.empty() ? -1 : terms.back().power;
}

// Add two polynomials
Polynomial Polynomial::operator+(const Polynomial& p) const {
    Polynomial result;
    auto it1 = terms.begin(), it2 = p.terms.begin();
    while (it1 != terms.end() && it2 != p.terms.end()) {
        if (it1->power == it2->power) {
            int sumCoeff = it1->coefficient + it2->coefficient;
            if (sumCoeff != 0) result.terms.push_back(Term(sumCoeff, it1->power));
            ++it1;
            ++it2;
        } else if (it1->power < it2->power) {
            result.terms.push_back(*it1++);
        } else {
            result.terms.push_back(*it2++);
        }
    }
    result.terms.insert(result.terms.end(), it1, terms.end());
    result.terms.insert(result.terms.end(), it2, p.terms.end());
    return result;
}

// Multiply polynomial by a scalar
Polynomial Polynomial::operator*(int scale) const {
    Polynomial result;
    for (const auto& term : terms) {
        result.terms.push_back(Term(term.coefficient * scale, term.power));
    }
    result.normalize();
    return result;
}

// Multiply polynomial by a term
Polynomial Polynomial::operator*(Term term) const {
    Polynomial result;
    for (const auto& t : terms) {
        result.terms.push_back(Term(t.coefficient * term.coefficient, t.power + term.power));
    }
    result.normalize();
    return result;
}

// Multiply polynomial by a scalar, altering this polynomial
void Polynomial::operator*=(int scale) {
    for (auto& term : terms) {
        term.coefficient *= scale;
    }
    normalize();
}

// Polynomial division (not implemented in this example)
Polynomial Polynomial::operator/(const Polynomial& p) const {
    // Division logic here
    return Polynomial(); // Placeholder
}

// Check if two polynomials are equal
bool Polynomial::operator==(const Polynomial& p) const {
    return terms == p.terms;
}

// Iterator functions implementation
Polynomial::iterator Polynomial::begin() { return terms.begin(); }
Polynomial::const_iterator Polynomial::begin() const { return terms.begin(); }
Polynomial::iterator Polynomial::end() { return terms.end(); }
Polynomial::const_iterator Polynomial::end() const { return terms.end(); }

// Output operator for Polynomial
ostream& operator<<(ostream& out, const Polynomial& p) {
    for (const auto& term : p.terms) {
        out << term << " ";
    }
    return out;
}

// Sanity check function (not implemented in this example)
bool Polynomial::sanityCheck() const {
    // Sanity check logic here
    return true; // Placeholder
}
