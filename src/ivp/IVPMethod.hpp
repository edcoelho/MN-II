#ifndef METII_IVP_METHOD_HPP
#define METII_IVP_METHOD_HPP

#include "eigen/Vector.hpp"
#include <vector>
#include <functional>
#include <utility>
#include <limits>

namespace metII {

    class IVPMethod {

        private:

            std::function<metII::Vector(metII::Vector, double)> F;
            metII::Vector initial_state;
            double initial_t, delta;

        public:

            IVPMethod (std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t = 0.0);

            std::function<metII::Vector(metII::Vector, double)> get_F() const;
            const std::function<metII::Vector(metII::Vector, double)>& get_ref_F() const;
            void set_F(std::function<metII::Vector(metII::Vector, double)> _F);

            metII::Vector get_initial_state() const;
            void set_initial_state(metII::Vector _initial_state);

            double get_delta() const;
            void set_delta(double _delta);

            double get_initial_t() const;
            void set_initial_t(double _initial_t);

            // Returns the state at time "final_t"
            virtual metII::Vector compute_state (double final_t) const = 0;
            // Returns all states from the initial state to the state at time "final_t"
            virtual std::vector<metII::Vector> compute_states (double final_t) const = 0;
            // Returns a pair containing the state where the main value reaches "final_state_main_value" and the time at which this state occurs.
            virtual std::pair<metII::Vector, double> compute_state_with_value (double final_state_main_value = 0.0, const std::size_t max_steps = std::numeric_limits<std::size_t>::max()) const = 0;
            // Returns all states from the initial state to the state where the main value reaches "final_state_main_value".
            virtual std::vector<metII::Vector> compute_states_until_value (double final_state_main_value = 0.0, const std::size_t max_steps = std::numeric_limits<std::size_t>::max()) const = 0;

    };

};

#endif