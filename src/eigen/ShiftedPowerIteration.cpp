#include "ShiftedPowerIteration.hpp"
#include "InversePowerIteration.hpp"

metII::ShiftedPowerIteration::ShiftedPowerIteration() {

}

std::pair<double, metII::Vector> metII::ShiftedPowerIteration::compute(metII::SquareMatrix matrix, double shifting_factor, double epsilon) {
    metII::SquareMatrix shifting_matrix(matrix.size(), shifting_factor, true); 
    metII::SquareMatrix A_hat = matrix - shifting_matrix; 
    metII::InversePowerIteration inverse_power_method; 
    std::pair<double, metII::Vector> eigen_pair = inverse_power_method.compute(A_hat, epsilon); 
    double eigenvalue = eigen_pair.first; 
    eigenvalue = eigenvalue + shifting_factor; 
    return std::pair<double, metII::Vector> (eigenvalue, eigen_pair.second); 
}