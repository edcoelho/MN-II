#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "integration/RiemannIntegral.hpp"
#include "integration/GaussHermiteIntegral.hpp"
#include "integration/GaussLaguerreIntegral.hpp"

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

    std::cout << "Riemann [-1.0, 1.0]" << std::endl;

    metII::RiemannIntegral r1(-1.0, 1.0);
    std::cout << r1.integrate(&g) << std::endl;

    metII::RiemannIntegral r2(-1.0, 1.0);
    std::cout << r2.integrate(&f) << std::endl;

    metII::RiemannIntegral r3(-1.0, 1.0);
    std::cout << r3.integrate(&h) << std::endl;

    metII::RiemannIntegral r4(-1.0, 1.0);
    std::cout << r4.integrate(&i) << std::endl;

    std::cout << std::endl << "Gauss-Hermite" << std::endl;

    metII::GaussHermiteIntegral gh1(1);
    std::cout << gh1.integrate(&g) << std::endl;

    metII::GaussHermiteIntegral gh2(2);
    std::cout << gh2.integrate(&f) << std::endl;

    metII::GaussHermiteIntegral gh3(3);
    std::cout << gh3.integrate(&h) << std::endl;

    metII::GaussHermiteIntegral gh4(4);
    std::cout << gh4.integrate(&i) << std::endl;

    std::cout << std::endl << "Gauss-Laguerre" << std::endl;

    metII::GaussLaguerreIntegral gl1(1);
    std::cout << gl1.integrate(&g) << std::endl;

    metII::GaussLaguerreIntegral gl2(2);
    std::cout << gl2.integrate(&f) << std::endl;

    metII::GaussLaguerreIntegral gl3(3);
    std::cout << gl3.integrate(&h) << std::endl;

    metII::GaussLaguerreIntegral gl4(4);
    std::cout << gl4.integrate(&i) << std::endl;

    return EXIT_SUCCESS;

}