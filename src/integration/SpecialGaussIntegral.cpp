#include "integration/SpecialGaussIntegral.hpp"

metII::SpecialGaussIntegral::SpecialGaussIntegral () : metII::Integral(0.0, 0.0, false) {}
metII::SpecialGaussIntegral::~SpecialGaussIntegral () {}

double metII::SpecialGaussIntegral::integrate_interval (std::function<double(double)> func, double a, double b) {

    double res = 0.0;

    for (std::size_t i = 0; i < this->weights.size(); i++) {

        res += this->weights[i] * func(this->roots[i]);

    }

    return res;

}

void metII::SpecialGaussIntegral::set_use_partitions (bool _use_partitions) {}

double metII::SpecialGaussIntegral::integrate_partitions(std::function<double(double)> func, std::size_t num_of_partitions) {

    return this->integrate_interval(func, 0.0, 0.0);

}