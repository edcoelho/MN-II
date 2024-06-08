#ifndef MET_II_GAUSS_LEGENDRE_INTEGRAL_HPP_
#define MET_II_GAUSS_LEGENDRE_INTEGRAL_HPP_

#include "integration/GaussIntegral.hpp"

namespace metII {

    class GaussLegendreIntegral : public GaussIntegral {

        public:

            GaussLegendreIntegral (double _lower_limit, double _upper_limit, std::size_t num_of_gauss_points = 2, bool _use_partitions = true, double _epsilon = 1e-6);

    };

}

#endif