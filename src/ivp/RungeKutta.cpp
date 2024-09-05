#include "ivp/RungeKutta.hpp"
#include "ivp/ExplicitEuler.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>

metII::Vector metII::RungeKutta::step (double curr_t, metII::Vector curr_state) const {

    std::vector<metII::Vector> estimated_states;
    metII::Vector next_state;
    metII::ExplicitEuler explicit_euler(this->get_F(), curr_state, this->get_delta(), curr_t);
    double delta_prime;

    if (this->get_order() == 2) {

        estimated_states = explicit_euler.compute_states(curr_t + this->get_delta());
        next_state = curr_state + (this->get_ref_F()(curr_state, curr_t) + this->get_ref_F()(estimated_states[1], curr_t + this->get_delta())) * (this->get_delta()/2.0);

    } else if (this->get_order() == 3) {

        delta_prime = this->get_delta()/2.0;
        explicit_euler.set_delta(delta_prime);
        estimated_states = explicit_euler.compute_states(curr_t + this->get_delta());
        next_state = curr_state + (this->get_ref_F()(curr_state, curr_t) + this->get_ref_F()(estimated_states[1], curr_t + delta_prime)*4.0 + this->get_ref_F()(estimated_states[2], curr_t + this->get_delta())) * (this->get_delta()/6.0);

    } else {

        delta_prime = this->get_delta()/3.0;
        explicit_euler.set_delta(delta_prime);
        estimated_states = explicit_euler.compute_states(curr_t + this->get_delta());
        next_state = curr_state + (this->get_ref_F()(curr_state, curr_t) + this->get_ref_F()(estimated_states[1], curr_t + delta_prime)*3.0 + this->get_ref_F()(estimated_states[2], curr_t + 2.0*delta_prime)*3.0 + this->get_ref_F()(estimated_states[3], curr_t + this->get_delta())) * (this->get_delta()/8.0);

    }

    return next_state;

}

metII::RungeKutta::RungeKutta (std::size_t _order, std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t) : metII::SimpleStep(_F, _initial_state, _delta, _initial_t) {

    if (_order < 2 || _order > 4) {

        throw std::runtime_error("Error in metII::RungeKutta::RungeKutta(std::size_t, std::function<metII::Vector(metII::Vector, double)>, metII::Vector, double, double): Invalid order! Please ensure that the order is 2, 3 or 4.");

    }


    this->order = _order;

}

std::size_t metII::RungeKutta::get_order () const {

    return this->order;

}
void metII::RungeKutta::set_order (std::size_t _order) {

    if (_order < 2 || _order > 4) {

        throw std::runtime_error("Error in (void) metII::RungeKutta::set_order(std::size_t): Invalid order! Please ensure that the order is 2, 3 or 4.");

    }

    this->order = _order;

}