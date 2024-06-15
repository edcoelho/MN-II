#ifndef MET_II_GAUSS_HERMITE_INTEGRAL_HPP_
#define MET_II_GAUSS_HERMITE_INTEGRAL_HPP_

#include "integration/SpecialGaussIntegral.hpp"

namespace metII {

    class GaussHermiteIntegral : public SpecialGaussIntegral {

        public:

            GaussHermiteIntegral (std::function<double(double)> _func, std::size_t num_of_gauss_points = 2);

    };

}

#endif