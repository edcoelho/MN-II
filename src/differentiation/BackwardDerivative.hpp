#ifndef MET_II_BACKWARD_DERIVATIVE_HPP_
#define MET_II_BACKWARD_DERIVATIVE_HPP_

#include "differentiation/Derivative.hpp"

namespace metII {

    class BackwardDerivative : public Derivative {

        private:

            double first_derivative (const double x, const double h) const final override;
            double second_derivative (const double x, const double h) const final override;
            double third_derivative (const double x, const double h) const final override;
            double fourth_derivative (const double x, const double h) const final override;

        public:

            BackwardDerivative (std::function<double(double)> _f, std::size_t _derivative_order = 1, std::size_t _error_order = 1, double _epsilon = 1.0e-6, double _h_divider = 2.0, double _initial_h = 0.1, bool _check_for_invalid_iterations = false);

    };

}

#endif