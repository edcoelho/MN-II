#include "integration/GaussHermiteIntegral1.hpp"
#include <cmath>

metII::GaussHermiteIntegral1::GaussHermiteIntegral1 () : SpecialGaussIntegral() {

    this->weights = {std::sqrt(M_PI)};
    this->roots = {0.0};

}