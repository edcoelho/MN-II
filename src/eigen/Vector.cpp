#include "eigen/Vector.hpp"
#include <stdexcept>
#include <cmath>

metII::Vector::Vector (std::size_t size, double value) {

    if (size == 0) {

        throw std::runtime_error("Error: Empty metII::Vector! Please ensure that vector size is greater than 0.");

    }

    this->data = std::vector<double>(size, value);

}

metII::Vector::Vector (std::pair<int, int> range) {
    int size = range.second - range.first + 1; 

    if (size <= 0) {

        throw std::runtime_error("Error: Empty metII::Vector! Please ensure that vector size is greater than 0.");
        
    }

    this->data = std::vector<double>(size); 
    for (int i = 0, x = range.first; i< size; i++, x++) {
        this->data[i] = x; 
    }
    
}

metII::Vector::Vector (std::vector<double> vector) {

    if (vector.size() == 0) {

        throw std::runtime_error("Error: Empty metII::Vector! Please ensure that vector size is greater than 0.");

    }

    this->data = vector;

}

void metII::Vector::swap_elements(std::size_t pos1, std::size_t pos2) {

    double t_element = this->data[pos1]; 
    this->data[pos1] = this->data[pos2]; 
    this->data[pos2] = t_element;

}

double metII::Vector::operator[] (std::size_t index) const {

    if (index < 0 || index > this->size()) {

        throw std::out_of_range("Error: Index out of range!\nPlease ensure that index is within vector bounds.");

    }

    return this->data[index];

}
double& metII::Vector::operator[] (std::size_t index) {

    if (index < 0 || index > this->size()) {

        throw std::out_of_range("Error: Index out of range!\nPlease ensure that index is within vector bounds.");

    }

    return this->data[index];

}

metII::Vector metII::Vector::operator+ (metII::Vector const& other) const {

    if (this->size() != other.size()) {

        throw std::runtime_error("Error: Different size metII::Vector addition! Please ensure that both vector have the same size.");

    }

    metII::Vector new_vector(this->size());

    for (std::size_t index = 0; index < this->size(); index++) {

        new_vector[index] = this->data[index] + other[index];

    }

    return new_vector;

}

metII::Vector metII::Vector::operator- (metII::Vector const& other) const {

    if (this->size() != other.size()) {

        throw std::runtime_error("Error: Different size metII::Vector subtraction! Please ensure that both vector have the same size.");

    }

    metII::Vector new_vector(this->size());

    for (std::size_t index = 0; index < this->size(); index++) {

        new_vector[index] = this->data[index] - other[index];

    }

    return new_vector;

}

metII::Vector metII::Vector::operator* (double const& scalar) const {

    metII::Vector new_vector(this->size());

    for (std::size_t index = 0; index < this->size(); index++) {

        new_vector[index] = this->data[index] * scalar;

    }

    return new_vector;

}

metII::Matrix metII::Vector::operator* (metII::Matrix const& matrix) const {

    if (matrix.m_size() != 1) {

        throw std::runtime_error("Error in (metII::Matrix) metII::Vector::operator*(metII::Matrix const&) const: Incompatible [column] vector and matrix multiplication! Please ensure that the matrix has only 1 row.");

    }

    metII::Matrix new_matrix(this->size(), matrix.n_size());

    for (std::size_t i = 0; i < this->size(); i++) {

        for (std::size_t j = 0; j < matrix.n_size(); j++) {

            new_matrix(i, j) += this->data[i] * matrix(0, j);

        }

    }

    return new_matrix;

}

bool metII::Vector::operator== (metII::Vector const& other) const {

    bool are_vectors_equal = true;
    std::size_t index;

    if (this->size() != other.size()) {

        are_vectors_equal = false;

    }

    index = 0;
    while (are_vectors_equal && index < this->size()) {

        if (this->data[index] != other[index]) {

            are_vectors_equal = false;

        }

        index++;

    }

    return are_vectors_equal;

}

bool metII::Vector::operator!= (metII::Vector const& other) const {

    return !this->operator==(other);

}


std::size_t metII::Vector::size () const {

    return this->data.size();

}

double metII::Vector::dot (metII::Vector const& other) const {

    if (this->size() != other.size()) {

        throw std::runtime_error("Error: Different size metII::Vector dot product! Please ensure that both vector have the same size.");

    }

    double result = 0.0;

    for (std::size_t index = 0; index < this->size(); index++) {

        result += this->data[index] * other[index];

    }

    return result;

}

double metII::Vector::norm () const {

    return std::sqrt(this->dot(*this));

}

void metII::Vector::normalize () {

    double vector_norm = this->norm();

    for (std::size_t i = 0; i < this->size(); i++) {

        this->data[i] = this->data[i] / vector_norm;

    }

}

metII::Vector metII::Vector::normalized () const {

    metII::Vector result = *this;
    result.normalize();
    return result;

}

metII::Matrix metII::Vector::transpose () const {

    return metII::Matrix({this->data});

}