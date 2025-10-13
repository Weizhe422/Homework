//Ackermann Function(非遞迴)
#include <iostream>
#include <cstring> // for memset
using namespace std;

int ackermann(int m, int n) {
    // 設定一個足夠大的 stack 來模擬遞迴
    const int MAX_STACK = 100000; // 可依需求調整
    int stack[MAX_STACK];
    int top = 0;
    stack[top++] = m;//把第一層 m 推入堆疊

    while (top > 0) {
        m = stack[--top];// 取出最上層 m
        if (m == 0) {
            if (top == 0) {
                return n + 1;
            }
            n = n + 1;//將結果往上回傳
        }
        else if (n == 0) {
            stack[top++] = m - 1;
            n = 1;// 對應到 A(m-1,1)
        }
        else {
            stack[top++] = m - 1;
            stack[top++] = m;
            n = n - 1; // 對應到 A(m-1, A(m,n-1))
        }
    }
    return n;
}

int main() {
    int m, n;
    cout << "輸入 m 和 n :  ";
    while (cin >> m >> n) {
        cout << "(" << m << ", " << n << ") = " << ackermann(m, n) << endl;
        cout << "輸入 m 和 n : ";
    }
    return 0;
}
