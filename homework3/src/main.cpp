#include <iostream>
#include "Polynomial.h"

int main() {
    Polynomial p1, p2;
    std::cout << "輸入 P1 (項數 c1 e1 ...): ";
    std::cin >> p1;
    std::cout << "輸入 P2 (項數 c1 e1 ...): ";
    std::cin >> p2;

    std::cout << "P1: " << p1 << std::endl;
    std::cout << "P2: " << p2 << std::endl;
    std::cout << "P1 + P2: " << (p1 + p2) << std::endl;
    std::cout << "P1 - P2: " << (p1 - p2) << std::endl;
    std::cout << "P1 * P2: " << (p1 * p2) << std::endl;
    std::cout << "P1(x=2): " << p1.Evaluate(2.0) << std::endl;

    return 0;
}
