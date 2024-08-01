#ifndef METII_PREDICTOR_CORRECTOR_HPP 
#define METII_PREDICTOR_CORRECTOR_HPP
#include "eigen/Vector.hpp"
#include <functional>


namespace metII {
    // realizar interpolação nos ultimos k+1 estados
    class PredictorCorrector {
        // de segunda ordem, k = 1
        // de terceira ordem k = 2
        // de quarta ordem k = 3
        private: 

        public: 
            metII::Matrix compute (int order, double delta, double initial_t, double final_t, double epsilon, metII::Vector initial_state, std::function<metII::Vector(metII::Vector, double)> f); 
    };
}
#endif 