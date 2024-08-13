#ifndef METII_PREDICTOR_CORRECTOR_HPP 
#define METII_PREDICTOR_CORRECTOR_HPP

#include "eigen/Vector.hpp"
#include "ivp/IVPMethod.hpp"
#include <vector>
#include <functional>
#include <limits>

namespace metII {

    class PredictorCorrector : public metII::IVPMethod {
        // de segunda ordem, k = 1
        // de terceira ordem k = 2
        // de quarta ordem k = 3
        private:

            std::size_t order;
            double correct_epsilon;

            metII::Vector predict (double first_t_in_curr_history, const std::vector<metII::Vector>& curr_history) const;
            metII::Vector correct (double first_t_in_curr_history, std::vector<metII::Vector> curr_history) const;
            std::vector<metII::Vector> step (double first_t_in_curr_history, const std::vector<metII::Vector>& curr_history) const;

        public:

            PredictorCorrector (std::size_t _order, std::function<metII::Vector(metII::Vector, double)> _F, metII::Vector _initial_state, double _delta, double _initial_t = 0.0, double _correct_epsilon = 1.0e-6);

            std::size_t get_order () const;
            void set_order (std::size_t _order);

            double get_correct_epsilon () const;
            void set_correct_epsilon (double _correct_epsilon);

            // Returns the state at time "final_t"
            virtual metII::Vector compute_state (double final_t) const;
            // Returns all states from the initial state to the state at time "final_t"
            virtual std::vector<metII::Vector> compute_states (double final_t) const;
            // Returns a pair containing the state where the main value reaches "final_state_main_value" and the time at which this state occurs.
            virtual std::pair<metII::Vector, double> compute_state_with_value (double final_state_main_value = 0.0, const std::size_t max_steps = std::numeric_limits<std::size_t>::max()) const;
            // Returns all states from the initial state to the state where the main value reaches "final_state_main_value".
            virtual std::vector<metII::Vector> compute_states_until_value (double final_state_main_value = 0.0, const std::size_t max_steps = std::numeric_limits<std::size_t>::max()) const;

    };
}

#endif