#ifndef METII_SHIFTED_POWER_ITERATION_HPP_
#define METII_SHIFTED_POWER_ITERATION_HPP_

#include <utility>
#include "eigen/SquareMatrix.hpp"
#include "eigen/Vector.hpp"
#include "eigen/PowerIteration.hpp"

namespace metII {

    class ShiftedPowerIteration : public metII::PowerIteration {

        public:

            ShiftedPowerIteration ();

            std::pair<double, Vector> compute (metII::SquareMatrix matrix, double epsilon) override;

    };
    
}

#endif