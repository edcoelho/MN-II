#include <stdexcept>
#include "eigen/Matrix.hpp"

metII::Matrix::Matrix(std::size_t m, std::size_t n, double value, bool diagonal) {

    if (m == 0) {

        throw std::runtime_error("Error in metII::Matrix::Matrix(std::size_t, std::size_t, double): Empty matrix! Please ensure that matrix has at least 1 row.");

    }

    if (n == 0) {

        throw std::runtime_error("Error in metII::Matrix::Matrix(std::size_t, std::size_t, double): Empty matrix! Please ensure that matrix has at least 1 column.");

    }

    if (diagonal) {

        this->data = std::vector<std::vector<double>>(m, std::vector<double>(n, 0.0));

        std::size_t i = 0;
        while (i < m && i < n) {

            this->data[i][i] = value;
            i++;

        }

    } else {

        this->data = std::vector<std::vector<double>>(m, std::vector<double>(n, value));

    }

    this->m = m;
    this->n = n;
    
}

metII::Matrix::Matrix (std::vector<std::vector<double>> matrix) {

    std::size_t i;
    bool valid_matrix;

    valid_matrix = matrix.size() > 0 ? true : false;
    i = 1;

    while (valid_matrix && i < matrix.size()) {

        if (matrix[0].size() != matrix[i].size()) {

            valid_matrix = false;

        }

        i++;

    }

    if (valid_matrix) {

        this->data = matrix;
        this->m = matrix.size();
        this->n = matrix[0].size();

    } else {

        throw std::runtime_error("Error in metII::Matrix::Matrix(std::vector<std::vector<double>>): Invalid matrix! Please ensure that matrix has at least 1 row and column and all rows have same size.");

    }

}

double metII::Matrix::operator() (std::size_t row, std::size_t column) const {

    if (row < 0 || row > this->m_size() || column < 0 || column > this->n_size()) {

        throw std::out_of_range("Error in (double) metII::Matrix::operator()(std::size_t, std::size_t) const: Index out of range!\nPlease ensure that row and column indices are within matrix bounds.");

    }

    return this->data[row][column];

}

double& metII::Matrix::operator() (std::size_t row, std::size_t column) {

    if (row < 0 || row > this->m_size() || column < 0 || column > this->n_size()) {

        throw std::out_of_range("Error in (double&) metII::Matrix::operator()(std::size_t, std::size_t): Index out of range!\nPlease ensure that row and column indices are within matrix bounds.");

    }

    return this->data[row][column];

}

metII::Matrix metII::Matrix::operator+ (metII::Matrix const& other) const {

    if (!this->has_same_size(other)) {

        throw std::runtime_error("Error in (metII::Matrix) metII::Matrix::operator+(metII::Matrix const&) const: Different size matrix addition! Please ensure that both matrices have the same size.");

    }

    metII::Matrix new_matrix(this->m_size(), this->n_size());

    for (std::size_t row = 0; row < this->m_size(); row++) {

        for (std::size_t column = 0; column < this->n_size(); column++) {

            new_matrix(row, column) = this->data[row][column] + other(row, column);

        }

    }

    return new_matrix;

}

metII::Matrix metII::Matrix::operator- (metII::Matrix const& other) const {

    if (!this->has_same_size(other)) {

        throw std::runtime_error("Error in (metII::Matrix) metII::Matrix::operator-(metII::Matrix const&) const: Different size matrix subtraction! Please ensure that both matrices have the same size.");

    }

    metII::Matrix new_matrix(this->m_size(), this->n_size());

    for (std::size_t row = 0; row < this->m_size(); row++) {

        for (std::size_t column = 0; column < this->n_size(); column++) {

            new_matrix(row, column) = this->data[row][column] - other(row, column);

        }

    }

    return new_matrix;
    
}

metII::Matrix metII::Matrix::operator* (double const& scalar) const {

    metII::Matrix new_matrix(this->m_size(), this->n_size());

    for (std::size_t row = 0; row < this->m_size(); row++) {

        for (std::size_t column = 0; column < this->n_size(); column++) {

            new_matrix(row, column) = this->data[row][column] * scalar;

        }

    }

    return new_matrix;

}

metII::Matrix metII::Matrix::operator* (metII::Matrix const& other) const {

    if (this->n_size() != other.m_size()) {

        throw std::runtime_error("Error in (metII::Matrix) metII::Matrix::operator*(metII::Matrix const&) const: Incompatible matrix multiplication! Please ensure that the number of columns in the first matrix equals the number of rows in the second matrix.");

    }

    metII::Matrix new_matrix(this->m_size(), other.n_size());

    for (std::size_t i = 0; i < this->m_size(); i++) {

        for (std::size_t j = 0; j < other.n_size(); j++) {

            for (std::size_t k = 0; k < this->n_size(); k++) {

                new_matrix(i, j) += this->data[i][k] * other(k, j);

            }

        }

    }

    return new_matrix;

}

