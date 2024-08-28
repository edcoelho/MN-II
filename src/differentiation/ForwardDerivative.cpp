#include "differentiation/ForwardDerivative.hpp"
#include <stdexcept>
#include <cmath>

namespace metII {

    double ForwardDerivative::first_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( -f(x) + f(x + h) ) / h;
                break;

            case 2:
                result = ( -3.0*f(x) + 4.0*f(x + h) - f(x + 2.0*h) ) / ( 2.0*h );
                break;

            case 3:
                result = ( -11.0*f(x) + 18.0*f(x + h) - 9.0*f(x + 2.0*h) + 2.0*f(x + 3.0*h) ) / ( 6.0*h );
                break;

            case 4:
                result = ( -25.0*f(x) + 48.0*f(x + h) - 36.0*f(x + 2.0*h) + 16.0*f(x + 3.0*h) - 3.0*f(x + 4.0*h) ) / ( 12.0*h );
                break;

            case 5:
                result = ( -137.0*f(x) + 300.0*f(x + h) - 300.0*f(x + 2.0*h) + 200.0*f(x + 3.0*h) - 75.0*f(x + 4.0*h) + 12.0*f(x + 5.0*h) ) / ( 60.0*h );
                break;

            case 6:
                result = ( -147.0*f(x) + 360.0*f(x + h) - 450.0*f(x + 2.0*h) + 400.0*f(x + 3.0*h) - 225.0*f(x + 4.0*h) + 72.0*f(x + 5.0*h) - 10.0*f(x + 6.0*h) ) / ( 60.0*h );
                break;
            
        }

        return result;

    }

    double ForwardDerivative::second_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( f(x) - 2.0*f(x + h) + f(x + 2.0*h) ) / std::pow(h, 2.0);
                break;

            case 2:
                result = ( 2.0*f(x) - 5.0*f(x + h) + 4.0*f(x + 2.0*h) - f(x + 3.0*h) ) / std::pow(h, 2.0);
                break;

            case 3:
                result = ( 35.0*f(x) - 104.0*f(x + h) + 114.0*f(x + 2.0*h) - 56.0*f(x + 3.0*h) + 11.0*f(x + 4.0*h) ) / ( 12.0*std::pow(h, 2.0) );
                break;

            case 4:
                result = ( 45.0*f(x) - 154.0*f(x + h) + 214.0*f(x + 2.0*h) - 156.0*f(x + 3.0*h) + 61.0*f(x + 4.0*h) - 10.0*f(x + 5.0*h) ) / ( 12.0*std::pow(h, 2.0) );
                break;

            case 5:
                result = ( 812.0*f(x) - 3132.0*f(x + h) + 5265.0*f(x + 2.0*h) - 5080.0*f(x + 3.0*h) + 2970.0*f(x + 4.0*h) - 972.0*f(x + 5.0*h) + 137.0*f(x + 6.0*h) ) / ( 180.0*std::pow(h, 2.0) );
                break;

            case 6:
                result = ( 938.0*f(x) - 4014.0*f(x + h) + 7911.0*f(x + 2.0*h) - 9490.0*f(x + 3.0*h) + 7380.0*f(x + 4.0*h) - 3618.0*f(x + 5.0*h) + 1019.0*f(x + 6.0*h) - 126.0*f(x + 7.0*h) ) / ( 180.0*std::pow(h, 2.0) );
                break;

        }

        return result;

    }

    double ForwardDerivative::third_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( -f(x) + 3.0*f(x + h) - 3.0*f(x + 2.0*h) + f(x + 3.0*h) ) / std::pow(h, 3.0);
                break;

            case 2:
                result = ( -5.0*f(x) + 18.0*f(x + h) - 24.0*f(x + 2.0*h) + 14.0*f(x + 3.0*h) - 3.0*f(x + 4.0*h) ) / ( 2.0*std::pow(h, 3.0) );
                break;

            case 3:
                result = ( -17.0*f(x) + 71.0*f(x + h) - 118.0*f(x + 2.0*h) + 98.0*f(x + 3.0*h) - 41.0*f(x + 4.0*h) + 7.0*f(x + 5.0*h) ) / ( 4.0*std::pow(h, 3.0) );
                break;

            case 4:
                result = ( -49.0*f(x) + 232.0*f(x + h) - 461.0*f(x + 2.0*h) + 496.0*f(x + 3.0*h) - 307.0*f(x + 4.0*h) + 104.0*f(x + 5.0*h) - 15.0*f(x + 6.0*h) ) / ( 8.0*std::pow(h, 3.0) );
                break;

            case 5:
                result = ( -967.0*f(x) + 5104.0*f(x + h) - 11787.0*f(x + 2.0*h) + 15560.0*f(x + 3.0*h) - 12725.0*f(x + 4.0*h) + 6432.0*f(x + 5.0*h) - 1849.0*f(x + 6.0*h) + 232.0*f(x + 7.0*h) ) / ( 120.0*std::pow(h, 3.0) );
                break;

            case 6:
                result = ( -2403.0*f(x) + 13960.0*f(x + h) - 36706.0*f(x + 2.0*h) + 57384.0*f(x + 3.0*h) - 58280.0*f(x + 4.0*h) + 39128.0*f(x + 5.0*h) - 16830.0*f(x + 6.0*h) + 4216.0*f(x + 7.0*h) - 469.0*f(x + 8.0*h) ) / ( 240.0*std::pow(h, 3.0) );
                break;

        }

        return result;

    }

    double ForwardDerivative::fourth_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( f(x) - 4.0*f(x + h) + 6.0*f(x + 2.0*h) - 4.0*f(x + 3.0*h) + f(x + 4.0*h) ) / std::pow(h, 4.0);
                break;

            case 2:
                result = ( 3.0*f(x) - 14.0*f(x + h) + 26.0*f(x + 2.0*h) - 24.0*f(x + 3.0*h) + 11.0*f(x + 4.0*h) - 2.0*f(x + 5.0*h) ) / std::pow(h, 4.0);
                break;

            case 3:
                result = ( 35.0*f(x) - 186.0*f(x + h) + 411.0*f(x + 2.0*h) - 484.0*f(x + 3.0*h) + 321.0*f(x + 4.0*h) - 114.0*f(x + 5.0*h) + 17.0*f(x + 6.0*h) ) / ( 6.0*std::pow(h, 4.0) );
                break;

            case 4:
                result = ( 56.0*f(x) - 333.0*f(x + h) + 852.0*f(x + 2.0*h) - 1219.0*f(x + 3.0*h) + 1056.0*f(x + 4.0*h) - 555.0*f(x + 5.0*h) + 164.0*f(x + 6.0*h) - 21.0*f(x + 7.0*h) ) / ( 6.0*std::pow(h, 4.0) );
                break;

            case 5:
                result = ( 3207.0*f(x) - 21056.0*f(x + h) + 61156.0*f(x + 2.0*h) - 102912.0*f(x + 3.0*h) + 109930.0*f(x + 4.0*h) - 76352.0*f(x + 5.0*h) + 33636.0*f(x + 6.0*h) - 8576.0*f(x + 7.0*h) + 967.0*f(x + 8.0*h) ) / ( 240.0*std::pow(h, 4.0) );
                break;

            case 6:
                result = ( 4275.0*f(x) - 30668.0*f(x + h) + 99604.0*f(x + 2.0*h) - 192624.0*f(x + 3.0*h) + 244498.0*f(x + 4.0*h) - 210920.0*f(x + 5.0*h) + 123348.0*f(x + 6.0*h) - 47024.0*f(x + 7.0*h) + 10579.0*f(x + 8.0*h) - 1068.0*f(x + 9.0*h) ) / ( 240.0*std::pow(h, 4.0) );
                break;

        }

        return result;

    }

    ForwardDerivative::ForwardDerivative (std::function<double(double)> _f, std::size_t _derivative_order, std::size_t _error_order, double _epsilon) : Derivative::Derivative(_f, _derivative_order, _error_order, _epsilon) {

        if (_derivative_order == 0 || _derivative_order > 4) {

            throw std::runtime_error("Error in metII::ForwardDerivative::ForwardDerivative(std::size_t, std::size_t, double): Invalid derivative order! Please ensure that the derivative order is 1, 2, 3 or 4 as the class does not support higher order derivatives.");

        }

        if (_error_order == 0 || _error_order > 6) {

            throw std::runtime_error("Error in metII::ForwardDerivative::ForwardDerivative(std::size_t, std::size_t, double): Invalid error order! Please ensure that the error order is between 1 and 6, inclusive, as the class does not support derivatives with a higher order error.");

        }

    }

}