#ifndef MET_II_GAUSS_LAGUERRE_INTEGRAL_HPP_
#define MET_II_GAUSS_LAGUERRE_INTEGRAL_HPP_

#include "integration/SpecialGaussIntegral.hpp"

namespace metII {

    class GaussLaguerreIntegral : public SpecialGaussIntegral {

        public:

            GaussLaguerreIntegral (std::size_t num_of_gauss_points = 2);

    };

}

#endif