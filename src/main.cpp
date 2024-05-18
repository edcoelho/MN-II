#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "integration/RiemannIntegral.hpp"

double f(double x) {

    return std::pow(x, 3.0) - 2.0 * std::pow(x, 2) - 3.0 * x;

}

int main (int argc, char * argv[]) {

    metII::RiemannIntegral i(1.0, 5.0);

    std::cout << i.integrate(&f) << std::endl;

    return EXIT_SUCCESS;

}