#include "pvi/ImplicitEuler.hpp"
#include <cmath>

metII::Vector metII::ImplicitEuler::step (double curr_t, metII::Vector curr_state) const {

    std::function<metII::Vector(metII::Vector)> g, dg_dnew_state;
    std::function<metII::Vector(metII::Vector, double)> F = this->get_F();
    double
        epsilon = this->get_root_epsilon(),
        sum_of_relative_errors = 1.0;
    metII::Vector
        curr_root_state(curr_state.size()), // Current root in Newton-Raphson iteration
        new_root_state(curr_state.size()), // New root in Newton-Raphson iteration
        f_state(curr_state.size()), // f(x) in Newton-Raphson iteration
        f_prime_state(curr_state.size()); // f'(x) in Newton-Raphson iteration

    // Numerical root-finding
    while (sum_of_relative_errors > epsilon) {

        f_state = new_state_equation(curr_root_state, curr_state, curr_t);
        f_prime_state = new_state_equation_prime(curr_root_state, curr_state, curr_t);

        sum_of_relative_errors = 0.0;
        for (std::size_t i = 0; i < new_root_state.size(); i++) {

            // Newton-Raphson iteration
            new_root_state[i] = curr_root_state[i] - (f_state[i] / f_prime_state[i]);

            sum_of_relative_errors += std::abs((new_root_state[i] - curr_root_state[i]) / new_root_state[i]);

        }

        //relative_error = std::abs((new_root_state.norm() - curr_root_state.norm()) / new_root_state.norm());
        //relative_error = std::abs((new_root_state[0] - curr_root_state[0]) / new_root_state[0]);

        curr_root_state = new_root_state;

    }

    return new_root_state;

}

metII::Vector metII::ImplicitEuler::new_state_equation (const metII::Vector& new_state, const metII::Vector& curr_state, const double& curr_t) const {

    return new_state - curr_state - this->get_ref_F()(new_state, curr_t + this->get_delta()) * this->get_delta();

}

metII::Vector metII::ImplicitEuler::new_state_equation_prime (const metII::Vector& new_state, const metII::Vector& curr_state, const double& curr_t) const {

    double
        h = 0.1,
        epsilon = this->get_derivative_epsilon(),
        sum_of_relative_errors = 1.0;
    metII::Vector
        new_state_prime = new_state,
        curr_state_prime = new_state;

    // Numerical differentiation
    while (sum_of_relative_errors > epsilon) {

        // Foward differentiation
        new_state_prime = (this->new_state_equation(new_state + metII::Vector(new_state.size(), h), curr_state, curr_t) - this->new_state_equation(new_state, curr_state, curr_t)) * (1.0/h);

        sum_of_relative_errors = 0.0;
        for (std::size_t i = 0; i < new_state_prime.size(); i++) {

            sum_of_relative_errors += std::abs((new_state_prime[i] - curr_state_prime[i]) / new_state_prime[i]);

        }

        //relative_error = std::abs((new_state_prime.norm() - curr_state_prime.norm()) / new_state_prime.norm());
        //relative_error = std::abs((new_state_prime[0] - curr_state_prime[0]) / new_state_prime[0]);

        curr_state_prime = new_state_prime;
        h = h * h;

    }

    return new_state_prime;

}

metII::ImplicitEuler::ImplicitEuler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t, double _root_epsilon, double _derivative_epsilon) : metII::Euler(_F, _initial_state, _delta, _initial_t) {

    this->root_epsilon = _root_epsilon;
    this->derivative_epsilon = _derivative_epsilon;

}

double metII::ImplicitEuler::get_root_epsilon () const {

    return this->root_epsilon;

}
void metII::ImplicitEuler::set_root_epsilon (double _root_epsilon) {

    this->root_epsilon = _root_epsilon;

}

double metII::ImplicitEuler::get_derivative_epsilon () const {

    return this->derivative_epsilon;

}
void metII::ImplicitEuler::set_derivative_epsilon (double _derivative_epsilon) {

    this->derivative_epsilon = _derivative_epsilon;

}