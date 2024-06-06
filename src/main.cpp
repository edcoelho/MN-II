#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "integration/RiemannIntegral.hpp"
#include "integration/GaussHermiteIntegral1.hpp"
#include "integration/GaussHermiteIntegral2.hpp"
#include "integration/GaussHermiteIntegral3.hpp"
#include "integration/GaussHermiteIntegral4.hpp"

double f(double x) {

    return std::pow(x, 3.0) - 2.0 * std::pow(x, 2) - 3.0 * x + 4.0;

}

double g(double x) {

    return x;

}

double h(double x) {

    return 8.0 * std::pow(x, 5.0) - 3.0 * std::pow(x, 4.0) - 6.0 * std::pow(x, 3.0) + 15.0 * std::pow(x, 2) - 2.0 * x + 9.0;

}

double i(double x) {

    return 7.0 * std::pow(x, 7.0) - 9.0 * std::pow(x, 6.0) + 2.0 * std::pow(x, 5.0) - 3.0 * std::pow(x, 4.0) + 5.0 * std::pow(x, 3.0) - 4.0 * std::pow(x, 2.0) + 6.0 * x - 1.0;

}

int main (int argc, char * argv[]) {

    metII::RiemannIntegral r(1.0, 5.0);
    std::cout << r.integrate(&f) << std::endl;

    metII::GaussHermiteIntegral1 gh1;
    std::cout << gh1.integrate(&g) << std::endl;

    metII::GaussHermiteIntegral2 gh2;
    std::cout << gh2.integrate(&f) << std::endl;

    metII::GaussHermiteIntegral3 gh3;
    std::cout << gh3.integrate(&h) << std::endl;

    metII::GaussHermiteIntegral4 gh4;
    std::cout << gh4.integrate(&i) << std::endl;

    return EXIT_SUCCESS;

}