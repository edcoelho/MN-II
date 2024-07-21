#include "ShiftedPowerIteration.hpp"
#include "InversePowerIteration.hpp"
#include <stdexcept>

metII::ShiftedPowerIteration::ShiftedPowerIteration() {

}

std::pair<double, metII::Vector> metII::ShiftedPowerIteration::compute(metII::Matrix matrix, double shifting_factor, double epsilon) const {

    if (matrix.m_size() != matrix.n_size()) {

        throw std::runtime_error("Error in std::pair<double, metII::Vector> metII::ShiftedPowerIteration::compute(metII::Matrix, double, double) const: Shifted power iteration is not implemented for non-square matrices! Please ensure that the number of columns in the matrix equals the number of rows.");

    }

    metII::Matrix shifting_matrix(matrix.m_size(), matrix.m_size(), shifting_factor, true); 
    metII::Matrix A_hat = matrix - shifting_matrix; 
    metII::InversePowerIteration inverse_power_method; 
    std::pair<double, metII::Vector> eigen_pair = inverse_power_method.compute(A_hat, epsilon); 
    double eigenvalue = eigen_pair.first; 
    eigenvalue = eigenvalue + shifting_factor; 
    return std::pair<double, metII::Vector> (eigenvalue, eigen_pair.second); 
}