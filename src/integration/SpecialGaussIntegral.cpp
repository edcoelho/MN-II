#include "integration/SpecialGaussIntegral.hpp"

metII::SpecialGaussIntegral::SpecialGaussIntegral (std::function<double(double)> _func) : metII::GaussIntegral(0.0, 0.0, _func, false) {}
metII::SpecialGaussIntegral::~SpecialGaussIntegral () {}

double metII::SpecialGaussIntegral::integrate_interval (double a, double b) {

    double res = 0.0;

    for (std::size_t i = 0; i < this->weights.size(); i++) {

        res += this->weights[i] * this->get_func()(this->roots[i]);

    }

    return res;

}

void metII::SpecialGaussIntegral::set_use_partitions (bool _use_partitions) {}

double metII::SpecialGaussIntegral::integrate_partitions(std::size_t num_of_partitions) {

    return this->integrate_interval(0.0, 0.0);

}