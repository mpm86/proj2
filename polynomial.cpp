#include "polynomial.h"
#include <algorithm>

// Normalize the polynomial: combine like terms and remove zero-coefficient terms
void Polynomial::normalize() {
    terms.sort([](const Term& a, const Term& b) { return a.power < b.power; }); // Sort terms by power
    auto it = terms.begin();
    while (it != terms.end()) {
        auto next_it = std::next(it);
        if (next_it != terms.end() && it->power == next_it->power) {
            it->coefficient += next_it->coefficient; // Combine like terms
            terms.erase(next_it);
        } else {
            if (it->coefficient == 0) {
                it = terms.erase(it); // Remove zero-coefficient terms
            } else {
                ++it;
            }
        }
    }
}

// Default constructor
Polynomial::Polynomial() {}

// Constructor for constant polynomials
Polynomial::Polynomial(int constant) {
    if (constant != 0) {
        terms.push_back(Term(constant, 0));
    }
}

// Constructor from an initializer list of terms
Polynomial::Polynomial(std::initializer_list<Term> init_terms) : terms(init_terms) {
    normalize();
}

// Get the coefficient of a specific power
int Polynomial::getCoeff(int power) const {
    for (const auto& term : terms) {
        if (term.power == power) return term.coefficient;
    }
    return 0; // Power not found
}

// Get the highest power of the polynomial
int Polynomial::getDegree() const {
    if (terms.empty()) return -1;
    return terms.back().power;
}

// Addition of two polynomials
Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result;
    auto it1 = terms.begin(), it2 = other.terms.begin();
    while (it1 != terms.end() && it2 != other.terms.end()) {
        if (it1->power == it2->power) {
            result.terms.push_back(Term(it1->coefficient + it2->coefficient, it1->power));
            ++it1;
            ++it2;
        } else if (it1->power < it2->power) {
            result.terms.push_back(*it1++);
        } else {
            result.terms.push_back(*it2++);
        }
    }
    result.terms.insert(result.terms.end(), it1, terms.end());
    result.terms.insert(result.terms.end(), it2, other.terms.end());
    result.normalize();
    return result;
}

// Polynomial multiplication (not implemented here)
Polynomial Polynomial::operator*(const Polynomial& other) const {
    // Implement polynomial multiplication logic
    return Polynomial();
}

// Polynomial subtraction (not implemented here)
Polynomial Polynomial::operator-(const Polynomial& other) const {
    // Implement polynomial subtraction logic
    return Polynomial();
}

// Output operator for polynomials
std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    for (const auto& term : p.terms) {
        os << (term.coefficient > 0 ? "+" : "") << term.coefficient << "x^" << term.power << " ";
    }
    return os;
}
