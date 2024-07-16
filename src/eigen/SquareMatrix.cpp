#include <stdexcept>
#include "eigen/SquareMatrix.hpp"

metII::SquareMatrix::SquareMatrix(std::size_t size) {

    if (size == 0) {

        throw std::runtime_error("Error: Empty metII::SquareMatrix! Please ensure that square matrix size is greater than 0.");

    }

    this->data = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.0));
    
}

metII::SquareMatrix::SquareMatrix(std::size_t size, double value, bool diagonal) {

    if (size == 0) {

        throw std::runtime_error("Error: Empty metII::SquareMatrix! Please ensure that square matrix size is greater than 0.");

    }

    if (diagonal) {

        this->data = std::vector<std::vector<double>>(size, std::vector<double>(size, 0.0));
        for (std::size_t i = 0; i < size; i++) {

            this->data[i][i] = value;

        }

    } else {

        this->data = std::vector<std::vector<double>>(size, std::vector<double>(size, value));

    }
    
}

metII::SquareMatrix::SquareMatrix (std::vector<std::vector<double>> matrix) {
    // TODO: confirmar se é realmente quadrada? 
    this->data = matrix; 
}

double metII::SquareMatrix::operator() (std::size_t row, std::size_t column) const {

    if (row < 0 || row > this->size() || column < 0 || column > this->size()) {

        throw std::out_of_range("Error: Index out of range!\nPlease ensure that row and column indices are within matrix bounds.");

    }

    return this->data[row][column];

}

double& metII::SquareMatrix::operator() (std::size_t row, std::size_t column) {

    if (row < 0 || row > this->size() || column < 0 || column > this->size()) {

        throw std::out_of_range("Error: Index out of range! Please ensure that row and column indices are within matrix bounds.");

    }

    return this->data[row][column];

}

metII::SquareMatrix metII::SquareMatrix::operator+ (metII::SquareMatrix const& other) const {

    if (this->size() != other.size()) {

        throw std::runtime_error("Error: Different size metII::SquareMatrix addition! Please ensure that both matrices have the same size.");

    }

    metII::SquareMatrix new_matrix(this->size());

    for (std::size_t row = 0; row < this->size(); row++) {

        for (std::size_t column = 0; column < this->size(); column++) {

            new_matrix(row, column) = this->data[row][column] + other(row, column);

        }

    }

    return new_matrix;

}

metII::SquareMatrix metII::SquareMatrix::operator- (metII::SquareMatrix const& other) const {

    if (this->size() != other.size()) {

        throw std::runtime_error("Error: Different size metII::SquareMatrix subtraction! Please ensure that both matrices have the same size.");

    }

    metII::SquareMatrix new_matrix(this->size());

    for (std::size_t row = 0; row < this->size(); row++) {

        for (std::size_t column = 0; column < this->size(); column++) {

            new_matrix(row, column) = this->data[row][column] - other(row, column);

        }

    }

    return new_matrix;
    
}

metII::SquareMatrix metII::SquareMatrix::operator* (double const& scalar) const {

    metII::SquareMatrix new_matrix(this->size());

    for (std::size_t row = 0; row < this->size(); row++) {

        for (std::size_t column = 0; column < this->size(); column++) {

            new_matrix(row, column) = this->data[row][column] * scalar;

        }

    }

    return new_matrix;

}

metII::SquareMatrix metII::SquareMatrix::operator* (metII::SquareMatrix const& other) const {

    if (this->size() != other.size()) {

        throw std::runtime_error("Error: Different size metII::SquareMatrix multiplication! Please ensure that both matrices have the same size.");

    }

    metII::SquareMatrix new_matrix(this->size());

    for (std::size_t i = 0; i < this->size(); i++) {

        for (std::size_t j = 0; j < this->size(); j++) {

            for (std::size_t k = 0; k < this->size(); k++) {

                new_matrix(i, j) += this->data[i][k] * other(k, j);

            }

        }

    }

    return new_matrix;

}

metII::Vector metII::SquareMatrix::operator* (metII::Vector const& vector) const {

    if (this->size() != vector.size()) {

        throw std::runtime_error("Error: Different dimension metII::SquareMatrix and metII::Vector multiplication! Please ensure that matrix and vector have the same dimension.");

    }

    metII::Vector new_vector(this->size());

    for (std::size_t i = 0; i < this->size(); i++) {

        for (std::size_t j = 0; j < this->size(); j++) {

            new_vector[i] += this->data[i][j] * vector[i];

        }

    }

    return new_vector;

}


bool metII::SquareMatrix::operator == (metII::SquareMatrix const& other) const {

    bool are_matrices_equal = true;
    std::size_t row, column;

    if (this->size() != other.size()) {

        are_matrices_equal = false;

    }

    row = 0;
    column = 0;
    while (are_matrices_equal && row < this->size()) {

        if (this->data[row][column] != other(row, column)) {

            are_matrices_equal = false;

        }

        column++;
        if (column == this->size()) {

            column = 0;
            row++;

        }

    }

    return are_matrices_equal;

}

bool metII::SquareMatrix::operator != (metII::SquareMatrix const& other) const {

    return !this->operator==(other);

}

std::size_t metII::SquareMatrix::size () const {

    return this->data.size();

}

void metII::SquareMatrix::swap_lines(int line1, int line2) {
    std::vector<double> t_vec = this->data[line2];  
    this->data[line2] = this->data[line1]; 
    this->data[line1] = t_vec;   
}

/*Solve the LUx = b problem*/
metII::Vector LU_solver(metII::SquareMatrix L, metII::SquareMatrix U, metII::Vector b) {
    // Solves first Ly = b 

    // Solves Ux = y and returns 
}

/*Assuming that the matrix is invertible, performs a LU decomposition*/
std::pair<metII::SquareMatrix, metII::SquareMatrix> metII::SquareMatrix::get_LU_pair() const {
    this->data; 
    int n = this->size();
    metII::SquareMatrix matrix_cpy(this->data); 
    metII::SquareMatrix L(n, 1, true); 
    metII::Vector permutation_vector(std::pair<int, int>(1, n)); 

    for (int j = 0; j < n; j ++) {
        double max_pivot = matrix_cpy.data[j][j]; 
        int max_pivot_pos = j; 
        // Partial pivoting to reduce roundoff errors
        for (int i = j + 1; i < n; i++) {
            if (matrix_cpy.data[i][j] > max_pivot) {
                max_pivot = matrix_cpy.data[i][j]; 
                max_pivot_pos = i; 
            }
        }
        if (max_pivot == 0){
            //error: all the column elements are 0
        }
        if (max_pivot_pos != j) {
            //swap lines  
            matrix_cpy.swap_lines(j, max_pivot_pos); 
            permutation_vector.swap_elements(j, max_pivot_pos); 
        }
        
        double pivot = matrix_cpy.data[j][j]; 

        // Elimination
        for (int i = j+1; i < n; i++) {
            double l = matrix_cpy.data[i][j]/pivot; 
            for (int k = j; k < n; k++) {
                matrix_cpy.data[i][k] = matrix_cpy.data[i][k]- l*matrix_cpy.data[j][k]; 
            }
            // l goes to L matrix in [i][j] and we are building U by this subtractiosn
            L.data[i][j] = l; 
        }
    }
    
    return std::pair<metII::SquareMatrix, metII::SquareMatrix> (L, matrix_cpy); 
}