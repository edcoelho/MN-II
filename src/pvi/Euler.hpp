#ifndef METII_EULER_HPP
#define METII_EULER_HPP

#include "eigen/Vector.hpp"
#include <vector>
#include <functional>
#include <utility>

namespace metII {

    class Euler {

        private:

            std::function<metII::Vector(metII::Vector, double)> F;
            metII::Vector initial_state;
            double initial_t, delta;

            virtual metII::Vector step (double curr_t, metII::Vector curr_state) const = 0;

        public:

            Euler (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t = 0.0);

            std::function<metII::Vector(metII::Vector, double)> get_F() const;
            void set_F(std::function<metII::Vector(metII::Vector, double)> _F);

            metII::Vector get_initial_state() const;
            void set_initial_state(metII::Vector _initial_state);

            double get_delta() const;
            void set_delta(double _delta);

            double get_initial_t() const;
            void set_initial_t(double _initial_t);

            // Returns the state at time "final_t"
            metII::Vector compute_state (double final_t);
            // Returns all states from the initial state to the state at time "final_t"
            std::vector<metII::Vector> compute_states (double final_t);
            // Returns a pair containing the state where the main value reaches "final_state_main_value" and the time at which this state occurs.
            std::pair<metII::Vector, double> compute_state_with_value (double final_state_main_value = 0.0, const std::size_t max_steps = 1.0e6);
            // Returns all states from the initial state to the state where the main value reaches "final_state_main_value".
            std::vector<metII::Vector> compute_states_until_value (double final_state_main_value = 0.0, const std::size_t max_steps = 1.0e6);

    };

};

#endif