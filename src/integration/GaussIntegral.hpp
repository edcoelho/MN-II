#ifndef MET_II_GAUSS_INTEGRAL_HPP_
#define MET_II_GAUSS_INTEGRAL_HPP_

#include "integration/Integral.hpp"
#include <vector>

namespace metII {

    class GaussIntegral : public Integral {

        protected:

            std::vector<double> weights;
            std::vector<double> roots;

        public:

            GaussIntegral (double _lower_limit, double _upper_limit, bool _use_partitions, double _epsilon = 1e-6);

    };

}

#endif