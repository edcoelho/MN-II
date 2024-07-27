#include "Euler.hpp"
#include <cmath>

metII::Euler::Euler () {

}

metII::Vector metII::Euler::explicit_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f) {
    return last_state + f(last_state, t)*delta;  
}

metII::Vector metII::Euler::implicit_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f) {
    //TODO: vai usar newton rhapson
}

void fill_columns (metII::Matrix state_matrix, metII::Vector curr_state, int num_lines, int curr_column) {
    for (int i = 0; i < num_lines; i++) {
        state_matrix(i,curr_column) = curr_state[i]; 
    }
}

metII::Matrix metII::Euler::compute(double delta, double initial_t, double final_t, metII::Vector initial_state, std::function<metII::Vector(metII::Vector, double)> f, bool is_explicit_step = true) {
    metII::Vector curr_state = initial_state; 
    int num_columns = std::floor((final_t - initial_t)/delta) + 1 ; 
    int num_lines = curr_state.size(); 
    metII::Matrix state_matrix(num_lines, num_columns); 
    
    int curr_column = 0; 
    fill_columns (state_matrix, curr_state, num_lines, curr_column++); 
    for (double t = initial_t; t <= final_t; t += delta) {
        if (is_explicit_step) {
            curr_state = explicit_step(delta, t, curr_state, f); 
        }
        else { 
            curr_state = implicit_step(delta, t, curr_state, f);
        }
        fill_columns (state_matrix, curr_state, num_lines, curr_column++); 
    }
    return state_matrix; 
}   