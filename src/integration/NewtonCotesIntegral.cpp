#include "NewtonCotesIntegral.hpp"
#include <stdexcept>

metII::NewtonCotesIntegral::NewtonCotesIntegral(double _lower_limit, double _upper_limit, std::function<double(double)> _func, bool _is_closed, int _degree)
    : metII::Integral(_lower_limit, _upper_limit, _func, true), is_closed(_is_closed), degree(_degree) 
{
    if (_degree < 1 || _degree > 4) {
        throw std::invalid_argument("Error: It is not possible to instantiate the class metII::NewtonCotesIntegral with degree<1 or degree>4!");
    }
    degree = _degree; 
}

double integral_result (std::function<double(double)> func, double h, double a, double b, bool is_closed, int degree) {
    double integral_res = 0.0; 
    if (is_closed) {
        switch(degree) {
            case 1:
                integral_res = (h/2.0)*(func(a) + func(b));
                break;
            case 2: 
                integral_res = (h/3.0)*(func(a) + 4*func(a+h) + func(b));
                break; 
            case 3: 
                integral_res = ((3.0*h)/8.0)*(func(a) + 3*func(a+h) + 3*(func(a+2*h) + func(b)));   
                break;
            case 4: 
                integral_res = ((2.0 * h)/45.0)*(7*func(a) + 32*func(a + h) + 12*func(a + 2*h) + 32*func(a + 3*h) + 7*func(b));
                break; 
            default:
                break; 
        }
    }
    else {
        switch(degree) {
            case 1: 
                integral_res = ((3*h)/2.0)*(func(a + h) + func(a + 2*h));
                break;
            case 2: 
                integral_res = ((4.0*h)/3.0)*(2*func(a + h) - 2*func(a + 2*h) + 2*func(a + 3*h));   
                break; 
            case 3: 
                integral_res = ((5.0*h)/24.0)*(11*func(a + h) + func(a + 2*h) + func(a + 3*h) + 11*func(a + 4*h)); 
                break; 
            case 4: 
                integral_res = ((6.0*h)/20.0)*(11*func(a + h) - 14*func(a + 2*h) + 26*func(a + 3*h) - 14*func(a + 4*h) + 11*func(a + 5*h));
                break; 
            default:
                break;
        }
    }
    return integral_res; 
}
double metII::NewtonCotesIntegral::integrate_interval(double a, double b) {
    double delta = (a-b);
    double h; 
    if (this->is_closed) { 
        h = delta/this->degree; 
    }
    else {
        h = delta/(this->degree + 2); 
    }

    return integral_result(this->get_func(), h, a, b, this->is_closed, this->degree);
    
}


void metII::NewtonCotesIntegral::set_is_closed(bool _is_closed) {
    is_closed = _is_closed;
}

bool metII::NewtonCotesIntegral::get_is_closed() const {
    return is_closed;
}

void metII::NewtonCotesIntegral::set_degree(int _degree) {
    if (_degree >= 1 && _degree <= 4) 
        degree = _degree;
}

int metII::NewtonCotesIntegral::get_degree() const {
    return degree;
}
