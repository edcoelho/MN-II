#include "pvi/Euler.hpp"

//exemplo 1 das notas de aula
metII::Vector iteration_function (metII::Vector state_vec, double t) {
    return state_vec*(2/3); 
}

int main () {
    metII::Euler euler_method; 
    metII::Vector s_0(1, 2);  
    double delta = 0.5, t_0 = 0, t_f = 1; 
    euler_method.compute(delta, t_0, t_f, s_0, iteration_function); 
}