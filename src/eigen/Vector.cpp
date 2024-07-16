#include "eigen/Vector.hpp"
#include <stdexcept>

metII::Vector::Vector (std::size_t size, double value) {

    if (size == 0) {

        throw std::runtime_error("Error: Empty metII::Vector! Please ensure that vector size is greater than 0.");

    }

    this->data = std::vector<double>(size, value);

}

metII::Vector::Vector (std::pair<int, int> range) {
    int size = range.first - range.second + 1; 

    if (size <= 0) {

        throw std::runtime_error("Error: Empty metII::Vector! Please ensure that vector size is greater than 0.");
        
    }

    this->data = std::vector<double>(size); 
    for (int i = 0, x = range.first; i< size; i++, x++) {
        this->data[i] = x; 
    }
    
}

void metII::Vector::swap_elements(int pos1, int pos2) {
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