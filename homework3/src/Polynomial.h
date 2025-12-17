#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "TermNode.h"
#include "AvailableList.h"
#include <iostream>

class Polynomial {
private:
    TermNode* head; // 指向循環鏈結串列的標頭節點 (Header Node)

    // 內部輔助函數
    void InsertTerm(int c, int e); // 按指數遞減順序插入或合併項
    void CopyFrom(const Polynomial& a); // 深度複製另一個多項式的內容

public:
    Polynomial();                          // 預設建構子
    Polynomial(const Polynomial& a);       // (c) 複製建構子
    ~Polynomial();                         // (e) 解構子
    const Polynomial& operator=(const Polynomial& a); // (d) 賦值運算子

    // 算術運算子
    Polynomial operator+(const Polynomial& b) const; // (f) 加法
    Polynomial operator-(const Polynomial& b) const; // (g) 減法
    Polynomial operator*(const Polynomial& b) const; // (h) 乘法
    float Evaluate(float x) const;                  // (i) 求值

    // 友元函數處理 I/O
    friend std::istream& operator>>(std::istream& is, Polynomial& x); // (a) 輸入
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& x); // (b) 輸出
};

#endif
