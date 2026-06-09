
#include "solver.h"
#include <cmath>

double solve_equation(double a, double b, double c) {
    return (-b + sqrt(b*b - 4*a*c)) / (2*a);
}
