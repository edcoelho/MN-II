#include "differentiation/CentralDerivative.hpp"
#include "differentiation/ForwardDerivative.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <string>
#include <iomanip>

// f1(x) = ln(x) + x^2 - 5*x + 3
double f1(double x) {

    return std::log(x) + std::pow(x, 2.0) - 5.0 * x + 3.0;

}

// f2(x) = exp(x) - 2*x^2 + 3*x + 1
double f2(double x) {

    return std::exp(x) - 2.0 * std::pow(x, 2.0) + 3.0 * x + 1.0;

}

// f3(x) = cos(x) * x^3 - 2*sin(x) + 7
double f3(double x) {

    return std::cos(x) * std::pow(x, 3.0) - 2.0 * std::sin(x) + 7.0;

}

// f4(x) = x^4 - 4*x^3 + 6*x^2 - 4*x + 1
double f4(double x) {

    return std::pow(x, 4.0) - 4.0 * std::pow(x, 3.0) + 6.0 * std::pow(x, 2.0) - 4.0 * x + 1.0;

}

void test_central(double x, double epsilon = 1.0e-6) {

    std::vector<std::pair<std::function<double(double)>, std::string>> functions = {
        {f1, "f1(x) = ln(x) + x^2 - 5*x + 3"},
        {f2, "f2(x) = exp(x) - 2*x^2 + 3*x + 1"},
        {f3, "f3(x) = cos(x) * x^3 - 2*sin(x) + 7"},
        {f4, "f4(x) = x^4 - 4*x^3 + 6*x^2 - 4*x + 1"}
    };
    std::size_t derivative_orders[] = {1, 2, 3, 4};
    std::size_t error_orders[] = {2, 4, 6};
    metII::CentralDerivative cd(f1, 1, 2, epsilon);

    std::cout << "Testing functions with x = " << x << std::endl << std::endl;

    std::cout << "---------------------------------" << std::endl << std::endl;

    for (const auto& func : functions) {

        cd.set_f(func.first);
        std::cout << func.second << std::endl << std::endl;
        
        for (std::size_t derivative_order : derivative_orders) {
            
            cd.set_derivative_order(derivative_order);
            std::cout << "Derivative order: " << derivative_order << std::endl << std::endl;

            for (std::size_t error_order : error_orders) {

                cd.set_error_order(error_order);
                std::cout << "Error order: " << error_order << std::endl;

                std::cout << "Result: " << cd.iterate(x, 1.05, true) << std::endl << std::endl;

            }

            std::cout << "-----" << std::endl << std::endl;

        }

        std::cout << "---------------------------------" << std::endl << std::endl;

    }

}

void test_forward(double x, double epsilon = 1.0e-6) {

    std::vector<std::pair<std::function<double(double)>, std::string>> functions = {
        {f1, "f1(x) = ln(x) + x^2 - 5*x + 3"},
        {f2, "f2(x) = exp(x) - 2*x^2 + 3*x + 1"},
        {f3, "f3(x) = cos(x) * x^3 - 2*sin(x) + 7"},
        {f4, "f4(x) = x^4 - 4*x^3 + 6*x^2 - 4*x + 1"}
    };
    std::size_t derivative_orders[] = {1, 2, 3, 4};
    std::size_t error_orders[] = {1, 2, 3, 4, 5, 6};
    metII::ForwardDerivative fd(f1, 1, 2, epsilon);

    std::cout << "Testing functions with x = " << x << std::endl << std::endl;

    std::cout << "---------------------------------" << std::endl << std::endl;

    for (const auto& func : functions) {

        fd.set_f(func.first);
        std::cout << func.second << std::endl << std::endl;
        
        for (std::size_t derivative_order : derivative_orders) {
            
            fd.set_derivative_order(derivative_order);
            std::cout << "Derivative order: " << derivative_order << std::endl << std::endl;

            for (std::size_t error_order : error_orders) {

                fd.set_error_order(error_order);
                std::cout << "Error order: " << error_order << std::endl;

                std::cout << "Result: " << fd.iterate(x, 1.005, false) << std::endl << std::endl;

            }

            std::cout << "-----" << std::endl << std::endl;

        }

        std::cout << "---------------------------------" << std::endl << std::endl;

    }

}

int main() {

    // std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);

    double x = 1.0;

    // test_central(x);
    test_forward(x);

    // metII::CentralDerivative cd(f1, 4, 2);
    // std::cout << cd.iterate(x, 1.05, true) << std::endl;

    // metII::ForwardDerivative fd(f3, 4, 1);
    // std::cout << fd.iterate(x, 1.005, false) << std::endl;

    return EXIT_SUCCESS;

}