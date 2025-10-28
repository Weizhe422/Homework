#include <iostream>
#include <algorithm> // for std::copy
#include <cmath>     // for pow()
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream &output, const Polynomial &Poly);
private:
    int exp;   // 指數
    float coef; // 係數
};

class Polynomial { 
private:
    Term *termArray;  // 儲存多項式各項
    int capacity;     // 陣列容量
    int terms;        // 實際項數
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }
    ~Polynomial() { delete[] termArray; }

    Polynomial Add(Polynomial b);   // 加法
    Polynomial Mult(Polynomial b);  // 乘法
    float Eval(float x);            // 代入 x 求值
    void newTerm(const float newcoef, const int newexp); // 新增項目

    friend istream& operator>>(istream &input, Polynomial &Poly);
    friend ostream& operator<<(ostream &output, const Polynomial &Poly);
};

//------------------- operator >> -------------------
istream& operator>>(istream& is, Polynomial& poly) {
    float coef;
    int exp, n;
    cout << "Enter number of terms: ";
    is >> n;
    cout << "Enter coefficient and exponent for each term:\n";
    while (n--) {
        is >> coef >> exp;
        poly.newTerm(coef, exp);
    }
    return is;
}

//------------------- operator << -------------------
ostream& operator<<(ostream& os, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        if (i > 0 && poly.termArray[i].coef >= 0)
            os << " + ";
        else if (poly.termArray[i].coef < 0)
            os << " ";
        os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
    }
    return os;
}

//------------------- Add Function -------------------
Polynomial Polynomial::Add(Polynomial b) {
    Polynomial c;
    int aPos = 0, bPos = 0;

    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }

    for (; aPos < terms; aPos++)
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);

    for (; bPos < b.terms; bPos++)
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}

//------------------- Mult Function -------------------
Polynomial Polynomial::Mult(Polynomial b) {
    Polynomial c;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < b.terms; j++) {
            float newCoef = termArray[i].coef * b.termArray[j].coef;
            int newExp = termArray[i].exp + b.termArray[j].exp;

            bool found = false;
            for (int k = 0; k < c.terms; k++) {
                if (c.termArray[k].exp == newExp) {
                    c.termArray[k].coef += newCoef;
                    found = true;
                    break;
                }
            }
            if (!found)
                c.newTerm(newCoef, newExp);
        }
    }

    return c;
}

//------------------- Eval Function -------------------
float Polynomial::Eval(float x) {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(x, termArray[i].exp);
    }
    return result;
}

//------------------- newTerm Function -------------------
void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef == 0) return;
    if (terms == capacity) {
        capacity *= 2;
        Term *temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoef;
    termArray[terms++].exp = theExp;
}

//------------------- main -------------------
int main() {
    Polynomial p1, p2, sum, prod;
    float x;

    cout << "=== Input Polynomial 1 ===\n";
    cin >> p1;
    cout << "Polynomial 1: " << p1 << endl;

    cout << "\n=== Input Polynomial 2 ===\n";
    cin >> p2;
    cout << "Polynomial 2: " << p2 << endl;

    sum = p1.Add(p2);
    cout << "\nSum = " << sum << endl;

    prod = p1.Mult(p2);
    cout << "Product = " << prod << endl;

    cout << "\nEnter x to evaluate Polynomial 1: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}
