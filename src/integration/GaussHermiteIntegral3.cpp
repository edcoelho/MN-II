#include "integration/GaussHermiteIntegral3.hpp"
#include <cmath>
#include <array>

metII::GaussHermiteIntegral3::GaussHermiteIntegral3 () : SpecialGaussIntegral() {

    this->weights = {std::sqrt(M_PI)/6.0, 2.0*std::sqrt(M_PI)/3.0, std::sqrt(M_PI)/6.0};
    this->roots = {-std::sqrt(3.0/2.0), 0.0, std::sqrt(3.0/2.0)};

}