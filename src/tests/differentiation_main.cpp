#include "differentiation/CentralDerivative.hpp"
#include "differentiation/ForwardDerivative.hpp"
#include "differentiation/BackwardDerivative.hpp"
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

void test_derivative(double x, metII::Derivative& d, const bool is_central_formula = false, double h_divider = 1.005) {

    std::vector<std::pair<std::function<double(double)>, std::string>> functions = {
        {f1, "f1(x) = ln(x) + x^2 - 5*x + 3"},
        {f2, "f2(x) = exp(x) - 2*x^2 + 3*x + 1"},
        {f3, "f3(x) = cos(x) * x^3 - 2*sin(x) + 7"},
        {f4, "f4(x) = x^4 - 4*x^3 + 6*x^2 - 4*x + 1"}
    };
    std::vector<std::size_t>
        derivative_orders = {1,2,3,4},
        error_orders;

    if (is_central_formula)
        error_orders = {2,4,6};
    else
        error_orders = {1,2,3,4,5,6};

    for (const auto& func : functions) {

        d.set_f(func.first);
        std::cout << func.second << std::endl << std::endl;
        
        for (std::size_t derivative_order : derivative_orders) {
            
            d.set_derivative_order(derivative_order);
            std::cout << "Derivative order: " << derivative_order << std::endl << std::endl;

            for (std::size_t error_order : error_orders) {

                d.set_error_order(error_order);
                std::cout << "Error order: " << error_order << std::endl;

                std::cout << "Result: " << d.iterate(x, h_divider, false) << std::endl << std::endl;

            }

            std::cout << "-----" << std::endl << std::endl;

        }

        std::cout << "---------------------------------" << std::endl << std::endl;

    }

}

void test_central(double x, double epsilon = 1.0e-6) {

    metII::CentralDerivative cd(f1, 1, 2, epsilon);

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Central Differentiation Formulas" << std::endl;
    std::cout << "---------------------------------" << std::endl << std::endl;
    std::cout << "Testing functions with x = " << x << std::endl << std::endl;

    test_derivative(x, cd, true);

}

void test_forward(double x, double epsilon = 1.0e-6) {

    metII::ForwardDerivative fd(f1, 1, 2, epsilon);

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Forward Differentiation Formulas" << std::endl;
    std::cout << "---------------------------------" << std::endl << std::endl;
    std::cout << "Testing functions with x = " << x << std::endl << std::endl;

    test_derivative(x, fd);

}

void test_backward(double x, double epsilon = 1.0e-6) {

    metII::BackwardDerivative bd(f1, 1, 2, epsilon);

    std::cout << "---------------------------------" << std::endl;
    std::cout << "Backward Differentiation Formulas" << std::endl;
    std::cout << "---------------------------------" << std::endl << std::endl;
    std::cout << "Testing functions with x = " << x << std::endl << std::endl;

    test_derivative(x, bd);

}

int main() {

    // std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);

    double x = 1.0;

    test_central(x);
    // test_forward(x);
    // test_backward(x);

    // metII::CentralDerivative cd(f1, 4, 2);
    // std::cout << cd.iterate(x, 1.05, false) << std::endl;

    // metII::ForwardDerivative fd(f3, 4, 1);
    // std::cout << fd.iterate(x, 1.005, false) << std::endl;

    // metII::BackwardDerivative bd(f1, 1, 1);
    // std::cout << bd.iterate(x, 1.005, false) << std::endl;

    return EXIT_SUCCESS;

}