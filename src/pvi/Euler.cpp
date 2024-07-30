#include "Euler.hpp"
#include <cmath>

metII::Euler::Euler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t) {

    this->F = _F;
    this->initial_state = _initial_state;
    this->delta = _delta;
    this->initial_t = _initial_t;

}

std::function<metII::Vector(metII::Vector, double)> metII::Euler::get_F() const {

    return this->F;

}

void metII::Euler::set_F(std::function<metII::Vector(metII::Vector, double)> _F) {

    this->F = _F;

}

metII::Vector metII::Euler::get_initial_state() const {

    return this->initial_state;

}

void metII::Euler::set_initial_state(metII::Vector _initial_state) {

    this->initial_state = _initial_state;

}

double metII::Euler::get_delta() const {

    return this->delta;

}

void metII::Euler::set_delta(double _delta) {

    this->delta = _delta;

}

double metII::Euler::get_initial_t() const {

    return this->initial_t;

}

void metII::Euler::set_initial_t(double _initial_t) {

    this->initial_t = _initial_t;

}

metII::Vector metII::Euler::compute_state(double final_t) {

    metII::Vector curr_state = this->get_initial_state();

    for (double t = this->get_initial_t(); t < final_t; t += this->get_delta()) {

        curr_state = this->step(t, curr_state);

    }

    return curr_state;

}

std::vector<metII::Vector> metII::Euler::compute_states(double final_t) {

    metII::Vector curr_state = this->get_initial_state();
    int num_of_states = std::floor((final_t - initial_t)/delta) + 1;
    std::vector<metII::Vector> states(num_of_states, metII::Vector(curr_state.size()));

    int curr_state_index = 0;
    states[curr_state_index] = curr_state;
    curr_state_index++;

    for (double t = this->get_initial_t(); t < final_t; t += this->get_delta()) {

        curr_state = this->step(t, curr_state);
        states[curr_state_index] = curr_state;
        curr_state_index++;

    }

    return states;

}

std::pair<metII::Vector, double> metII::Euler::compute_state_with_value (double final_state_main_value, const std::size_t max_steps) {

    metII::Vector curr_state = this->get_initial_state();
    double curr_diff_values, prev_diff_values, t = this->get_initial_t();
    bool did_diff_signal_changed = false;
    std::size_t curr_step = 0;

    prev_diff_values = curr_state[0] - final_state_main_value;

    while (!did_diff_signal_changed && curr_step < max_steps) {

        curr_state = this->step(t, curr_state);

        curr_diff_values = curr_state[0] - final_state_main_value;
        did_diff_signal_changed = (prev_diff_values >= 0 && curr_diff_values < 0) || (prev_diff_values < 0 && curr_diff_values >=0);
        prev_diff_values = curr_diff_values;

        t += this->get_delta();
        curr_step++;

    }

    return std::pair<metII::Vector, double>(curr_state, t);

}

std::vector<metII::Vector> metII::Euler::compute_states_until_value (double final_state_main_value, const std::size_t max_steps) {

    metII::Vector curr_state = this->get_initial_state();
    std::vector<metII::Vector> states;
    double curr_diff_values, prev_diff_values, t = this->get_initial_t();
    bool did_diff_signal_changed = false;
    std::size_t curr_step = 0;

    states.push_back(curr_state);
    prev_diff_values = curr_state[0] - final_state_main_value;

    while (!did_diff_signal_changed && curr_step < max_steps) {

        curr_state = this->step(t, curr_state);
        states.push_back(curr_state);

        curr_diff_values = curr_state[0] - final_state_main_value;
        did_diff_signal_changed = (prev_diff_values >= 0 && curr_diff_values < 0) || (prev_diff_values < 0 && curr_diff_values >=0);
        prev_diff_values = curr_diff_values;

        t += this->get_delta();
        curr_step++;

    }

    return states;

}