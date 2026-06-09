
#include <iostream>
#include "../solver_lib/solver.h"

int main() {
    float a = 1, b = -3, c = 2;
    float x1, x2;
    
    solve(a, b, c, x1, x2);
    
    std::cout << "x1 = " << x1 << ", x2 = " << x2 << std::endl;
    return 0;
}
