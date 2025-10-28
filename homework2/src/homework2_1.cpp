#include <iostream>
using namespace std;
int ack(int m, int n) {
   // 當 m = 0 時，直接回傳 n+1
    if (m == 0) return n + 1; 
   // 當 m > 0 且 n = 0 時，變成 A(m-1, 1)
    else if (n == 0) return ack(m - 1, 1); 
    // 其他情況 → A(m-1, A(m, n-1))
    else return ack(m - 1, ack(m, n - 1)); 
int main() {
    int m, n;
    cout << "輸入 m 和 n : ";
    // 持續輸入直到手動停止
    while (cin >> m >> n) {
        cout << "(" << m << ", " << n << ") = " << ack(m, n) << endl;
        cout << "輸入 m 和 n : ";
    }
    return 0;
}

