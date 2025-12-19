# 41343134
## 作業三 Polynomial + Available Lists
## 解題說明
實現對多項式的：加法 (+) , 減法 (-)  , 乘法 (*) , 把x的值帶入多項式裡面 , 動態輸入多項式
使用鏈結串列管理多項式項目，提高效率（可回收節點）

### 解題策略
1. ChainNode:建立一個通用的節點,只存儲必要的資料 + 指向下一個節點的指標
2. Chain:可以用基本的操作,例如:插入元素、刪除元素、遍歷
3. Interator迭代:可將複雜的判斷、迴圈簡化
4. AvailableList放所有可回收節點:可以把要用的元素放進去,要用的時候可以馬上取出,
                               相比跟 OS 要記憶體快速許多

## 程式實作
### IDE:
Microsoft Visual Studio Code C/C++

```Chain.h
//Chain.h
#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
using namespace std;

template <class T> class ChainNode;
template <class T> class ChainIterator;
template <class T> class Chain;
template <class T> class AvailableList;

// -------- ChainNode --------
template <class T>
class ChainNode {
    friend class Chain<T>;
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    T element;
    ChainNode<T>* next;
public:
    ChainNode() : next(nullptr) {}
    ChainNode(const T& elem) : element(elem), next(nullptr) {}
    ChainNode(const T& elem, ChainNode<T>* nextNode)
        : element(elem), next(nextNode) {
    }
    void setElement(const T& elem) { element = elem; }
    void setNext(ChainNode<T>* nextNode) { next = nextNode; }
};

// -------- ChainIterator --------
template <class T>
class ChainIterator {
private:
    ChainNode<T>* currentNode;
public:
    ChainIterator(ChainNode<T>* startNode = nullptr) : currentNode(startNode) {}

    T& operator*() const { return currentNode->element; }
    T* operator->() const { return &currentNode->element; }

    ChainIterator& operator++() {
        if (currentNode) currentNode = currentNode->next;
        return *this;
    }

    ChainIterator operator++(int) {
        ChainIterator old = *this;
        if (currentNode) currentNode = currentNode->next;
        return old;
    }

    bool operator!=(const ChainIterator& right) const {
        return currentNode != right.currentNode;
    }
    bool operator==(const ChainIterator& right) const {
        return currentNode == right.currentNode;
    }

    int operator-(const ChainIterator& right) const {
        int distance = 0;
        ChainNode<T>* temp = right.currentNode;
        while (temp != currentNode) {
            if (temp == nullptr) return -1;
            temp = temp->next;
            ++distance;
        }
        return distance;
    }
};

// -------- AvailableList --------
template <class T>
class AvailableList {
private:
    static ChainNode<T>* availableHead;
public:
    AvailableList() {}
    ~AvailableList() {
        while (availableHead) {
            ChainNode<T>* tmp = availableHead;
            availableHead = availableHead->next;
            delete tmp;
        }
    }

    static ChainNode<T>* getNode() {
        if (!availableHead) return nullptr;
        ChainNode<T>* nodeToReturn = availableHead;
        availableHead = availableHead->next;
        nodeToReturn->next = nullptr;
        return nodeToReturn;
    }

    static void getBack(ChainNode<T>* firstNode) {
        if (!firstNode) return;
        ChainNode<T>* current = firstNode;
        while (current->next) current = current->next;
        current->next = availableHead;
        availableHead = firstNode;
    }

    static bool isEmpty() { return availableHead == nullptr; }

    static ChainNode<T>* getOneNodeOrNew(const T& elem) {
        ChainNode<T>* node = getNode();
        if (!node) node = new ChainNode<T>(elem);
        else node->setElement(elem);
        return node;
    }
};

template <class T>
ChainNode<T>* AvailableList<T>::availableHead = nullptr;

// -------- Chain --------
template <class T>
class Chain {
    friend class ChainIterator<T>;
    friend class AvailableList<T>;
private:
    ChainNode<T>* head;
public:
    Chain() : head(nullptr) {}
    ~Chain() {
        ChainNode<T>* current = head;
        while (current != nullptr) {
            ChainNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    ChainNode<T>* release() {
        ChainNode<T>* oldHead = head;
        head = nullptr;
        return oldHead;
    }

    ChainIterator<T> begin() const { return ChainIterator<T>(head); }
    ChainIterator<T> end() const { return ChainIterator<T>(nullptr); }

    void insert(int idx, const T& element) {
        ChainNode<T>* newNode = AvailableList<T>::getNode();
        if (!newNode) newNode = new ChainNode<T>(element);
        else newNode->setElement(element);

        if (idx == 0 || head == nullptr) {
            newNode->next = head;
            head = newNode;
        }
        else {
            ChainNode<T>* prev = head;
            for (int i = 0; i < idx - 1 && prev != nullptr; ++i)
                prev = prev->next;

            if (prev != nullptr) {
                newNode->next = prev->next;
                prev->next = newNode;
            }
            else {
                // index 超出範圍，回收
                AvailableList<T>::getBack(newNode);
            }
        }
    }
};

#endif

```
```Polynomial.h
//Polynomial.h
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
```
```main.cpp
//main.cpp
#include <iostream>
#include "Polynomial.h"

using namespace std;

int main() {
    Polynomial A, B;
    float x;

    cout << "輸入A的項數:";
    cin >> A;
    cout << "輸入B的項數:";
    cin >> B;
    cout << "輸入x為多少:";
    cin >> x;

    cout << "A = " << A << '\n';
    cout << "B = " << B << '\n';

    cout << "A + B = " << (A + B) << '\n';
    cout << "A - B = " << (A - B) << '\n';
    cout << "A * B = " << (A * B) << '\n';

    cout << "A(" << x << ") = " << A.Evaluate(x) << '\n';

    return 0;
}



```
## 效能分析
### 時間複雜度：
| 操作 | 時間複雜度 | 空間複雜度 | 說明 |
|:-----|:---------:|:---------:|:-----|
| newTerm(coef, exp) | O(n) | O(1) | 平均插入位置 n/2 |
| operator+ | O((m+n)²) | O(m+n) | 可優化至 O(m+n) |
| operator- | O((m+n)²) | O(m+n) | 同加法 |
| operator* | O(m×n×(m+n)) | O(m×n) | 可優化至 O(m×n) |
| Evaluate(x) | O(n×d) | O(1) | d=平均指數 |
| 拷貝建構 | O(n²) | O(n) | 可優化至 O(n) |
| 賦值運算 | O(n²+m) | O(n) | 可優化至 O(n+m) |
| 解構 | O(n) | O(1) | 回收鏈表 |

