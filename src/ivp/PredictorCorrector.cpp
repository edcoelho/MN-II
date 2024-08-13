#include "ivp/PredictorCorrector.hpp"
#include "ivp/RungeKutta.hpp"
#include <stdexcept>
#include <vector>

#include <iostream>
using namespace std;

metII::PredictorCorrector::PredictorCorrector (std::size_t _order, std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t, double _correct_epsilon) : metII::IVPMethod(_F, _initial_state, _delta, _initial_t) {

    if (_order < 2 || _order > 4) {

        throw std::runtime_error("Error in metII::PredictorCorrector::PredictorCorrector(std::size_t, std::vector<metII::Vector>, std::function<metII::Vector(metII::Vector, double)>, metII::Vector, double, double): Invalid order! Please ensure that the order is 2, 3 or 4.");

    }

    this->order = _order;
    this->correct_epsilon = _correct_epsilon;

}

metII::Vector metII::PredictorCorrector::predict (double first_t_in_curr_history, const std::vector<metII::Vector>& curr_history) const {

    metII::Vector new_state;

    if (this->get_order() == 2) {

        new_state = curr_history[1] + (this->get_ref_F()(curr_history[0], first_t_in_curr_history)*(-1.0) + this->get_ref_F()(curr_history[1], first_t_in_curr_history + this->get_delta())*3.0)*(this->get_delta()/2.0);

    } else if (this->get_order() == 3) {

        new_state = curr_history[2] + (this->get_ref_F()(curr_history[0], first_t_in_curr_history)*5.0 - this->get_ref_F()(curr_history[1], first_t_in_curr_history + this->get_delta())*16.0 + this->get_ref_F()(curr_history[2], first_t_in_curr_history + this->get_delta()*2.0)*23.0)*(this->get_delta()/12.0);

    } else {

        new_state = curr_history[3] + (this->get_ref_F()(curr_history[0], first_t_in_curr_history)*(-9.0) + this->get_ref_F()(curr_history[1], first_t_in_curr_history + this->get_delta())*37.0 - this->get_ref_F()(curr_history[2], first_t_in_curr_history + this->get_delta()*2.0)*59.0 + this->get_ref_F()(curr_history[3], first_t_in_curr_history + this->get_delta()*3.0)*55.0)*(this->get_delta()/24.0);

    }

    return new_state;

}

metII::Vector metII::PredictorCorrector::correct (double first_t_in_curr_history, std::vector<metII::Vector> curr_history) const {

    double
        epsilon = this->get_correct_epsilon(),
        sum_of_relative_errors = epsilon + 1.0;
    metII::Vector new_state;

    while (sum_of_relative_errors > epsilon) {

        if (this->get_order() == 2) {

            new_state = curr_history[0] + (this->get_ref_F()(curr_history[0], first_t_in_curr_history) + this->get_ref_F()(curr_history[1], first_t_in_curr_history + this->get_delta()))*(this->get_delta()/2.0);

        } else if (this->get_order() == 3) {

            new_state = curr_history[1] + (this->get_ref_F()(curr_history[0], first_t_in_curr_history)*(-1.0) + this->get_ref_F()(curr_history[1], first_t_in_curr_history + this->get_delta())*8.0 + this->get_ref_F()(curr_history[2], first_t_in_curr_history + this->get_delta()*2.0)*5.0)*(this->get_delta()/12.0);

        } else {

            new_state = curr_history[2] + (this->get_ref_F()(curr_history[0], first_t_in_curr_history) - this->get_ref_F()(curr_history[1], first_t_in_curr_history + this->get_delta())*5.0 + this->get_ref_F()(curr_history[2], first_t_in_curr_history + this->get_delta()*2.0)*19.0 + this->get_ref_F()(curr_history[3], first_t_in_curr_history + this->get_delta()*3.0)*9.0)*(this->get_delta()/24.0);
            
        }

        sum_of_relative_errors = 0.0;
        for (std::size_t i = 0; i < new_state.size(); i++) {

            sum_of_relative_errors += std::abs((new_state[i] - curr_history.back()[i]) / new_state[i]);

        }

        curr_history.back() = new_state;

    }

    return new_state;

}

std::vector<metII::Vector> metII::PredictorCorrector::step (double first_t_in_curr_history, const std::vector<metII::Vector>& curr_history) const {

    std::vector<metII::Vector> new_history(curr_history.begin() + 1, curr_history.end());

    new_history.push_back(this->predict(first_t_in_curr_history, curr_history));
    new_history.back() = this->correct(first_t_in_curr_history + this->get_delta(), new_history);

    return new_history;

}

std::size_t metII::PredictorCorrector::get_order () const {

    return this->order;

}
void metII::PredictorCorrector::set_order (std::size_t _order) {

    if (_order < 2 || _order > 4) {

        throw std::runtime_error("Error in (void) metII::PredictorCorrector::set_order(std::size_t): Invalid order! Please ensure that the order is 2, 3 or 4.");

    }

    this->order = _order;

}

double metII::PredictorCorrector::get_correct_epsilon () const {

    return this->correct_epsilon;

}
void metII::PredictorCorrector::set_correct_epsilon (double _correct_epsilon) {

    this->correct_epsilon = _correct_epsilon;

}

