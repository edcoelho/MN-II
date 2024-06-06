#include "integration/GaussHermiteIntegral4.hpp"
#include <cmath>
#include <array>

metII::GaussHermiteIntegral4::GaussHermiteIntegral4 () : SpecialGaussIntegral() {

    this->weights = std::vector<double>(4, 0.0);
    this->roots = std::vector<double>(4, 0.0);
    
    this->weights[0] = std::sqrt(M_PI)/(4.0*(3.0 - std::sqrt(6.0)));
    this->roots[0] = -std::sqrt((3.0 - std::sqrt(6.0))/2.0);

    this->weights[1] = std::sqrt(M_PI)/(4.0*(3.0 + std::sqrt(6.0)));
    this->roots[1] = -std::sqrt((3.0 + std::sqrt(6.0))/2.0);

    this->weights[2] = this->weights[0];
    this->roots[2] = -this->roots[0];

    this->weights[3] = this->weights[1];
    this->roots[3] = -this->roots[1];

}