#include "integration/ExponentialIntegral.hpp"
#include "integration/NewtonCotesIntegral.hpp"
#include "integration/GaussLegendreIntegral.hpp"
#include <cmath>
#include <limits>

metII::ExponentialIntegral::ExponentialIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, metII::quadrature_type _internal_quadrature_type, std::size_t _internal_quadrature_num_of_points, bool _use_partitions, double _epsilon, double _internal_epsilon) : metII::Integral(_lower_limit, _upper_limit, _func, _use_partitions, _epsilon), internal_epsilon(_internal_epsilon) {

    std::function<double(double)> new_func = [this, _func](double s) {

        return _func(this->x(s)) * this->dx_ds(s);

    };

    if (_internal_quadrature_type == NEWTON_COTES) {

        this->internal_quadrature = new NewtonCotesIntegral(0.0, 1.0, new_func, true, _internal_quadrature_num_of_points);

    } else {

        this->internal_quadrature = new GaussLegendreIntegral(0.0, 1.0, new_func, _internal_quadrature_num_of_points, _use_partitions, _internal_epsilon);

    }

}

metII::ExponentialIntegral::~ExponentialIntegral () {

    delete this->internal_quadrature;
    
}

double metII::ExponentialIntegral::integrate_interval (double a, double b) {

    this->internal_quadrature->set_lower_limit(a);
    this->internal_quadrature->set_upper_limit(b);
    return this->internal_quadrature->integrate();

}

double metII::ExponentialIntegral::get_internal_epsilon () const {

    return this->internal_epsilon;

}
void metII::ExponentialIntegral::set_internal_epsilon (double _internal_epsilon) {

    this->internal_epsilon = _internal_epsilon;

}

void metII::ExponentialIntegral::set_func (std::function<double(double)> _func) {

    metII::Integral::set_func(_func);

    this->internal_quadrature->set_func([this, _func](double s) {

        return _func(this->x(s)) * this->dx_ds(s);

    });

}

double metII::ExponentialIntegral::integrate_partitions (std::size_t num_of_partitions) {

    return this->integrate();

}

double metII::ExponentialIntegral::integrate () {

    double relative_error = 1.0, old_sum = 0.0, new_sum = 0.0, internal_limit = 1.0;
    std::size_t num_zero_iterations = 0, max_zero_iterations = 10;

    while (relative_error > this->get_epsilon()) {

        new_sum = this->integrate_interval(-internal_limit, internal_limit);

        if (-std::numeric_limits<double>::infinity() >= new_sum || new_sum >= std::numeric_limits<double>::infinity()) {

            new_sum = old_sum;
            relative_error = 0.0;

        } else if (new_sum != 0.0) {

            relative_error = std::abs((new_sum - old_sum) / new_sum);
            num_zero_iterations = 0;

        } else if (new_sum == 0.0 && old_sum != 0.0) {

            relative_error = std::abs(new_sum - old_sum);
            num_zero_iterations = 0;

        } else {
            
            if (num_zero_iterations < max_zero_iterations) {

                num_zero_iterations++;

            } else {

                relative_error = 0.0;

            }

        }

        old_sum = new_sum;
        internal_limit += 1;

    }

    return new_sum;

}