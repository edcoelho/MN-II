#include "integration/RiemannIntegral.hpp"

metII::RiemannIntegral::RiemannIntegral (double _lower_limit, double _upper_limit, bool _use_partitions, double _epsilon) : metII::Integral(_lower_limit, _upper_limit, _use_partitions, _epsilon) {}

double metII::RiemannIntegral::integrate_interval (std::function<double(double)> func, double a, double b) {

    return (b - a) * func(a + ((b - a)/2));

}