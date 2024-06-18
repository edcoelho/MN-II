#include "integration/DoubleExponentialIntegral.hpp"
#include <cmath>

metII::DoubleExponentialIntegral::DoubleExponentialIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, metII::quadrature_type _internal_quadrature_type, std::size_t _internal_quadrature_num_of_points, bool _use_partitions, double _epsilon, double _internal_epsilon) : ExponentialIntegral(_lower_limit, _upper_limit, _func, _internal_quadrature_type, _internal_quadrature_num_of_points, _use_partitions, _epsilon, _internal_epsilon) {}

double metII::DoubleExponentialIntegral::x (double s) {

    double a = this->get_lower_limit(), b = this->get_upper_limit();

    return (a + b + (b - a)*std::tanh(M_PI_2*std::sinh(s)))/2.0;

}

double metII::DoubleExponentialIntegral::dx_ds (double s) {

    double a = this->get_lower_limit(), b = this->get_upper_limit();

    return ((b - a)/2.0) * (M_PI_2 * std::cosh(s) / std::pow(std::cosh(M_PI_2 * std::sinh(s)), 2.0));

}