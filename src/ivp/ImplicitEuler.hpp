#ifndef METII_IMPLICIT_EULER_HPP
#define METII_IMPLICIT_EULER_HPP

#include "ivp/Euler.hpp"

namespace metII {
 
    class ImplicitEuler : public metII::Euler {

        private:

            double root_epsilon, derivative_epsilon;

            metII::Vector step (double curr_t, metII::Vector curr_state) const override;

            metII::Vector new_state_equation (const metII::Vector& new_state, const metII::Vector& curr_state, const double& curr_t) const;
            metII::Vector new_state_equation_prime (const metII::Vector& new_state, const metII::Vector& curr_state, const double& curr_t) const;

        public:

            ImplicitEuler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t = 0.0, double _root_epsilon = 1.0e-6, double _derivative_epsilon = 1.0e-6);

            double get_root_epsilon () const;
            void set_root_epsilon (double _root_epsilon);

            double get_derivative_epsilon () const;
            void set_derivative_epsilon (double _derivative_epsilon);

    };

}
 
#endif