## 測試與驗證
## 測試案例

### 測試一：基本多項式運算

| 步驟 | 輸入 | 輸出 |
|:-----|:-----|:-----|
| 輸入A的項數 | 3 | - |
| 第1項係數和指數 | 3, 2 | - |
| 第2項係數和指數 | 2, 1 | - |
| 第3項係數和指數 | 1, 0 | - |
| **多項式A** | - | **3x² + 2x + 1** |
| 輸入B的項數 | 2 | - |
| 第1項係數和指數 | 2, 1 | - |
| 第2項係數和指數 | 1, 0 | - |
| **多項式B** | - | **2x + 1** |
| 輸入x值 | 2 | - |

**運算結果：**

| 運算 | 算式 | 結果 |
|:-----|:-----|:-----|
| A + B | (3x²+2x+1) + (2x+1) | 3x² + 4x + 2 |
| A - B | (3x²+2x+1) - (2x+1) | 3x² + 0x + 0 |
| A × B | (3x²+2x+1) × (2x+1) | 6x³ + 7x² + 4x + 1 |
| A(2) | 3(2²) + 2(2) + 1 | 17 |

### 測試輸入
```
輸入A的項數:4
輸入第1項的係數和指數:4 3
輸入第2項的係數和指數:3 2
輸入第3項的係數和指數:2 1
輸入第4項的係數和指數:5 0
輸入B的項數:3
輸入第1項的係數和指數:2 3
輸入第2項的係數和指數:1 2
輸入第3項的係數和指數:5 1
輸入x為多少:2
```
### 測試輸出
```
A = 4x^3 + 3x^2 + 2x^1 + 5x^0
B = 2x^3 + 1x^2 + 5x^1
A + B = 6x^3 + 4x^2 + 7x^1 + 5x^0
A - B = 2x^3 + 2x^2 + -3x^1 + 5x^0
A * B = 8x^6 + 10x^5 + 27x^4 + 27x^3 + 15x^2 + 25x^1
A(2) = 53
```


## 申論及開發報告
### 申論
#### 資料結構設計
1.Term 結構

- 儲存多項式單項的資訊：係數 coef 與指數 exp。

- 範例：3x^2 → coef=3, exp=2。

2.ChainNode 節點

- 用於構建單向鏈結串列。

- 每個節點包含一個 Term 與下一個節點指標 next。

- 與 AvailableList 搭配，可重複使用節點，減少動態分配與釋放的開銷。

3.Chain 鏈結串列

- 封裝整個多項式項目的鏈表。

- 提供：

    - 插入項目（insert）

    - 釋放整個鏈表（release）

    - 迭代器遍歷（begin / end）

4.AvailableList 可用節點列表

- 管理已釋放但可重用的節點。

- 核心功能：

    - getNode()：取得可用節點

    - getBack(node)：回收節點

    - getOneNodeOrNew(elem)：取得節點或創建新節點

5.ChainIterator 迭代器

- 用於遍歷 Chain。

- 支援操作：*、->、++、==、!=。

- 方便在多項式運算中逐項操作。

6.Polynomial 類別

- 封裝多項式操作，核心成員為 Chain<Term>。

- 功能：

    - 新增項目 newTerm(coef, exp)，自動合併同指數項。

    - 運算符重載：+, -, *。

    - 計算多項式在某個 x 值的數值 Evaluate(x)。

### 結論

本次程式透過鏈結串列與可回收節點列表實現了多項式的動態管理和運算。
多項式的加、減、乘運算及在指定 x 值的求值功能都可正確執行，且利用迭代器與節點回收機制，提高了記憶體的使用效率。
程式的空間複雜度主要取決於多項式項數。整體而言，該程式設計具有資源管理效益，可作為多項式計算與鏈結串列應用的範例。
