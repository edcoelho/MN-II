#include "eigen/PowerIteration.hpp"
#include <cmath>

metII::PowerIteration::PowerIteration () {}

std::pair<double, metII::Vector> metII::PowerIteration::compute (metII::SquareMatrix matrix, double epsilon) {

    double relative_error = 1.0, old_eigenvalue = 0.0, new_eigenvalue = 0.0;
    std::size_t num_zero_iterations = 0;
    const std::size_t max_zero_iterations = 10;
    metII::Vector old_eigenvector(matrix.size(), 1.0), new_eigenvector(matrix.size(), 1.0);

    while (relative_error > epsilon) {

        old_eigenvalue = new_eigenvalue;
        old_eigenvector = new_eigenvector;

        old_eigenvector.normalize();
        new_eigenvector = matrix * old_eigenvector;
        new_eigenvalue = old_eigenvector.dot(new_eigenvector); // old_eigenvectorT * matrix * old_eigenvector

        if (new_eigenvalue != 0.0) {

            relative_error = std::abs((new_eigenvalue - old_eigenvalue) / new_eigenvalue);
            num_zero_iterations = 0;

        } else if (new_eigenvalue == 0.0 && old_eigenvalue != 0.0) {

            relative_error = std::abs(new_eigenvalue - old_eigenvalue);
            num_zero_iterations = 0;

        } else {
            
            if (num_zero_iterations < max_zero_iterations) {

                num_zero_iterations++;

            } else {

                relative_error = 0.0;

            }

        }     

    }

    return std::pair<double, metII::Vector>(new_eigenvalue, old_eigenvector);

}