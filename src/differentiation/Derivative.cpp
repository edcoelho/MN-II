#include "differentiation/Derivative.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <cmath>
#include <limits>

namespace metII {

    Derivative::Derivative (std::function<double(double)> _f, std::size_t _derivative_order, std::size_t _error_order, double _epsilon) {

        this->f = _f;
        this->derivative_order = _derivative_order;
        this->error_order = _error_order;
        this->epsilon = _epsilon;

    }

    std::function<double(double)> Derivative::get_f () const {

        return this->f;

    }
    void Derivative::set_f (std::function<double(double)> _f) {

        this->f = _f;

    }

    std::size_t Derivative::get_derivative_order () const {

        return this->derivative_order;

    }
    void Derivative::set_derivative_order (std::size_t _derivative_order) {

        if (_derivative_order > 4) {

            throw std::runtime_error("Error in (void) metII::Derivative::set_derivative_order(std::size_t): Invalid derivative order! Please ensure that the derivative order is 1, 2, 3 or 4 as the class does not support higher order derivatives.");

        }

        this->derivative_order = _derivative_order;

    }

    std::size_t Derivative::get_error_order () const {

        return this->error_order;

    }
    void Derivative::set_error_order (std::size_t _error_order) {

        if (_error_order > 6) {

            throw std::runtime_error("Error in (void) metII::Derivative::set_error_order(std::size_t): Invalid error order! Please ensure that the error order is 1, 2, 3, 4, 5 or 6 as the class does not support derivatives with a higher order error.");

        }

        this->error_order = _error_order;

    }

    double Derivative::get_epsilon () const {

        return this->epsilon;

    }
    void Derivative::set_epsilon (double _epsilon) {

        this->epsilon = _epsilon;

    }

    double Derivative::iterate (const double x, const double h_divider, const bool check_for_invalid_iterations, const std::size_t max_zero_iterations) const {

        double
            curr_result = 0.0,
            new_result = 0.0,
            relative_error = this->get_epsilon() + 1.0,
            h = 0.1;
        std::size_t count_zero_iterations = 0;
        bool
            continue_iteration = true,
            is_iteration_valid = true;

        if (h_divider <= 1.0) {

            throw std::runtime_error("Error in (double) metII::Derivative::iterate(const double, const double, bool, const std::size_t): Invalid h_divider! Please ensure that h_divider is greater than 1.");

        }

        while (relative_error > this->get_epsilon() && continue_iteration) {

            new_result = this->derive(x, h);
            is_iteration_valid = !check_for_invalid_iterations || (!std::isinf(new_result) && !std::isnan(curr_result));

            if (std::abs(new_result) > std::numeric_limits<double>::epsilon() && is_iteration_valid) {

                relative_error = std::abs((new_result - curr_result) / new_result);
                count_zero_iterations = 0;

            } else if (count_zero_iterations < max_zero_iterations) {

                count_zero_iterations++;

            } else {

                continue_iteration = false;

            }

            curr_result = new_result;
            h = h / h_divider;

        };

        return new_result;

    }

    double Derivative::derive (double x, const double h) const {

        double result = 0.0;

        switch (this->get_derivative_order()) {

            case 1:
                result = this->first_derivative(x, h);
                break;

            case 2:
                result = this->second_derivative(x, h);
                break;

            case 3:
                result = this->third_derivative(x, h);
                break;

            case 4:
                result = this->fourth_derivative(x, h);
                break;
            
        }

        return result;

    }

}