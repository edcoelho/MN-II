#include "utils.hpp"
#include <iostream>

void metII::print_vector (metII::Vector vector) {

    for (std::size_t index = 0; index < vector.size(); index++) {

        std::cout << vector[index] << std::endl;

    }

}

void metII::print_matrix (metII::Matrix matrix) {

    for (std::size_t row = 0; row < matrix.m_size(); row++) {

        for (std::size_t column = 0; column < matrix.n_size(); column++) {

            std::cout << matrix(row, column) << " ";

        }

        std::cout << std::endl;

    }

}

void metII::print_states (std::vector<metII::Vector> states, double delta) {

    for (std::size_t i = 0; i < states.size(); i++) {

        std::cout << "State at time t = " << ((double) i) * delta << ": " << std::endl;
        print_vector(states[i]);
        std::cout << std::endl;

    }

}