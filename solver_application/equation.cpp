
#include <iostream>
#include "formatter_ex.h"
#include "solver.h"

int main() {
    double a = 1, b = -3, c = 2;
    double root = solve_equation(a, b, c);
    
    std::cout << format_ex("Equation: " + std::to_string(a) + "x^2 + " + 
                           std::to_string(b) + "x + " + std::to_string(c) + " = 0") << std::endl;
    std::cout << "Root: " << root << std::endl;
    
    return 0;
}
