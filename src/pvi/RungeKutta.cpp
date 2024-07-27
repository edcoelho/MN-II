#include "RungeKutta.hpp"
#include "Euler.hpp" 
#include <cmath>

metII::RungeKutta::RungeKutta() {

}

metII::Vector metII::RungeKutta::second_order_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f) {
    metII::Euler euler_method; 
    metII::Vector estimated_next_state = euler_method.compute(delta,0,0,last_state, f); // one iteration of euler
    return last_state + (f(last_state,t) + f(estimated_next_state, t))*(delta/2);
}

metII::Vector metII::RungeKutta::third_order_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f) {
    metII::Euler euler_method; 
}

metII::Vector metII::RungeKutta::fourth_order_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f) {

}

void fill_columns (metII::Matrix state_matrix, metII::Vector curr_state, int num_lines, int curr_column) {
    for (int i = 0; i < num_lines; i++) {
        state_matrix(i,curr_column) = curr_state[i]; 
    }
}

metII::Matrix metII::RungeKutta::compute (int order, double delta, double initial_t, double final_t, metII::Vector initial_state, std::function<metII::Vector(metII::Vector, double)> f, bool is_explicit_step) {
    metII::Vector curr_state = initial_state; 
    int num_columns = std::floor((final_t - initial_t)/delta) + 1 ; 
    int num_lines = curr_state.size(); 
    metII::Matrix state_matrix(num_lines, num_columns); 
    
    int curr_column = 0; 
    fill_columns (state_matrix, curr_state, num_lines, curr_column++); 
    for (double t = initial_t; t <= final_t; t += delta) {
        if (order == 2) {
            curr_state = second_order_step(delta, t, curr_state, f); 
        }

        if (order == 3) {
            curr_state = third_order_step(delta, t, curr_state, f); 
        }

        if (order == 4) {
            curr_state = fourth_order_step(delta, t, curr_state, f); 
        }
        fill_columns (state_matrix, curr_state, num_lines, curr_column++); 
    }

    return state_matrix; 
}