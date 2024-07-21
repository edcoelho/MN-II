#ifndef METII_POWER_ITERATION_HPP_
#define METII_POWER_ITERATION_HPP_

#include <utility>
#include "eigen/Matrix.hpp"
#include "eigen/Vector.hpp"

namespace metII {

    class PowerIteration {

        public:

            PowerIteration ();

            virtual std::pair<double, metII::Vector> compute (metII::Matrix matrix, double epsilon = 1.0e-6) const;

    };
    
}

#endif