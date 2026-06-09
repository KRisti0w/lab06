
#include <iostream>
#include "solver.h"

int main() {
    double a = 1, b = -3, c = 2;
    double x1 = 0, x2 = 0;
    
    solve(a, b, c, x1, x2);
    
    std::cout << "Equation: " << a << "x^2 + " << b << "x + " << c << " = 0" << std::endl;
    std::cout << "x1 = " << x1 << ", x2 = " << x2 << std::endl;
    
    return 0;
}
