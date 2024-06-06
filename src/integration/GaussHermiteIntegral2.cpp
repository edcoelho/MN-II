#include "integration/GaussHermiteIntegral2.hpp"
#include <cmath>
#include <array>

metII::GaussHermiteIntegral2::GaussHermiteIntegral2 () : SpecialGaussIntegral() {

    this->weights = {std::sqrt(M_PI)/2.0, std::sqrt(M_PI)/2.0};
    this->roots = {-1.0/M_SQRT2, 1.0/M_SQRT2};


}