#include "integration/GaussChebyshevIntegral.hpp"
#include <cmath>
#include <stdexcept>

metII::GaussChebyshevIntegral::GaussChebyshevIntegral (std::function<double(double)> _func, std::size_t num_of_gauss_points) : SpecialGaussIntegral(_func) {

    if (num_of_gauss_points >= 1) {

        this->weights = std::vector<double>(num_of_gauss_points, M_PI/num_of_gauss_points);
        this->roots = std::vector<double>(num_of_gauss_points, 0.0);

        switch (num_of_gauss_points) {

            case 1:

                this->roots[0] = 0.0;

                break;

            case 2:

                this->roots[0] = 1.0/M_SQRT2;
                this->roots[1] = -this->roots[0];

                break;

            case 3:

                this->roots[0] = std::sqrt(3.0)/2.0;
                this->roots[1] = 0.0;
                this->roots[2] = -this->roots[0];

                break;

            case 4:

                this->roots[0] = std::sqrt(2.0 + std::sqrt(2.0))/2.0;
                this->roots[1] = std::sqrt(2.0 - std::sqrt(2.0))/2.0;
                this->roots[2] = -this->roots[1];
                this->roots[3] = -this->roots[0];

                break;

            default:

                for (std::size_t i = 0; i < num_of_gauss_points; i++) {

                    this->roots[i] = std::cos((2.0*(i+1) - 1.0)*M_PI/(2.0*num_of_gauss_points));

                }

        }

    } else {

        throw std::invalid_argument("Error: It is not possible to instantiate the class metII::GaussChebyshevIntegral with num_of_gauss_points<1!");
        
    }

}