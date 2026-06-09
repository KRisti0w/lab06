
#include "solver.h"
#include <cmath>

void solve(double a, double b, double c, double& x1, double& x2) {
    double d = b*b - 4*a*c;
    if (d >= 0) {
        x1 = (-b + sqrt(d)) / (2*a);
        x2 = (-b - sqrt(d)) / (2*a);
    }
}
