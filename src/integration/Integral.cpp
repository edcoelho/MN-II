#include "integration/Integral.hpp"
#include <cmath>

metII::Integral::Integral (double _lower_limit, double _upper_limit, bool _use_partitions, double _epsilon) : lower_limit(_lower_limit), upper_limit(_upper_limit), use_partitions(_use_partitions), epsilon(_epsilon) {}

double metII::Integral::get_lower_limit () const {

    return this->lower_limit;

}
void metII::Integral::set_lower_limit (double _lower_limit) {

    this->lower_limit = _lower_limit;

}

double metII::Integral::get_upper_limit () const {

    return this->upper_limit;

}
void metII::Integral::set_upper_limit (double _upper_limit) {

    this->upper_limit = _upper_limit;

}

double metII::Integral::get_epsilon () const {

    return this->epsilon;

}
void metII::Integral::set_epsilon (double _epsilon) {

    this->epsilon = _epsilon;

}

bool metII::Integral::get_use_partitions () const {

    return this->use_partitions;

}
void metII::Integral::set_use_partitions (bool _use_partitions) {

    this->use_partitions = _use_partitions;

}

double metII::Integral::integrate_partitions(std::function<double(double)> func, std::size_t num_of_partitions) {

    double delta_x, a, b, sum = 0.0;

    delta_x = (this->get_upper_limit() - this->get_lower_limit()) / num_of_partitions;

    for (std::size_t i = 0; i < num_of_partitions; i++) {

        a = this->get_lower_limit() + i*delta_x;
        b = a + delta_x;
        sum += this->integrate_interval(func, a, b);
        
    }

    return sum;

}

double metII::Integral::integrate (std::function<double(double)> func) {

    if (!this->get_use_partitions()) {

        return this->integrate_interval(func, this->get_lower_limit(), this->get_upper_limit());

    }

    double relative_error = 1.0, old_sum = 0.0, new_sum = 0.0;
    std::size_t num_of_partitions = 1, num_zero_iterations = 0, max_zero_iterations = 10;

    while (relative_error > epsilon) {

        new_sum = this->integrate_partitions(func, num_of_partitions);
        if (new_sum != 0.0) {

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
        num_of_partitions *= 2;

    }

    return new_sum;

}