#ifndef METII_INVERSE_POWER_ITERATION_HPP_
#define METII_INVERSE_POWER_ITERATION_HPP_

#include <utility>
#include "eigen/Matrix.hpp"
#include "eigen/Vector.hpp"
#include "eigen/PowerIteration.hpp"

namespace metII {

    class InversePowerIteration {

        private: 

            metII::Vector LU_solver(metII::Matrix L, metII::Matrix U, metII::Vector permutation_vector, metII::Vector b) const; 

        public:

            InversePowerIteration ();

            std::pair<double, Vector> compute (metII::Matrix matrix, double epsilon) const;

    };
    
}

#endif