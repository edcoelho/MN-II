#include "differentiation/CentralDerivative.hpp"
#include <stdexcept>
#include <cmath>

namespace metII {

    double CentralDerivative::first_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 2:
                result = ( -f(x - h) + f(x + h) ) / ( 2.0*h );
                break;

            case 4:
                result = ( f(x - 2.0*h) - 8.0*f(x - h) + 8.0*f(x + h) - f(x + 2.0*h) ) / ( 12.0*h );
                break;

            case 6:
                result = ( -f(x - 3.0*h) + 9.0*f(x - 2.0*h) - 45.0*f(x - h) + 45.0*f(x + h) - 9.0*f(x + 2.0*h) + f(x + 3.0*h) ) / ( 60.0*h );
                break;
            
        }

        return result;

    }

    double CentralDerivative::second_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 2:
                result = ( f(x-h) - 2.0*f(x) + f(x+h) ) / std::pow(h, 2.0);
                break;

            case 4:
                result = ( -f(x-2.0*h) + 16.0*f(x-h) - 30.0*f(x) + 16.0*f(x+h) - f(x+2.0*h) ) / ( 12.0*std::pow(h, 2.0) );
                break;

            case 6:
                result = ( 2.0*f(x-3.0*h) - 27.0*f(x-2.0*h) + 270.0*f(x-h) - 490.0*f(x) + 270.0*f(x+h) - 27.0*f(x+2.0*h) + 2.0*f(x+3.0*h) ) / ( 180.0*std::pow(h, 2.0) );
                break;

        }

        return result;

    }

    double CentralDerivative::third_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 2:
                result = ( -f(x - 2.0*h) + 2.0*f(x - h) - 2.0*f(x + h) + f(x + 2.0*h) ) / ( 2.0*std::pow(h, 3.0) );
                break;

            case 4:
                result = ( f(x - 3.0*h) - 8.0*f(x - 2.0*h) + 13.0*f(x - h) - 13.0*f(x + h) + 8.0*f(x + 2.0*h) - f(x + 3.0*h) ) / ( 8.0*std::pow(h, 3.0) );
                break;

            case 6:
                result = ( -7.0*f(x - 4.0*h) + 72.0*f(x - 3.0*h) - 338.0*f(x - 2.0*h) + 488.0*f(x - h) - 488.0*f(x + h) + 338.0*f(x + 2.0*h) - 72.0*f(x + 3.0*h) + 7.0*f(x + 4.0*h) ) / ( 240.0*std::pow(h, 3.0) );
                break;

        }

        return result;

    }

    double CentralDerivative::fourth_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 2:
                result = ( f(x - 2.0*h) - 4.0*f(x - h) + 6.0*f(x) - 4.0*f(x + h) + f(x + 2.0*h) ) / std::pow(h, 4.0);
                break;

            case 4:
                result = ( -f(x - 3.0*h) + 12.0*f(x - 2.0*h) - 39.0*f(x - h) + 56.0*f(x) - 39.0*f(x + h) + 12.0*f(x + 2.0*h) - f(x + 3.0*h) ) / (6.0*std::pow(h, 4.0));
                break;

            case 6:
                result = ( 7.0*f(x - 4.0*h) - 96.0*f(x - 3.0*h) + 676.0*f(x - 2.0*h) - 1952.0*f(x - h) + 2730.0*f(x) + - 1952.0*f(x + h) + 676.0*f(x + 2.0*h) - 96.0*f(x + 3.0*h) + 7.0*f(x + 4.0*h) ) / (240.0*std::pow(h, 4.0));
                break;

        }

        return result;

    }

    CentralDerivative::CentralDerivative (std::function<double(double)> _f, std::size_t _derivative_order, std::size_t _error_order, double _epsilon) : Derivative::Derivative(_f, _derivative_order, _error_order, _epsilon) {

        if (_derivative_order == 0 || _derivative_order > 4) {

            throw std::runtime_error("Error in metII::CentralDerivative::CentralDerivative(std::size_t, std::size_t, double): Invalid derivative order! Please ensure that the derivative order is 1, 2, 3 or 4 as the class does not support higher order derivatives.");

        }

        if (_error_order == 0 || _error_order > 6 || _error_order % 2 != 0) {

            throw std::runtime_error("Error in metII::CentralDerivative::CentralDerivative(std::size_t, std::size_t, double): Invalid error order! Please ensure that the error order is 2, 4 or 6 as the class does not support derivatives with a higher order error.");

        }

    }

}