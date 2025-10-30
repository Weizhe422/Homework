# 41343134
## 作業二 Polynomial
## 解題說明
本題要把「多項式」這個資料結構做成一個 C++ 類別，能讀、能印、能做基本運算
例如：輸入項 (2,3), (4,1), (5,0) 應輸出 2x^3 + 4x + 5
### 需求
- 可以輸入多項式的內容，每一項都要輸入「係數」和「指數」。
- 要能計算多項式的「加法」和「乘法」
- 可以代入 x 的值來算結果
- 輸出的格式要好看
### 解題策略
以物件導向為核心這些:

- Term和Polynomial類別
- 多項式加法 Add()
- 多項式乘法 Mult()
- 多項式求值 Eval(x)
## 程式實作
### IDE:
Microsoft Visual Studio Code C/C++

```cpp
#include <iostream>
#include <algorithm> // for std::copy
#include <cmath>     // for pow()
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
private:
    int exp;   // 指數
    float coef; // 係數
};

class Polynomial {
private:
    Term* termArray;  // 儲存多項式各項
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

    friend istream& operator>>(istream& input, Polynomial& Poly);
    friend ostream& operator<<(ostream& output, const Polynomial& Poly);
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
        Term* temp = new Term[capacity];
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
	system("pause");

    return 0;
}
```
## 效能分析
1. 時間複雜度：

    Newterms: $O(1)$   當發生重新配置時 $O(t)$（t =terms)

    Add: $O(n + m)$   以兩指標線性尋找兩個已排序的 term 陣列

    Mult: $O(n * m^2)$   當 m ≈ n 時，最壞情況為 $O(n^3)$

    Eval: $O(n)$   不改變多項式本身，僅常數空間

    Newterms（單次）：均攤  $O(1)$

2. 空間複雜度：

    Newterms: $O(1)$   當須擴充陣列時會配置一個新陣列 Term[capacity*2]，此時短暫同時存在新舊陣列，峰值為 $O(t)$ ，如果長期使用的空間是 O(t)（termArray 的容量，t 為目前 capacity）

    Add: $O(n + m)$   程式總共在記憶體中需要 A、B ，所以此函式儲存量為 $O(m + n)$

    Mult: $O(m * n)$   最多會含有 m * n 個不同項，所以此函式儲存量為 $O(m * n)$

    Eval: $O(1)$   每項一個 pow 呼叫，因此整體  $O(n)$

    istream： $O(1)$ 輸入後 Poly 內部儲存 n 項 $O(n)$

    ostream： $O(1)$

## 測試與驗證
### 測試案例

| 測試案例 | 輸入參數   | 預期輸出  | 實際輸出  | 
|----------|--------------|----------|----------|
| 測試一   |      3     |             |         |       
|          |        2, 3    |            |        | 
|          |        -4,1     |            |        |
|          |        3, 0    |    2x^3 - 4x + 3       |    2x^3 - 4x + 3      |  
| 測試二  |      3    |            |         |       
|          |       1, 2    |            |        | 
|          |       -2, 1    |         |      |
		   |      	1,0     |	x^2 - 2x + 1	| x^2 - 2x + 1	|
|   $A(x)$  +    $B(x)$     |      | 2x^3 + x^2 - 6x + 4       |2x^3 + x^2 - 6x + 4       |   
|   $A(x)$ * $B(x)$  |     |   2x^5 - 4x^4 + 7x^3 - 11x^2 + 10x + 3     |    2x^5 - 4x^4 + 7x^3 - 11x^2 + 10x + 3            |
|   $A(1)$      |      | 1    |   1  |

### 測試輸入
```
輸入次數: 3
輸入第1項的係數和指數 : 2 3
輸入第2項的係數和指數 : -4 1
輸入第3項的係數和指數 : 3 0
輸入次數: 3
輸入第1項的係數和指數 : 1 2
輸入第2項的係數和指數 : -2 1
輸入第3項的係數和指數 : 1	0
輸入x為多少: 1
```
### 測試輸出
```
A(x) =  2x^3 - 4x + 3 
B(x) =  x^2 - 2x + 1
Sum =  2x^3 + 1x^2 - 6x + 4
Product = 2x^5 - 4x^4 + 7x^3 - 11x^2 + 10x + 3
P(1) = 1
```


## 申論及開發報告
### 申論
#### Polynomial 類別
屬性包含：

- termArray：動態陣列儲存多項式項
- capacity：陣列容量
- terms：實際項數

實作方法：

- Add()：多項式加法
- Mult()：多項式乘法
- Eval()：代入求值
- Newterms()：新增項目（並自動擴充記憶體）
#### 多項式加法 Add()
- 依據指數從大到小比對
- 指數相同，則係數相加
- 不同，則將較大指數的項直接加入結果多項式中
#### 多項式乘法 Mult()
- 採用雙層迴圈將每一項彼此相乘，並利用加法函式來完成
  ```cpp
  
  for (int i = 0; i < terms; i++) {
            Polynomial Temp;
            for (int j = 0; j < Poly.terms; j++) {
                float newCoef = termArray[i].coef * Poly.termArray[j].coef;
                int newExp = termArray[i].exp + Poly.termArray[j].exp;
                Temp.Newterms(newCoef, newExp);
            }
            Res = Res.Add(Temp);
        }
        return Res;
  
#### 多項式求值 Eval(x)
- 將輸入的 x 值代入多項式：

$$P(x) = \sum_i (coef_i \times x^{exp_i})$$


對每一項計算後累加得結果。

### 結論

本次作業充分的練習到了物件導向,對多項式運算的邏輯化設計有更深理解。
其中在很多函式跟語法都很不熟練在這個程式學到了很多
class的整體建構對我來說也是一大挑戰
