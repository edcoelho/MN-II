#include "InversePowerIteration.hpp" 
#include <cmath>

metII::InversePowerIteration::InversePowerIteration() {

}

metII::Vector metII::InversePowerIteration::LU_solver(metII::SquareMatrix L, metII::SquareMatrix U, metII::Vector permutation_vector, metII::Vector b) {
    int n = L.size(); 

    metII::Vector Pb(n);
    for (int i = 0; i < n; ++i) {
        Pb[i] = b[permutation_vector[i]];
    }

    // Ly = b part 
    metII::Vector y(n); 
    for (int i = 0; i < n; i++) {
        double sum = Pb[i]; 
        for (int j = i - 1; j >= 0; j--) {
            sum -= L(i, j)*y[j]; 
        }
        y[i] = sum/L(i,i);  
    }

    // Ux = y part
    metII::Vector x(n); 
    for (int i  = n -1; i >= 0; i--) {
        double sum = y[i]; 
        for (int j = i + 1; j < n; j++) {
            sum -= U(i,j)*x[j];  
        } 
        x[i] = sum/U(i,i); 
    }

    return x;
}

std::pair<double, metII::Vector> metII::InversePowerIteration::compute(metII::SquareMatrix matrix, double epsilon) {

    metII::Vector permutation_vector (std::pair<int, int>(0, matrix.size() - 1)); 
    std::pair<metII::SquareMatrix, metII::SquareMatrix> LU_pair = matrix.get_LU_pair(permutation_vector); 

    metII::SquareMatrix L = LU_pair.first; 
    metII::SquareMatrix U = LU_pair.second; 
    metII::Vector v_0 (matrix.size(), 1); 

    double eigenvalue = 0; 
    std::size_t num_zero_iterations = 0;
    const std::size_t max_zero_iterations = 10;

    metII::Vector eigenvector = v_0; 
    double error; 

    metII::Vector old_eigenvector(matrix.size(), 1);  
    double old_eigenvalue;  
    do {
        old_eigenvalue = eigenvalue; 
        old_eigenvector = eigenvector; 

        old_eigenvector.normalize(); 
        eigenvector = LU_solver(L, U, permutation_vector, old_eigenvector);
        eigenvalue  = old_eigenvector.dot(eigenvector);

        if (eigenvalue != 0.0) {

            error = std::abs((eigenvalue - old_eigenvalue) / eigenvalue);
            num_zero_iterations = 0;

        } else if (eigenvalue == 0.0 && old_eigenvalue != 0.0) {

            error = std::abs(eigenvalue - old_eigenvalue);
            num_zero_iterations = 0;

        } else {
            
            if (num_zero_iterations < max_zero_iterations) {

                num_zero_iterations++;

            } else {

                error = 0.0;

            }

        }      

    } while (error > epsilon); 

    return std::pair<double, metII::Vector> (1.0/eigenvalue, old_eigenvector); 
}