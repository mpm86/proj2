#include "polynomial.h"
#include <algorithm>

Polynomial::Polynomial() = default;

Polynomial::Polynomial(int constant) {
    if (constant != 0) {
        terms.emplace_back(constant, 0);
    }
}

Polynomial::Polynomial(std::initializer_list<Term> init_terms) : terms(init_terms) {
    normalize();
}

void Polynomial::normalize() {
    terms.sort([](const Term& a, const Term& b) { return a.power < b.power; });
    auto it = terms.begin();
    while (it != terms.end()) {
        auto next_it = std::next(it);
        if (next_it != terms.end() && it->power == next_it->power) {
            it->coefficient += next_it->coefficient;
            terms.erase(next_it);
        } else {
            if (it->coefficient == 0) {
                it = terms.erase(it);
            } else {
                ++it;
            }
        }
    }
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    // Implement addition
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    // Implement subtraction
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    // Implement multiplication if needed
}

Polynomial Polynomial::operator/(const Term& divisor) const {
    // Implement division by a Term
}

bool Polynomial::operator!=(const Polynomial& other) const {
    // Implement inequality check
}

int Polynomial::getCoeff(int power) const {
    for (const auto& term : terms) {
        if (term.power == power) return term.coefficient;
    }
    return 0;
}

int Polynomial::getDegree() const {
    if (terms.empty()) return -1;
    return terms.back().power;
}

Polynomial::iterator Polynomial::begin() { return terms.begin(); }
Polynomial::const_iterator Polynomial::begin() const { return terms.begin(); }
Polynomial::iterator Polynomial::end() { return terms.end(); }
Polynomial::const_iterator Polynomial::end() const { return terms.end(); }
