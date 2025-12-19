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
