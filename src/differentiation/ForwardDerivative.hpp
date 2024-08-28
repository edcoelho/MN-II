#ifndef MET_II_FORWARD_DERIVATIVE_HPP_
#define MET_II_FORWARD_DERIVATIVE_HPP_

#include "differentiation/Derivative.hpp"

namespace metII {

    class ForwardDerivative : public Derivative {

        private:

            double first_derivative (const double x, const double h) const final override;
            double second_derivative (const double x, const double h) const final override;
            double third_derivative (const double x, const double h) const final override;
            double fourth_derivative (const double x, const double h) const final override;

        public:

            ForwardDerivative (std::function<double(double)> _f, std::size_t _derivative_order = 1, std::size_t _error_order = 1, double _epsilon = 1.0e-6);

    };

}

#endif