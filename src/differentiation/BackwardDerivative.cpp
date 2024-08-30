#include "differentiation/BackwardDerivative.hpp"
#include <stdexcept>
#include <cmath>

namespace metII {

    double BackwardDerivative::first_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( -f(x - h) + f(x) ) / h;
                break;

            case 2:
                result = ( f(x - 2.0*h) - 4.0*f(x - h) + 3.0*f(x) ) / ( 2.0*h );
                break;

            case 3:
                result = ( -2.0*f(x - 3.0*h) + 9.0*f(x - 2.0*h) - 18.0*f(x - h) + 11.0*f(x) ) / ( 6.0*h );
                break;

            case 4:
                result = ( 3.0*f(x - 4.0*h) - 16.0*f(x - 3.0*h) + 36.0*f(x - 2.0*h) - 48.0*f(x - h) + 25.0*f(x) ) / ( 12.0*h );
                break;

            case 5:
                result = ( -12.0*f(x - 5.0*h) + 75.0*f(x - 4.0*h) - 200.0*f(x - 3.0*h) + 300.0*f(x - 2.0*h) - 300.0*f(x - h) + 137.0*f(x) ) / ( 60.0*h );
                break;

            case 6:

                result = ( 10.0*f(x - 6.0*h) - 72.0*f(x - 5.0*h) + 225.0*f(x - 4.0*h) - 400.0*f(x - 3.0*h) + 450.0*f(x - 2.0*h) - 360.0*f(x - h) + 147.0*f(x) ) / ( 60.0*h );
                break;
            
        }

        return result;

    }

    double BackwardDerivative::second_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( f(x - 2.0*h) - 2.0*f(x - h) + f(x) ) / std::pow(h, 2.0);
                break;

            case 2:
                result = ( -f(x - 3.0*h) + 4.0*f(x - 2.0*h) - 5.0*f(x - h) + 2.0*f(x) ) / std::pow(h, 2.0);
                break;

            case 3:
                result = ( 11.0*f(x - 4.0*h) - 56.0*f(x - 3.0*h) + 114.0*f(x - 2.0*h) - 104.0*f(x - h) + 35.0*f(x) ) / ( 12.0*std::pow(h, 2.0) );
                break;

            case 4:
                result = ( -10.0*f(x - 5.0*h) + 61.0*f(x - 4.0*h) - 156.0*f(x - 3.0*h) + 214.0*f(x - 2.0*h) - 154.0*f(x - h) + 45.0*f(x) ) / ( 12.0*std::pow(h, 2.0) );
                break;

            case 5:
                result = ( 137.0*f(x - 6.0*h) - 972.0*f(x - 5.0*h) + 2970.0*f(x - 4.0*h) - 5080.0*f(x - 3.0*h) + 5265.0*f(x - 2.0*h) - 3132.0*f(x - h) + 812.0*f(x) ) / ( 180.0*std::pow(h, 2.0) );
                break;

            case 6:
                result = ( -126.0*f(x - 7.0*h) + 1019.0*f(x - 6.0*h) - 3618.0*f(x - 5.0*h) + 7380.0*f(x - 4.0*h) - 9490.0*f(x - 3.0*h) + 7911.0*f(x - 2.0*h) - 4014.0*f(x - h) + 938.0*f(x) ) / ( 180.0*std::pow(h, 2.0) );
                break;

        }

        return result;

    }

    double BackwardDerivative::third_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( -f(x - 3.0*h) + 3.0*f(x - 2.0*h) - 3.0*f(x - h) + f(x) ) / std::pow(h, 3.0);
                break;

            case 2:
                result = ( 3.0*f(x - 4.0*h) - 14.0*f(x - 3.0*h) + 24.0*f(x - 2.0*h) - 18.0*f(x - h) + 5.0*f(x) ) / ( 2.0*std::pow(h, 3.0) );
                break;

            case 3:
                result = ( -7.0*f(x - 5.0*h) + 41.0*f(x - 4.0*h) - 98.0*f(x - 3.0*h) + 118.0*f(x - 2.0*h) - 71.0*f(x - h) + 17.0*f(x) ) / ( 4.0*std::pow(h, 3.0) );
                break;

            case 4:
                result = ( 15.0*f(x - 6.0*h) - 104.0*f(x - 5.0*h) + 307.0*f(x - 4.0*h) - 496.0*f(x - 3.0*h) + 461.0*f(x - 2.0*h) - 232.0*f(x - h) + 49.0*f(x) ) / ( 8.0*std::pow(h, 3.0) );

            case 5:
                result = ( -232.0*f(x - 7.0*h) + 1849.0*f(x - 6.0*h) - 6432.0*f(x - 5.0*h) + 12725.0*f(x - 4.0*h) - 15560.0*f(x - 3.0*h) + 11787.0*f(x - 2.0*h) - 5104.0*f(x - h) + 967.0*f(x) ) / ( 120.0*std::pow(h, 3.0) );
                break;

            case 6:
                result = ( 469.0*f(x - 8.0*h) - 4216.0*f(x - 7.0*h) + 16830.0*f(x - 6.0*h) - 39128.0*f(x - 5.0*h) + 58280.0*f(x - 4.0*h) - 57384.0*f(x - 3.0*h) + 36706.0*f(x - 2.0*h) - 13960.0*f(x - h) + 2403.0*f(x) ) / ( 240.0*std::pow(h, 3.0) );
                break;

        }

        return result;

    }

    double BackwardDerivative::fourth_derivative (const double x, const double h) const {

        double result;
        std::function<double(double)> f = this->get_f();

        switch (this->get_error_order()) {

            case 1:
                result = ( f(x - 4.0*h) - 4.0*f(x - 3.0*h) + 6.0*f(x - 2.0*h) - 4.0*f(x - h) + f(x) ) / std::pow(h, 4.0);
                break;

            case 2:
                result = ( -2.0*f(x - 5.0*h) + 11.0*f(x - 4.0*h) - 24.0*f(x - 3.0*h) + 26.0*f(x - 2.0*h) - 14.0*f(x - h) + 3.0*f(x) ) / std::pow(h, 4.0);
                break;

            case 3:
                result = ( 17.0*f(x - 6.0*h) - 114.0*f(x - 5.0*h) + 321.0*f(x - 4.0*h) - 484.0*f(x - 3.0*h) + 411.0*f(x - 2.0*h) - 186.0*f(x - h) + 35.0*f(x) ) / ( 6.0*std::pow(h, 4.0) );
                break;

            case 4:
                result = ( -21.0*f(x - 7.0*h) + 164.0*f(x - 6.0*h) - 555.0*f(x - 5.0*h) + 1056.0*f(x - 4.0*h) - 1219.0*f(x - 3.0*h) + 852.0*f(x - 2.0*h) - 333.0*f(x - h) + 56.0*f(x) ) / ( 6.0*std::pow(h, 4.0) );
                break;

            case 5:
                result = ( 967.0*f(x - 8.0*h) - 8576.0*f(x - 7.0*h) + 33636.0*f(x - 6.0*h) - 76352.0*f(x - 5.0*h) + 109930.0*f(x - 4.0*h) - 102912.0*f(x - 3.0*h) + 61156.0*f(x - 2.0*h) - 21056.0*f(x - h) + 3207.0*f(x) ) / ( 240.0*std::pow(h, 4.0) );
                break;

            case 6:
                result = ( -1068.0*f(x - 9.0*h) + 10579.0*f(x - 8.0*h) - 47024.0*f(x - 7.0*h) + 123348.0*f(x - 6.0*h) - 210920.0*f(x - 5.0*h) + 244498.0*f(x - 4.0*h) - 192624.0*f(x - 3.0*h) + 99604.0*f(x - 2.0*h) - 30668.0*f(x - h) + 4275.0*f(x) ) / ( 240.0*std::pow(h, 4.0) );
                break;

        }

        return result;

    }

    BackwardDerivative::BackwardDerivative (std::function<double(double)> _f, std::size_t _derivative_order, std::size_t _error_order, double _epsilon) : Derivative::Derivative(_f, _derivative_order, _error_order, _epsilon) {

        if (_derivative_order == 0 || _derivative_order > 4) {

            throw std::runtime_error("Error in metII::BackwardDerivative::BackwardDerivative(std::size_t, std::size_t, double): Invalid derivative order! Please ensure that the derivative order is 1, 2, 3 or 4 as the class does not support higher order derivatives.");

        }

        if (_error_order == 0 || _error_order > 6) {

            throw std::runtime_error("Error in metII::BackwardDerivative::BackwardDerivative(std::size_t, std::size_t, double): Invalid error order! Please ensure that the error order is between 1 and 6, inclusive, as the class does not support derivatives with a higher order error.");

        }

    }

}