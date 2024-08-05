#include "ivp/ExplicitEuler.hpp"
#include "ivp/ImplicitEuler.hpp"
#include "ivp/RungeKutta.hpp"
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

    std::cout << std::endl;

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
    double delta = 0.0001, t_f = 1;
    metII::ExplicitEuler euler_method(ivp_1, s_0, delta);
    metII::Vector final_state = euler_method.compute_state(t_f);
    print_vector(final_state);

}

void test_explicit_euler_states () {

    metII::Vector s_0(1, 2);
    double delta = 0.0001, t_f = 1;
    metII::ExplicitEuler euler_method(ivp_1, s_0, delta);
    std::vector<metII::Vector> states = euler_method.compute_states(t_f);

    print_states(states, delta);

}

void test_explicit_euler_state_with_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.0001;
    metII::ExplicitEuler euler_method(ivp_2, s_0, delta);
    std::pair<metII::Vector, double> state_and_time = euler_method.compute_state_with_value(0.0);

    std::cout << "State at time t = " << state_and_time.second << ": " << std::endl;
    print_vector(state_and_time.first);

}

void test_explicit_euler_states_until_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.0001;
    metII::ExplicitEuler euler_method(ivp_2, s_0, delta);
    std::vector<metII::Vector> states = euler_method.compute_states_until_value(0.0);

    print_states(states, delta);

}

void test_implicit_euler_state () {

    metII::Vector s_0(1, 2);
    double delta = 0.0001, t_f = 1;
    metII::ImplicitEuler euler_method(ivp_1, s_0, delta);
    metII::Vector final_state = euler_method.compute_state(t_f);
    print_vector(final_state);

}

void test_implicit_euler_states () {

    metII::Vector s_0(1, 2);
    double delta = 0.0001, t_f = 1;
    metII::ImplicitEuler euler_method(ivp_1, s_0, delta);
    std::vector<metII::Vector> states = euler_method.compute_states(t_f);

    print_states(states, delta);

}

void test_implicit_euler_state_with_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.0001;
    metII::ImplicitEuler euler_method(ivp_2, s_0, delta);
    std::pair<metII::Vector, double> state_and_time = euler_method.compute_state_with_value(0.0);

    std::cout << "State at time t = " << state_and_time.second << ": " << std::endl;
    print_vector(state_and_time.first);

}

void test_implicit_euler_states_until_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.0001;
    metII::ImplicitEuler euler_method(ivp_2, s_0, delta);
    std::vector<metII::Vector> states = euler_method.compute_states_until_value(0.0);

    print_states(states, delta);

}

void test_runge_kutta_state () {

    metII::Vector s_0(1, 2);
    double delta = 0.0001, t_f = 1;
    metII::RungeKutta runge_kutta(2, ivp_1, s_0, delta);

    std::cout << "Runge-Kutta 2nd order:" << std::endl;
    print_vector(runge_kutta.compute_state(t_f));

    runge_kutta.set_order(3);
    std::cout << "Runge-Kutta 3rd order:" << std::endl;
    print_vector(runge_kutta.compute_state(t_f));

    runge_kutta.set_order(4);
    std::cout << "Runge-Kutta 4th order:" << std::endl;
    print_vector(runge_kutta.compute_state(t_f));

}

void test_runge_kutta_states () {

    metII::Vector s_0(1, 2);
    double delta = 0.0001, t_f = 1;
    metII::RungeKutta runge_kutta(2, ivp_1, s_0, delta);

    std::cout << "Runge-Kutta 2nd order:" << std::endl;
    print_states(runge_kutta.compute_states(t_f), delta);

    runge_kutta.set_order(3);
    std::cout << "Runge-Kutta 3rd order:" << std::endl;
    print_states(runge_kutta.compute_states(t_f), delta);

    runge_kutta.set_order(4);
    std::cout << "Runge-Kutta 4th order:" << std::endl;
    print_states(runge_kutta.compute_states(t_f), delta);

}

void test_runge_kutta_state_with_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.0001;
    metII::RungeKutta runge_kutta(2, ivp_2, s_0, delta);
    std::pair<metII::Vector, double> state_and_time = runge_kutta.compute_state_with_value(0.0);

    std::cout << "Runge-Kutta 2nd order:" << std::endl;
    std::cout << "State at time t = " << state_and_time.second << ": " << std::endl;
    print_vector(state_and_time.first);

    runge_kutta.set_order(3);
    state_and_time = runge_kutta.compute_state_with_value(0.0);
    std::cout << "Runge-Kutta 3rd order:" << std::endl;
    std::cout << "State at time t = " << state_and_time.second << ": " << std::endl;
    print_vector(state_and_time.first);

    runge_kutta.set_order(4);
    state_and_time = runge_kutta.compute_state_with_value(0.0);
    std::cout << "Runge-Kutta 4th order:" << std::endl;
    std::cout << "State at time t = " << state_and_time.second << ": " << std::endl;
    print_vector(state_and_time.first);

}

void test_runge_kutta_states_until_value () {

    metII::Vector s_0(std::vector<double>({150.0, 3.0}));
    double delta = 0.0001;
    metII::RungeKutta runge_kutta(2, ivp_2, s_0, delta);

    std::cout << "Runge-Kutta 2nd order:" << std::endl;
    print_states(runge_kutta.compute_states_until_value(0.0), delta);

    runge_kutta.set_order(3);
    std::cout << "Runge-Kutta 3rd order:" << std::endl;
    print_states(runge_kutta.compute_states_until_value(0.0), delta);

    runge_kutta.set_order(4);
    std::cout << "Runge-Kutta 4th order:" << std::endl;
    print_states(runge_kutta.compute_states_until_value(0.0), delta);

}

int main () {

    // test_explicit_euler_state();
    // test_runge_kutta_state();

    //test_runge_kutta_states();
    //test_explicit_euler_states();

    // test_explicit_euler_state_with_value();
    // test_runge_kutta_state_with_value();

    // test_explicit_euler_states_until_value();
    // test_runge_kutta_states_until_value();


}