#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "integration/RiemannIntegral.hpp"
#include "integration/GaussHermiteIntegral.hpp"
#include "integration/GaussLaguerreIntegral.hpp"
#include "integration/GaussChebyshevIntegral.hpp"

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

    metII::RiemannIntegral r1(-1.0, 1.0, &g);
    std::cout << r1.integrate() << std::endl;

    metII::RiemannIntegral r2(-1.0, 1.0, &f);
    std::cout << r2.integrate() << std::endl;

    metII::RiemannIntegral r3(-1.0, 1.0, &h);
    std::cout << r3.integrate() << std::endl;

    metII::RiemannIntegral r4(-1.0, 1.0, &i);
    std::cout << r4.integrate() << std::endl;

    std::cout << std::endl << "Gauss-Hermite" << std::endl;

    metII::GaussHermiteIntegral gh1(&g, 1);
    std::cout << gh1.integrate() << std::endl;

    metII::GaussHermiteIntegral gh2(&f, 2);
    std::cout << gh2.integrate() << std::endl;

    metII::GaussHermiteIntegral gh3(&h, 3);
    std::cout << gh3.integrate() << std::endl;

    metII::GaussHermiteIntegral gh4(&i, 4);
    std::cout << gh4.integrate() << std::endl;

    std::cout << std::endl << "Gauss-Laguerre" << std::endl;

    metII::GaussLaguerreIntegral gl1(&g, 1);
    std::cout << gl1.integrate() << std::endl;

    metII::GaussLaguerreIntegral gl2(&f, 2);
    std::cout << gl2.integrate() << std::endl;

    metII::GaussLaguerreIntegral gl3(&h, 3);
    std::cout << gl3.integrate() << std::endl;

    metII::GaussLaguerreIntegral gl4(&i, 4);
    std::cout << gl4.integrate() << std::endl;

    std::cout << std::endl << "Gauss-Chebyshev" << std::endl;

    metII::GaussChebyshevIntegral gc1(&g, 1);
    std::cout << gc1.integrate() << std::endl;

    metII::GaussChebyshevIntegral gc2(&f, 2);
    std::cout << gc2.integrate() << std::endl;

    metII::GaussChebyshevIntegral gc3(&h, 3);
    std::cout << gc3.integrate() << std::endl;

    metII::GaussChebyshevIntegral gc4(&i, 4);
    std::cout << gc4.integrate() << std::endl;

    return EXIT_SUCCESS;

}