metII::Vector metII::PredictorCorrector::compute_state(double final_t) const {

    metII::RungeKutta rk(this->get_order(), this->get_F(), this->get_initial_state(), this->get_delta(), this->get_initial_t());
    std::vector<metII::Vector> curr_history;

    curr_history = rk.compute_states(this->get_initial_t() + ((double) this->get_order() - 1.0)*this->get_delta());

    double first_t_in_final_history = final_t - ((double) this->get_order() - 1.0)*this->get_delta();
    for (double first_t_in_curr_history = this->get_initial_t(); first_t_in_curr_history < first_t_in_final_history; first_t_in_curr_history += this->get_delta()) {

        curr_history = this->step(first_t_in_curr_history, curr_history);

    }

    return curr_history.back();

}

std::vector<metII::Vector> metII::PredictorCorrector::compute_states (double final_t) const {

    metII::RungeKutta rk(this->get_order(), this->get_F(), this->get_initial_state(), this->get_delta(), this->get_initial_t());
    std::vector<metII::Vector> curr_history, states;

    curr_history = rk.compute_states(this->get_initial_t() + ((double) this->get_order() - 1.0)*this->get_delta());
    states = curr_history;

    double first_t_in_final_history = final_t - ((double) this->get_order() - 1.0)*this->get_delta();
    for (double first_t_in_curr_history = this->get_initial_t(); first_t_in_curr_history < first_t_in_final_history; first_t_in_curr_history += this->get_delta()) {

        curr_history = this->step(first_t_in_curr_history, curr_history);
        states.push_back(curr_history.back());

    }

    return states;

}

std::pair<metII::Vector, double> metII::PredictorCorrector::compute_state_with_value (double final_state_main_value, const std::size_t max_steps) const {

    metII::RungeKutta rk(this->get_order(), this->get_F(), this->get_initial_state(), this->get_delta(), this->get_initial_t());
    std::vector<metII::Vector> curr_history;
    double curr_diff_values, prev_diff_values, t = this->get_initial_t();
    bool did_diff_signal_changed = false;
    std::size_t curr_step = 0;

    curr_history = rk.compute_states(this->get_initial_t() + ((double) this->get_order() - 1)*this->get_delta());

    prev_diff_values = curr_history[0][0] - final_state_main_value;

    // Checks if the signal changed in initialization.
    std::size_t i = 1;
    while (!did_diff_signal_changed && i < curr_history.size()) {

        curr_diff_values = curr_history[i][0] - final_state_main_value;
        did_diff_signal_changed = (prev_diff_values >= 0 && curr_diff_values < 0) || (prev_diff_values < 0 && curr_diff_values >=0);
        prev_diff_values = curr_diff_values;

        t += this->get_delta();
        i++;

    }

    // Checks if the signal changed in next states.
    while (!did_diff_signal_changed && curr_step < max_steps) {

        curr_history = this->step(t, curr_history);

        curr_diff_values = curr_history.back()[0] - final_state_main_value;
        did_diff_signal_changed = (prev_diff_values >= 0 && curr_diff_values < 0) || (prev_diff_values < 0 && curr_diff_values >=0);
        prev_diff_values = curr_diff_values;

        t += this->get_delta();
        curr_step++;

    }

    return std::pair<metII::Vector, double>(curr_history.back(), t);

}

std::vector<metII::Vector> metII::PredictorCorrector::compute_states_until_value (double final_state_main_value, const std::size_t max_steps) const {

    metII::RungeKutta rk(this->get_order(), this->get_F(), this->get_initial_state(), this->get_delta(), this->get_initial_t());
    std::vector<metII::Vector> curr_history, states;
    double curr_diff_values, prev_diff_values, t = this->get_initial_t();
    bool did_diff_signal_changed = false;
    std::size_t curr_step = 0;

    curr_history = rk.compute_states(this->get_initial_t() + ((double) this->get_order() - 1)*this->get_delta());
    states.push_back(curr_history[0]);

    prev_diff_values = curr_history[0][0] - final_state_main_value;

    // Checks if the signal changed in initialization.
    std::size_t i = 1;
    while (!did_diff_signal_changed && i < curr_history.size()) {

        states.push_back(curr_history[i]);

        curr_diff_values = curr_history[i][0] - final_state_main_value;
        did_diff_signal_changed = (prev_diff_values >= 0 && curr_diff_values < 0) || (prev_diff_values < 0 && curr_diff_values >=0);
        prev_diff_values = curr_diff_values;

        t += this->get_delta();
        i++;

    }

    // Checks if the signal changed in next states.
    while (!did_diff_signal_changed && curr_step < max_steps) {

        curr_history = this->step(t, curr_history);
        states.push_back(curr_history.back());

        curr_diff_values = curr_history.back()[0] - final_state_main_value;
        did_diff_signal_changed = (prev_diff_values >= 0 && curr_diff_values < 0) || (prev_diff_values < 0 && curr_diff_values >=0);
        prev_diff_values = curr_diff_values;

        t += this->get_delta();
        curr_step++;

    }

    return states;

}