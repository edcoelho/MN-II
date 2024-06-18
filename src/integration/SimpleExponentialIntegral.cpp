#include "integration/SimpleExponentialIntegral.hpp"
#include <cmath>

metII::SimpleExponentialIntegral::SimpleExponentialIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, metII::quadrature_type _internal_quadrature_type, std::size_t _internal_quadrature_num_of_points, bool _use_partitions, double _epsilon, double _internal_epsilon) : ExponentialIntegral(_lower_limit, _upper_limit, _func, _internal_quadrature_type, _internal_quadrature_num_of_points, _use_partitions, _epsilon, _internal_epsilon) {}

double metII::SimpleExponentialIntegral::x (double s) {

    double a = this->get_lower_limit(), b = this->get_upper_limit();

    return (a + b + (b - a)*std::tanh(s))/2.0;

}

double metII::SimpleExponentialIntegral::dx_ds (double s) {

    double a = this->get_lower_limit(), b = this->get_upper_limit();

    return ((b - a)/2.0) * (1.0/std::pow(std::cosh(s), 2));

}