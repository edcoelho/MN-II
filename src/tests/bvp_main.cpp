#include "bvp/FiniteDifference.hpp"
#include "bvp/FiniteDifferencePlus.hpp"
#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

const double
    delta = 0.0001,
    t_f = 1.0;

void test_finite_difference_1D (std::size_t N = 4) {

    metII::boundary
        i_bx = {0.0, 0.0},
        f_bx = {1.0, 1.0};

    double delta_x = (f_bx.position - i_bx.position) / ((double) N);

    metII::Matrix kernel(1, 3);
    kernel(0,0) = 1.0/std::pow(delta_x, 2.0);
    kernel(0,1) = -1.0*( ( 2.0/std::pow(delta_x, 2.0) ) + 1.0 );
    kernel(0,2) = 1.0/std::pow(delta_x, 2.0);

    metII::FiniteDifference fd(N, kernel, {i_bx, f_bx}, 0.0);

    print_vector(fd.compute_nodes());

}

void test_finite_difference_plus_1D (std::size_t N = 3) {

    metII::boundary
        i_bx = {0.2, 0.0},
        f_bx = {0.5, 0.0};

    double
        delta_x = (f_bx.position - i_bx.position) / ((double) N),
        T = 14.0,
        P = 11.0;

    std::function<double(double)>
        // left_node = [=](double x) { return 1.0 + ( delta_x/( 2.0*x ) ); },
        left_node = [=](double x) { return 1.0 - ( delta_x/( 2.0*x ) ); },
        central_node = [=](double x) { return -2.0; },
        right_node = [=](double x) { return 1.0 + ( delta_x/( 2.0*x ) ); };

    metII::BVP_kernel_plus kernel = { left_node, central_node, right_node };

    metII::FiniteDifferencePlus fdp(N, {i_bx, f_bx}, (-P/T)*std::pow(delta_x, 2));

    print_vector(fdp.compute_nodes(kernel));

}

void test_finite_difference_2D (std::size_t N = 4) {

    metII::boundary
        i_bx = {0.0, 0.0},
        f_bx = {1.0, 0.0},
        i_by = {0.0, 0.0},
        f_by = {1.0, 0.0};

    double
        delta_x = (f_bx.position - i_bx.position) / ((double) N),
        delta_y = (f_by.position - i_by.position) / ((double) N);

    metII::Matrix kernel(3, 3);

    kernel(1,0) = 1.0/std::pow(delta_x, 2.0); // left
    kernel(1,1) = -2.0*( ( 1.0/std::pow(delta_x, 2.0) ) + ( 1.0/std::pow(delta_y, 2.0) ) ); // center
    kernel(1,2) = 1.0/std::pow(delta_x, 2.0); // right
    kernel(2,1) = 1.0/std::pow(delta_y, 2.0); // bottom
    kernel(0,1) = 1.0/std::pow(delta_y, 2.0); // top

    metII::FiniteDifference fd(N, kernel, {i_bx, f_bx, i_by, f_by}, 4.0);

    print_vector(fd.compute_nodes());

}

int main () {

    std::cout << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);

    // test_finite_difference_1D();
    // test_finite_difference_1D(8);
    // test_finite_difference_2D();
    // test_finite_difference_2D(8);

    test_finite_difference_plus_1D();

}