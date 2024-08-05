#include "ivp/SimpleStep.hpp"
#include <cmath>

metII::SimpleStep::SimpleStep (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t) {

    this->F = _F;
    this->initial_state = _initial_state;
    this->delta = _delta;
    this->initial_t = _initial_t;

}

std::function<metII::Vector(metII::Vector, double)> metII::SimpleStep::get_F() const {

    return this->F;

}

const std::function<metII::Vector(metII::Vector, double)>& metII::SimpleStep::get_ref_F() const {

    return this->F;

}

void metII::SimpleStep::set_F(std::function<metII::Vector(metII::Vector, double)> _F) {

    this->F = _F;

}

metII::Vector metII::SimpleStep::get_initial_state() const {

    return this->initial_state;

}

void metII::SimpleStep::set_initial_state(metII::Vector _initial_state) {

    this->initial_state = _initial_state;

}

double metII::SimpleStep::get_delta() const {

    return this->delta;

}

void metII::SimpleStep::set_delta(double _delta) {

    this->delta = _delta;

}

double metII::SimpleStep::get_initial_t() const {

    return this->initial_t;

}

void metII::SimpleStep::set_initial_t(double _initial_t) {

    this->initial_t = _initial_t;

}

metII::Vector metII::SimpleStep::compute_state(double final_t) const {

    metII::Vector curr_state = this->get_initial_state();

    for (double t = this->get_initial_t(); t < final_t; t += this->get_delta()) {

        curr_state = this->step(t, curr_state);

    }

    return curr_state;

}

std::vector<metII::Vector> metII::SimpleStep::compute_states (double final_t) const {

    metII::Vector curr_state = this->get_initial_state();
    std::vector<metII::Vector> states;

    states.push_back(curr_state);

    for (double t = this->get_initial_t(); t < final_t; t += this->get_delta()) {

        curr_state = this->step(t, curr_state);
        states.push_back(curr_state);

    }

    return states;

}

std::pair<metII::Vector, double> metII::SimpleStep::compute_state_with_value (double final_state_main_value, const std::size_t max_steps) const {

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

std::vector<metII::Vector> metII::SimpleStep::compute_states_until_value (double final_state_main_value, const std::size_t max_steps) const {

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