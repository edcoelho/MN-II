#include "GaussLegendreIntegral.hpp" 
#include <stdexcept>
#include <cmath>

metII::GaussLegendreIntegral::GaussLegendreIntegral(double _lower_limit, double _upper_limit,
    std::size_t num_of_gauss_points , bool _use_partitions, double _epsilon)
    : GaussIntegral(_lower_limit, _upper_limit, _use_partitions, _epsilon), gauss_points(num_of_gauss_points) 
{
    if (num_of_gauss_points < 1 || num_of_gauss_points > 4) {
        throw std::invalid_argument("Error: It is not possible to instantiate the class metII::GaussLaguerreIntegral with num_of_gauss_points<1 or num_of_gauss_points>4!");
    }
    gauss_points = num_of_gauss_points; 
}

std::vector<double> get_weights_1_points() {
    return std::vector<double>({2});
}

std::vector<double> get_weights_2_points() {
    double w = 1; 
    return std::vector<double>({w, w});
}

std::vector<double> get_weights_3_points() {
    double w1 = 5.0 / 9.0; 
    double w2 = 8.0 / 9.0;
    return std::vector<double>({w1, w2, w1}); 
}

std::vector<double> get_weights_4_points() {
    double w1 = 0.3478548451; 
    double w2 = 0.6521451549; 
    return std::vector<double>({w1, w1, w2, w2}); 
}

std::vector<double> get_roots_1_points() {
    return std::vector<double>({0});
}

std::vector<double> get_roots_2_points() {
    double s = sqrt(1.0 / 3.0); 
    return std::vector<double>({-s, s}); 
}

std::vector<double> get_roots_3_points() {
    double s1 = sqrt(3.0 / 5.0); 
    return std::vector<double>({-s1, 0, s1}); 
}

std::vector<double> get_roots_4_points() {
    return std::vector<double>({-0.8611363116, 0.8611363116, -0.3399810436, 0.3399810436}); 
}

double get_x (double root_k, double a, double b) {
    return (b + a)/2 + ((b - a)/2)*root_k; 
}


double metII::GaussLegendreIntegral::integrate_interval (std::function<double(double)> func, double a, double b) {
    std::vector<double> weights;
    std::vector<double> roots;  
    switch (gauss_points) {
        case 1:
            weights = get_weights_1_points();
            roots = get_roots_1_points();
            break;
        case 2:
            weights = get_weights_2_points();
            roots = get_roots_2_points();
            break; 
        case 3:
            weights = get_weights_3_points();
            roots = get_roots_3_points();
            break; 
        case 4:
            weights = get_weights_4_points();
            roots = get_roots_4_points();
            break; 
        default:
            break; 
    }
    
    double sum = 0.0; 

    for (int k = 0; k < gauss_points; k++) {
        sum += weights[k] * func( get_x(roots[k], a, b) ); 
    }
    return ((b-a)/2)*sum ; 
}

double metII::GaussLegendreIntegral::get_gauss_points (void) const {
    return gauss_points; 
}

void metII::GaussLegendreIntegral::set_gauss_points(double num_of_gauss_points) {
    if (num_of_gauss_points >= 1 && num_of_gauss_points <= 4) {
        gauss_points = num_of_gauss_points; 
    }
}