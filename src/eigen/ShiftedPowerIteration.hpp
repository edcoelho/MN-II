#ifndef METII_SHIFTED_POWER_ITERATION_HPP_
#define METII_SHIFTED_POWER_ITERATION_HPP_

#include <utility>
#include "eigen/Matrix.hpp"
#include "eigen/Vector.hpp"
#include "eigen/PowerIteration.hpp"

namespace metII {

    class ShiftedPowerIteration {

        public:

            ShiftedPowerIteration ();

            std::pair<double, Vector> compute (metII::Matrix matrix, double shifting_factor, double epsilon) const;

    };
    
}

#endif