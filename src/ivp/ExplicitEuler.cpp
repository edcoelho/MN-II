#include "ivp/ExplicitEuler.hpp"

metII::Vector metII::ExplicitEuler::step (double curr_t, metII::Vector curr_state) const {

    return curr_state + this->get_F()(curr_state, curr_t)*this->get_delta();

}

metII::ExplicitEuler::ExplicitEuler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t) : metII::Euler(_F, _initial_state, _delta, _initial_t) {}