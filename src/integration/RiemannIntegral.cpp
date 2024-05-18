#include "integration/RiemannIntegral.hpp"

metII::RiemannIntegral::RiemannIntegral (double _lower_limit, double _upper_limit) : metII::Integral(_lower_limit, _upper_limit) {}

double metII::RiemannIntegral::integrate_interval (std::function<double(double)> func, double a, double b) {

    return (b - a) * func(a + ((b - a)/2));

}