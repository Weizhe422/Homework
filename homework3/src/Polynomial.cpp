#include "Polynomial.h"
#include <cmath>

Polynomial::Polynomial() {
    head = AvailableList::getInstance().GetNode(0, -1);
    head->nextlink = head;
}

Polynomial::Polynomial(const Polynomial& a) {
    head = AvailableList::getInstance().GetNode(0, -1);
    head->nextlink = head;
    CopyFrom(a);
}

Polynomial::~Polynomial() {
    AvailableList::getInstance().ReturnList(head);
}

void Polynomial::CopyFrom(const Polynomial& a) {
    TermNode* curr = a.head->nextlink;
    while (curr != a.head) {
        InsertTerm(curr->coef, curr->exp);
        curr = curr->nextlink;
    }
}

const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) {
        TermNode* first = head->nextlink;
        if (first != head) {
            // 暫時將數據節點從 head 斷開
            TermNode* last = head;
            while (last->nextlink != head) last = last->nextlink;
            last->nextlink = nullptr; // 變成非循環
            AvailableList::getInstance().ReturnList(first);
            head->nextlink = head;
        }
        CopyFrom(a);
    }
    return *this;
}

void Polynomial::InsertTerm(int c, int e) {
    if (c == 0) return;
    TermNode* prev = head;
    TermNode* curr = head->nextlink;

    while (curr != head && curr->exp > e) {
        prev = curr;
        curr = curr->nextlink;
    }

    if (curr != head && curr->exp == e) {
        curr->coef += c;
        if (curr->coef == 0) {
            prev->nextlink = curr->nextlink;
            AvailableList::getInstance().ReturnNode(curr);
        }
    }
    else {
        TermNode* newNode = AvailableList::getInstance().GetNode(c, e);
        newNode->nextlink = curr;
        prev->nextlink = newNode;
    }
}

Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial res = *this;
    TermNode* currB = b.head->nextlink;
    while (currB != b.head) {
        res.InsertTerm(currB->coef, currB->exp);
        currB = currB->nextlink;
    }
    return res;
}

Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial res = *this;
    TermNode* currB = b.head->nextlink;
    while (currB != b.head) {
        res.InsertTerm(-(currB->coef), currB->exp);
        currB = currB->nextlink;
    }
    return res;
}

Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial res;
    for (TermNode* ai = head->nextlink; ai != head; ai = ai->nextlink) {
        for (TermNode* bj = b.head->nextlink; bj != b.head; bj = bj->nextlink) {
            res.InsertTerm(ai->coef * bj->coef, ai->exp + bj->exp);
        }
    }
    return res;
}

float Polynomial::Evaluate(float x) const {
    float total = 0;
    for (TermNode* curr = head->nextlink; curr != head; curr = curr->nextlink) {
        total += curr->coef * std::pow(x, curr->exp);
    }
    return total;
}

std::istream& operator>>(std::istream& is, Polynomial& x) {
    int n, c, e;
    if (!(is >> n)) return is;
    for (int i = 0; i < n; i++) {
        is >> c >> e;
        x.InsertTerm(c, e);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& x) {
    int count = 0;
    TermNode* curr = x.head->nextlink;
    while (curr != x.head) { count++; curr = curr->nextlink; }
    os << count;
    curr = x.head->nextlink;
    while (curr != x.head) {
        os << " " << curr->coef << " " << curr->exp;
        curr = curr->nextlink;
    }
    return os;
}
