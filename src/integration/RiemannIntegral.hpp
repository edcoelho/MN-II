#ifndef MET_II_RIEMANN_INTEGRAL_HPP_
#define MET_II_RIEMANN_INTEGRAL_HPP_

#include "integration/Integral.hpp"

namespace metII {

    class RiemannIntegral : public Integral {

        protected:

            double integrate_interval (double a, double b) override;

        public:

            RiemannIntegral (double _lower_limit, double _upper_limit, std::function<double(double)> _func, bool _use_partitions = true, double _epsilon = 1e-6);

    };

}

#endif