#ifndef EULER_HPP 
#define EULER_HPP 
#include "Vector.hpp"
#include <functional>

namespace metII{ 
    class Euler { 
        private: 
            metII::Vector explicit_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f); 

            metII::Vector implicit_step(double delta, double t, metII::Vector last_state, std::function<metII::Vector(metII::Vector, double)> f); 

        public: 
            Euler(); 
            // Will return a matrix with all the states, from s_0 to s_final_t
            metII::Matrix compute(double delta, double initial_t, double final_t, metII::Vector initial_state, std::function<metII::Vector(metII::Vector, double)> f, bool is_explicit_step = true); 
    };
} 
#endif
