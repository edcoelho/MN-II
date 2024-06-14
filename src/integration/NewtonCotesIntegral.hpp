#ifndef NEWTON_COTES_INTEGRAL_HPP
#define NEWTON_COTES_INTEGRAL_HPP 
#include "Integral.hpp"

namespace metII {
    class NewtonCotesIntegral : public metII::Integral {
    public: 
        NewtonCotesIntegral(double _lower_limit, double _upper_limit, bool _is_closed = 1, int _degree = 1); 

        double integrate_interval (std::function<double(double)> func, double a, double b) override;

        void set_is_closed(bool _is_closed); 
        bool get_is_closed() const;  

        void set_degree(int _degree); 
        int get_degree() const; 

    private:
        bool is_closed; 

        int degree; //substitution polynome degree 
    };

}
#endif
