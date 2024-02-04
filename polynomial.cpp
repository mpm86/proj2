#include "polynomial.h"
#include <algorithm>
#include <iostream>

using namespace std;

Polynomial::Polynomial() : degree(-1) {
}

Polynomial::Polynomial(int b, int a) : degree(1) {
    terms.emplace_back(b, 0);
    terms.emplace_back(a, 1);
    normalize();
}

Polynomial::Polynomial(std::initializer_list<Term> terms) : degree(-1), terms(terms) {
    normalize();
}

Polynomial::Polynomial(int nC, int coeff[]) : degree(nC - 1) {
    for (int i = 0; i < nC; ++i) {
        terms.emplace_back(coeff[i], i);
    }
    normalize();
}

int Polynomial::getCoeff(int power) const {
    if (power >= 0 && power <= degree) {
        auto it = terms.begin();
        while (it != terms.end()) {
            if (it->getPower() == power) {
                return it->getCoefficient();
            }
            ++it;
        }
        return 0;
    } else {
        return 0;
    }
}

int Polynomial::getDegree() const {
    return degree;
}

Polynomial Polynomial::operator+ (const Polynomial& p) const {
    if (degree == -1 || p.degree == -1) {
        return Polynomial();
    }

    int resultSize = max(degree + 1, p.degree + 1);
    int* resultCoefficients = new int[resultSize];

    for (int i = 0; i < resultSize; ++i) {
        resultCoefficients[i] = 0;
    }

    auto it1 = terms.begin();
    auto it2 = p.terms.begin();

    while (it1 != terms.end() && it2 != p.terms.end()) {
        int power1 = it1->getPower();
        int power2 = it2->getPower();

        if (power1 == power2) {
            resultCoefficients[power1] = it1->getCoefficient() + it2->getCoefficient();
            ++it1;
            ++it2;
        } else if (power1 < power2) {
            resultCoefficients[power1] = it1->getCoefficient();
            ++it1;
        } else {
            resultCoefficients[power2] = it2->getCoefficient();
            ++it2;
        }
    }

    while (it1 != terms.end()) {
        resultCoefficients[it1->getPower()] = it1->getCoefficient();
        ++it1;
    }

    while (it2 != p.terms.end()) {
        resultCoefficients[it2->getPower()] = it2->getCoefficient();
        ++it2;
    }

    Polynomial result(resultSize, resultCoefficients);
    delete[] resultCoefficients;

    return result;
}

Polynomial Polynomial::operator* (int scale) const {
    if (degree == -1) {
        return Polynomial();
    }

    Polynomial result(*this);

    for (Term& term : result.terms) {
        term.setCoefficient(term.getCoefficient() * scale);
    }

    result.normalize();
    return result;
}

Polynomial Polynomial::operator* (Term term) const {
    if (degree == -1) {
        return Polynomial();
    }

    int* results = new int[degree + 1 + term.getPower()];

    for (int i = 0; i < term.getPower(); ++i) {
        results[i] = 0;
    }

    for (auto it = terms.begin(); it != terms.end(); ++it) {
        results[it->getPower() + term.getPower()] = it->getCoefficient() * term.getCoefficient();
    }

    Polynomial result(degree + 1 + term.getPower(), results);
    delete[] results;
    return result;
}

void Polynomial::operator*= (int scale) {
    if (degree == -1) {
        return;
    }

    for (Term& term : terms) {
        term.setCoefficient(term.getCoefficient() * scale);
    }

    normalize();
}

Polynomial Polynomial::operator/ (const Polynomial& denominator) const {
    if (degree == -1 || denominator.degree == -1) {
        return Polynomial();
    }

    if (*this == Polynomial(0)) {
        return *this;
    }

    if (denominator.getDegree() > getDegree()) {
        return Polynomial();
    }

    int resultSize = degree - denominator.degree + 1;
    int* results = new int[resultSize];

    for (int i = 0; i < resultSize; ++i) {
        results[i] = 0;
    }

    Polynomial remainder = *this;

    for (int i = resultSize - 1; i >= 0; --i) {
        int remainder1stCoeff = remainder.getCoeff(i + denominator.getDegree());
        int denominator1stCoeff = denominator.getCoeff(denominator.getDegree());

        if (remainder1stCoeff % denominator1stCoeff == 0) {
            results[i] = remainder1stCoeff / denominator1stCoeff;
            Polynomial subtractor = denominator * Term(-results[i], i);
            remainder = remainder + subtractor;
        } else {
            break;
        }
    }

    if (remainder == Polynomial(0)) {
        Polynomial result(resultSize, results);
        delete[] results;
        return result;
    } else {
        delete[] results;
        return Polynomial();
    }
}

bool Polynomial::operator== (const Polynomial& p) const {
    if (degree != p.degree) {
        return false;
    }

    auto it1 = terms.begin();
    auto it2 = p.terms.begin();

    while (it1 != terms.end() && it2 != p.terms.end()) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }

    return (it1 == terms.end()) && (it2 == p.terms.end());
}

void Polynomial::normalize() {
    while (degree + 1 > 1 && terms.back().getCoefficient() == 0) {
        terms.pop_back();
        --degree;
    }
}

ostream& operator<< (ostream& out, const Polynomial& p) {
    if (p.degree == -1) {
        out << "Invalid Polynomial";
    } else {
        bool firstTerm = true;

        for (const Term& term : p.terms) {
            if (!firstTerm) {
                out << " + ";
            } else {
                firstTerm = false;
            }

            int coefficient = term.getCoefficient();
            int power = term.getPower();

            if (coefficient == 1) {
                if (power == 0) {
                    out << "1";
                }
            } else if (coefficient == -1) {
                out << "-";
                if (power == 0) {
                    out << "1";
                }
            } else {
                out << coefficient;
            }

            if (power > 0) {
                out << "x";
                if (power > 1) {
                    out << "^" << power;
                }
            }
        }

        if (firstTerm) {
            out << "could not factor: " << p;
        }
    }
    return out;
}

bool Polynomial::sanityCheck() const {
    for (auto it = terms.begin(); it != terms.end(); ++it) {
        if (it->getCoefficient() == 0) {
            return false;
        }
    }
    return true;
}
