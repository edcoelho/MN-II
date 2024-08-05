#ifndef METII_RUNGE_KUTTA_HPP 
#define METII_RUNGE_KUTTA_HPP

#include "ivp/SimpleStep.hpp"
#include "eigen/Vector.hpp"
#include <functional>

namespace metII {

    class RungeKutta : public metII::SimpleStep {

        private:

            std::function<metII::Vector(metII::Vector, double)> F;
            metII::Vector initial_state;
            double initial_t, delta;
            std::size_t order;

            metII::Vector step (double curr_t, metII::Vector curr_state) const override;

        public:

            std::size_t get_order () const;
            void set_order (std::size_t _order);

            RungeKutta (std::size_t order, std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t = 0.0);

    };

}

#endif