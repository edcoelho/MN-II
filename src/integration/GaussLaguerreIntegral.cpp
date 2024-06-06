#include "integration/GaussLaguerreIntegral.hpp"
#include <cmath>
#include <stdexcept>

metII::GaussLaguerreIntegral::GaussLaguerreIntegral (std::size_t num_of_gauss_points) : SpecialGaussIntegral() {

    switch (num_of_gauss_points) {

        case 1:

            this->weights = {1.0};
            this->roots = {1.0};

            break;

        case 2:

            this->weights = std::vector<double>(2, 0.0);
            this->roots = std::vector<double>(2, 0.0);

            this->weights[0] = (2.0 + M_SQRT2)/4.0;
            this->roots[0] = 2.0 - M_SQRT2;

            this->weights[1] = (2.0 - M_SQRT2)/4.0;
            this->roots[1] = 2.0 + M_SQRT2;

            break;

        case 3:

            this->weights = std::vector<double>(3, 0.0);
            this->roots = std::vector<double>(3, 0.0);

            this->weights[0] = 0.7110930099;
            this->roots[0] = 0.4157745568;

            this->weights[1] = 0.2785177336;
            this->roots[1] = 2.2942803603;

            this->weights[2] = 0.0103892565;
            this->roots[2] = 6.2899450829;

            break;

        case 4:

            this->weights = std::vector<double>(4, 0.0);
            this->roots = std::vector<double>(4, 0.0);
            
            this->weights[0] = 0.6031541043;
            this->roots[0] = 0.3225476896;

            this->weights[1] = 0.3574186924;
            this->roots[1] = 1.7457611012;

            this->weights[2] = 0.0388879085;
            this->roots[2] = 4.5366202969;

            this->weights[3] = 0.0005392947;
            this->roots[3] = 9.3950709123;

            break;

        default:

            throw std::invalid_argument("Error: It is not possible to instantiate the class metII::GaussLaguerreIntegral with num_of_gauss_points<1 or num_of_gauss_points>4!");

    }

}