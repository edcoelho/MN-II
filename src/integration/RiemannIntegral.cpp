#include "integration/RiemannIntegral.hpp"

metII::RiemannIntegral::RiemannIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _function, bool _use_partitions, double _epsilon) : metII::Integral(_lower_limit, _upper_limit, _function, _use_partitions, _epsilon) {}

double metII::RiemannIntegral::integrate_interval (double a, double b) {

    return (b - a) * this->get_func()((a + ((b - a)/2)));

}