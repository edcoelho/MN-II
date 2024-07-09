#ifndef METII_INVERSE_POWER_ITERATION_HPP_
#define METII_INVERSE_POWER_ITERATION_HPP_

#include <utility>
#include "eigen/SquareMatrix.hpp"
#include "eigen/Vector.hpp"
#include "eigen/PowerIteration.hpp"

namespace metII {

    class InversePowerIteration : public metII::PowerIteration {

        public:

            InversePowerIteration ();

            std::pair<double, Vector> compute (metII::SquareMatrix matrix, double epsilon) override;

    };
    
}

#endif