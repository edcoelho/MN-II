#include "pvi/ExplicitEuler.hpp"
#include <iostream>

//exemplo 1 das notas de aula
metII::Vector ivp_1 (metII::Vector state_vec, double t) {

    return state_vec*(2.0/3.0);

}

metII::Vector ivp_2 (metII::Vector state_vec, double t) {

    double g = 10.0, k = 0.5, m = 0.5;

    state_vec[0] = state_vec[1];
    state_vec[1] = -g - (k/m)*state_vec[1];

    return state_vec;

}

void print_vector (metII::Vector vector) {

    for (std::size_t index = 0; index < vector.size(); index++) {

        std::cout << vector[index] << std::endl;

    }

}

void print_states (std::vector<metII::Vector> states, double delta) {

    for (std::size_t i = 0; i < states.size(); i++) {

        std::cout << "State at time t = " << ((double) i) * delta << ": " << std::endl;
        print_vector(states[i]);
        std::cout << std::endl;

    }

}

void test_explicit_euler_state () {

    metII::Vector s_0(1, 2);
    double delta = 0.00001, t_f = 1;
    metII::ExplicitEuler euler_method(ivp_1, s_0, delta);
    metII::Vector final_state = euler_method.compute_state(t_f);
    print_vector(final_state);

}

void test_explicit_euler_states () {

    metII::Vector s_0(1, 2);
    double delta = 0.00001, t_f = 1;
    metII::ExplicitEuler euler_method(ivp_1, s_0, delta);
    std::vector<metII::Vector> states = euler_method.compute_states(t_f);

    print_states(states, delta);

}

void test_explicit_euler_state_with_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.1;
    metII::ExplicitEuler euler_method(ivp_2, s_0, delta);
    std::pair<metII::Vector, double> state_and_time = euler_method.compute_state_with_value(0.0);

    std::cout << "State at time t = " << state_and_time.second << ": " << std::endl;
    print_vector(state_and_time.first);

}

void test_explicit_euler_states_until_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.1;
    metII::ExplicitEuler euler_method(ivp_2, s_0, delta);
    std::vector<metII::Vector> states = euler_method.compute_states_until_value(0.0, 100000000000000);

    print_states(states, delta);

}

int main () {

    test_explicit_euler_state_with_value();

}