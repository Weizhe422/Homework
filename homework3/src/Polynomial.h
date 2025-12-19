#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Chain.h"
#include <iostream>
using namespace std;

// ---- Term ----
struct Term {
    double coef;
    int exp;
    Term() : coef(0.0), exp(0) {}
    Term(double c, int e) : coef(c), exp(e) {}
};

// ---- Polynomial ----
class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend istream& operator>>(istream& is, Polynomial& poly);
private:
    Chain<Term> terms;
public:
    Polynomial() {}

    Polynomial(const Polynomial& other) {
        int index = 0;
        for (ChainIterator<Term> it = other.begin(); it != other.end(); ++it, ++index)
            terms.insert(index, *it);
    }

    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            AvailableList<Term>::getBack(terms.release());
            int index = 0;
            for (ChainIterator<Term> it = other.begin(); it != other.end(); ++it, ++index)
                terms.insert(index, *it);
        }
        return *this;
    }

    ~Polynomial() {
        AvailableList<Term>::getBack(terms.release());
    }

    ChainIterator<Term> begin() const { return terms.begin(); }
    ChainIterator<Term> end() const { return terms.end(); }

    void newTerm(double coef, int exp) {
        if (coef == 0) return;

        if (terms.begin() == terms.end()) {
            terms.insert(0, Term(coef, exp));
            return;
        }

        int index = 0;
        for (ChainIterator<Term> it = terms.begin(); it != terms.end(); ++it, ++index) {
            if (it->exp < exp) {
                terms.insert(index, Term(coef, exp));
                return;
            }
            else if (it->exp == exp) {
                it->coef += coef;
                return;
            }
        }
        terms.insert(index, Term(coef, exp));
    }

    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        ChainIterator<Term> it1 = begin();
        ChainIterator<Term> it2 = other.begin();
        while (it1 != end() && it2 != other.end()) {
            if (it1->exp > it2->exp) {
                result.newTerm(it1->coef, it1->exp);
                ++it1;
            }
            else if (it1->exp < it2->exp) {
                result.newTerm(it2->coef, it2->exp);
                ++it2;
            }
            else {
                double newCoef = it1->coef + it2->coef;
                if (newCoef != 0) result.newTerm(newCoef, it1->exp);
                ++it1;
                ++it2;
            }
        }
        while (it1 != end()) {
            result.newTerm(it1->coef, it1->exp);
            ++it1;
        }
        while (it2 != other.end()) {
            result.newTerm(it2->coef, it2->exp);
            ++it2;
        }
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        Polynomial negOther;
        for (ChainIterator<Term> it = other.begin(); it != other.end(); ++it)
            negOther.newTerm(-it->coef, it->exp);
        return (*this) + negOther;
    }

    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        for (ChainIterator<Term> it1 = begin(); it1 != end(); ++it1)
            for (ChainIterator<Term> it2 = other.begin(); it2 != other.end(); ++it2)
                result.newTerm(it1->coef * it2->coef, it1->exp + it2->exp);
        return result;
    }

    float Evaluate(float x) const {
        float result = 0.0f;
        for (ChainIterator<Term> it = begin(); it != end(); ++it) {
            float power = 1.0f;
            for (int i = 0; i < it->exp; ++i)
                power *= x;
            result += static_cast<float>(it->coef) * power;
        }
        return result;
    }
};

// ---- I/O operators ----
inline istream& operator>>(istream& is, Polynomial& poly) {
    int numTerms;
    if (!(is >> numTerms)) return is;
    for (int i = 0; i < numTerms; ++i) {
        double coef;
        int exp;
        cout << "輸入第" << i + 1 << "項的係數和指數:";
        is >> coef >> exp;
        poly.newTerm(coef, exp);
    }
    return is;
}

inline ostream& operator<<(ostream& os, const Polynomial& poly) {
    bool first = true;
    for (ChainIterator<Term> it = poly.begin(); it != poly.end(); ++it) {
        if (!first) os << " + ";
        first = false;
        os << it->coef << "x^" << it->exp;
    }
    if (first) os << "0";
    return os;
}

#endif
