#ifndef METII_RUNGE_KUTTA_HPP 
#define METII_RUNGE_KUTTA_HPP

#include "eigen/Vector.hpp"
#include <functional>

namespace metII {
    class RungeKutta {
        private: 
            metII::Vector second_order_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f); 

            metII::Vector third_order_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f); 

            metII::Vector fourth_order_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f); 

        public: 
            RungeKutta();

            metII::Matrix compute (int order, double delta, double initial_t, double final_t, metII::Vector initial_state, std::function<metII::Vector(metII::Vector, double)> f, bool is_explicit_step = true);
    };
}

#endif