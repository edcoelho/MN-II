#ifndef MET_II_SIMPLE_EXPONENTIAL_INTEGRAL_HPP_
#define MET_II_SIMPLE_EXPONENTIAL_INTEGRAL_HPP_

#include "integration/ExponentialIntegral.hpp"

namespace metII {

    class SimpleExponentialIntegral : public ExponentialIntegral {

        protected:

            double x (double s) override;
            double dx_ds (double s) override;

        public:

            SimpleExponentialIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, metII::quadrature_type _internal_quadrature_type, std::size_t _internal_quadrature_num_of_points = 2, bool _use_partitions = true, double _epsilon = 1e-6, double _internal_epsilon = 1e-6);

    };

}

#endif