metII::Vector metII::Matrix::operator* (metII::Vector const& vector) const {

    if (this->n_size() != vector.size()) {

        throw std::runtime_error("Error in metII::Vector metII::Matrix::operator* (metII::Vector const&) const: Incompatible matrix and vector multiplication! Please ensure that the number of columns in the matrix equals the number of elements in the vector.");

    }

    metII::Vector new_vector(this->m_size());

    for (std::size_t i = 0; i < this->m_size(); i++) {

        for (std::size_t j = 0; j < this->n_size(); j++) {

            new_vector[i] += this->data[i][j] * vector[j];

        }

    }

    return new_vector;

}

bool metII::Matrix::operator == (metII::Matrix const& other) const {

    bool are_matrices_equal = true;
    std::size_t row, column;

    if (this->has_same_size(other)) {

        are_matrices_equal = false;

    }

    row = 0;
    column = 0;
    while (are_matrices_equal && row < this->m_size()) {

        if (this->data[row][column] != other(row, column)) {

            are_matrices_equal = false;

        }

        column++;
        if (column >= this->n_size()) {

            column = 0;
            row++;

        }

    }

    return are_matrices_equal;

}

bool metII::Matrix::operator != (metII::Matrix const& other) const {

    return !this->operator==(other);

}

std::size_t metII::Matrix::m_size () const {

    return this->m;

}

std::size_t metII::Matrix::n_size () const {

    return this->n;

}

bool metII::Matrix::has_same_size (metII::Matrix const& other) const {

    return this->m_size() == other.m_size() && this->n_size() == other.n_size();

}

metII::Matrix metII::Matrix::transpose () const {

    Matrix transposed(this->n_size(), this->m_size());

    for (std::size_t i = 0; i < this->m_size(); i++) {

        for (std::size_t j = 0; j < this->n_size(); j++) {

            transposed(j, i) = data[i][j]; //functionando para quadrada

        }

    }

    return transposed;

}

/*Assuming that the matrix is invertible, performs a LU decomposition*/
std::pair<metII::Matrix, metII::Matrix> metII::Matrix::get_LU_pair(metII::Vector &permutation_vector) const {
    int n = this->n_size();
    metII::Matrix matrix_cpy(this->data); 
    metII::Matrix L(n, n, 1, true);

    if (this->m_size() != this->n_size()) {

        throw std::runtime_error("Error in std::pair<metII::Matrix, metII::Matrix> metII::Matrix::get_LU_pair(metII::Vector) const: LU factoration is not implemented to non-square matrix! Please ensure that the number of columns in the matrix equals the number of rows.");

    }

    for (int j = 0; j < n-1; j ++) { 
        double max_pivot = std::abs(matrix_cpy.data[j][j]); 
        int max_pivot_pos = j; 

        // Partial pivoting to reduce roundoff errors 
        for (int i = j + 1; i < n; i++) {
            if (std::abs(matrix_cpy.data[i][j]) > max_pivot) {
                max_pivot = std::abs(matrix_cpy.data[i][j]); 
                max_pivot_pos = i; 
            }
        }

        if (max_pivot == 0) {
            throw std::runtime_error("Matrix is singular and cannot be decomposed.");
        }

        if (max_pivot_pos != j) {
            //swap lines  
            matrix_cpy.swap_lines(j, max_pivot_pos); 
            std::swap(permutation_vector[j], permutation_vector[max_pivot_pos]); 
            //swap L matrix
            if (j > 0) {
                for (int k = 0; k < j; k++) {
                    std::swap(L(j,k), L(max_pivot_pos, k)); 
                }
            }
        }
        double pivot = matrix_cpy.data[j][j];

        // Elimination
        for (int i = j+1; i < n; i++) {
            double l = matrix_cpy.data[i][j]/pivot; 
            matrix_cpy.data[i][j] = 0; 
            for (int k = j + 1; k < n; k++) {
                matrix_cpy.data[i][k] = matrix_cpy.data[i][k]- l*matrix_cpy.data[j][k]; 
            }
            // l goes to L matrix in [i][j] and we are building U by this subtraction
            L.data[i][j] = l; 
        }
    }
    
    return std::pair<metII::Matrix, metII::Matrix> (L, matrix_cpy); 
}

void metII::Matrix::swap_lines(int line1, int line2) {
    std::vector<double> t_vec = this->data[line2];  
    this->data[line2] = this->data[line1]; 
    this->data[line1] = t_vec;   
}