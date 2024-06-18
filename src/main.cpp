#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "integration/RiemannIntegral.hpp"
#include "integration/GaussHermiteIntegral.hpp"
#include "integration/GaussLaguerreIntegral.hpp"
#include "integration/GaussChebyshevIntegral.hpp"
#include "integration/NewtonCotesIntegral.hpp"
#include "integration/GaussLegendreIntegral.hpp"
#include "integration/SimpleExponentialIntegral.hpp"
#include "integration/DoubleExponentialIntegral.hpp"

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

double j(double x) {

    return 1.0/std::sqrt(x);

}

double k(double x) {

    return std::pow(M_PI*std::sqrt(x), M_E);

}

int main (int argc, char * argv[]) {

    std::cout << "Newton-Cotes (Closed) [1.0, 5.0]" << std::endl;

    metII::NewtonCotesIntegral nc1(1.0, 5.0, &k, true, 1);
    std::cout << nc1.integrate() << std::endl;

    metII::NewtonCotesIntegral nc2(1.0, 5.0, &k, true, 2);
    std::cout << nc2.integrate() << std::endl;

    metII::NewtonCotesIntegral nc3(1.0, 5.0, &k, true, 3);
    std::cout << nc3.integrate() << std::endl;

    metII::NewtonCotesIntegral nc4(1.0, 5.0, &k, true, 4);
    std::cout << nc4.integrate() << std::endl;

    std::cout << std::endl << "Gauss-Legendre [1.0, 5.0]" << std::endl;

    metII::GaussLegendreIntegral gl1(1.0, 5.0, &k, 1);
    std::cout << gl1.integrate() << std::endl;

    metII::GaussLegendreIntegral gl2(1.0, 5.0, &k, 2);
    std::cout << gl2.integrate() << std::endl;

    metII::GaussLegendreIntegral gl3(1.0, 5.0, &k, 3);
    std::cout << gl3.integrate() << std::endl;

    metII::GaussLegendreIntegral gl4(1.0, 5.0, &k, 4);
    std::cout << gl4.integrate() << std::endl;

    std::cout << std::endl << "Simple Exponential (using Newton-Cotes) [0.0, 1.0]" << std::endl;

    metII::SimpleExponentialIntegral se_nc1(0.0, 3.0, &j, metII::NEWTON_COTES, 1);
    std::cout << se_nc1.integrate() << std::endl;

    metII::SimpleExponentialIntegral se_nc2(0.0, 3.0, &j, metII::NEWTON_COTES, 2);
    std::cout << se_nc2.integrate() << std::endl;

    metII::SimpleExponentialIntegral se_nc3(0.0, 3.0, &j, metII::NEWTON_COTES, 3);
    std::cout << se_nc3.integrate() << std::endl;

    metII::SimpleExponentialIntegral se_nc4(0.0, 3.0, &j, metII::NEWTON_COTES, 4);
    std::cout << se_nc4.integrate() << std::endl;

    std::cout << std::endl << "Simple Exponential (using Gauss-Legendre) [0.0, 1.0]" << std::endl;

    metII::SimpleExponentialIntegral se_gl1(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 1);
    std::cout << se_gl1.integrate() << std::endl;

    metII::SimpleExponentialIntegral se_gl2(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 2);
    std::cout << se_gl2.integrate() << std::endl;

    metII::SimpleExponentialIntegral se_gl3(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 3);
    std::cout << se_gl3.integrate() << std::endl;

    metII::SimpleExponentialIntegral se_gl4(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 4);
    std::cout << se_gl4.integrate() << std::endl;

    std::cout << std::endl << "Double Exponential (using Newton-Cotes) [0.0, 1.0]" << std::endl;

    metII::DoubleExponentialIntegral de_nc1(0.0, 3.0, &j, metII::NEWTON_COTES, 1);
    std::cout << de_nc1.integrate() << std::endl;

    metII::DoubleExponentialIntegral de_nc2(0.0, 3.0, &j, metII::NEWTON_COTES, 2);
    std::cout << de_nc2.integrate() << std::endl;

    metII::DoubleExponentialIntegral de_nc3(0.0, 3.0, &j, metII::NEWTON_COTES, 3);
    std::cout << de_nc3.integrate() << std::endl;

    metII::DoubleExponentialIntegral de_nc4(0.0, 3.0, &j, metII::NEWTON_COTES, 4);
    std::cout << de_nc4.integrate() << std::endl;

    std::cout << std::endl << "Double Exponential (using Gauss-Legendre) [0.0, 1.0]" << std::endl;

    metII::DoubleExponentialIntegral de_gl1(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 1);
    std::cout << de_gl1.integrate() << std::endl;

    metII::DoubleExponentialIntegral de_gl2(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 2);
    std::cout << de_gl2.integrate() << std::endl;

    metII::DoubleExponentialIntegral de_gl3(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 3);
    std::cout << de_gl3.integrate() << std::endl;

    metII::DoubleExponentialIntegral de_gl4(0.0, 3.0, &j, metII::GAUSS_LEGENDRE, 4);
    std::cout << de_gl4.integrate() << std::endl;

    return EXIT_SUCCESS;

}