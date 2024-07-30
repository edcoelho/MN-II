#ifndef METII_EXPLICIT_EULER_HPP
#define METII_EXPLICIT_EULER_HPP

#include "pvi/Euler.hpp"

namespace metII {
 
    class ExplicitEuler : public metII::Euler {

        private:

            metII::Vector step (double curr_t, metII::Vector curr_state) const override;

        public:

            ExplicitEuler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t = 0.0);

    };

}
 
#endif
