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