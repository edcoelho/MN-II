#include "pvi/ImplicitEuler.hpp"

metII::Vector metII::ImplicitEuler::step (double curr_t, metII::Vector curr_state) const {

    //TODO: vai usar newton rhapson
    return metII::Vector();

}

metII::ImplicitEuler::ImplicitEuler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t) : metII::Euler(_F, _initial_state, _delta, _initial_t) {}