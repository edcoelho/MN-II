#include "integration/GaussHermiteIntegral.hpp"
#include <cmath>
#include <stdexcept>

metII::GaussHermiteIntegral::GaussHermiteIntegral (std::size_t num_of_gauss_points) : SpecialGaussIntegral() {

    switch (num_of_gauss_points) {

        case 1:

            this->weights = {std::sqrt(M_PI)};
            this->roots = {0.0};

            break;

        case 2:

            this->weights = std::vector<double>(2, 0.0);
            this->roots = std::vector<double>(2, 0.0);

            this->weights[0] = std::sqrt(M_PI)/2.0;
            this->roots[0] = -1.0/M_SQRT2;

            this->weights[1] = this->weights[0];
            this->roots[1] = -this->roots[0];

            break;

        case 3:

            this->weights = std::vector<double>(3, 0.0);
            this->roots = std::vector<double>(3, 0.0);

            this->weights[0] = std::sqrt(M_PI)/6.0;
            this->roots[0] = -std::sqrt(3.0/2.0);

            this->weights[1] = 2.0*std::sqrt(M_PI)/3.0;
            this->roots[1] = 0.0;

            this->weights[2] = this->weights[0];
            this->roots[2] = -this->roots[0];

            break;

        case 4:

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

            break;

        default:

            throw std::invalid_argument("Error: It is not possible to instantiate the class metII::GaussHermiteIntegral with num_of_gauss_points<1 or num_of_gauss_points>4!");

    }

}