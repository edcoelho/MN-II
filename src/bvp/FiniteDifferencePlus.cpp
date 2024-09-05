#include "FiniteDifferencePlus.hpp"
#include <stdexcept>
#include <cmath>
#include <vector>

metII::FiniteDifferencePlus::FiniteDifferencePlus (std::size_t _n, std::vector<metII::boundary> _boundaries, double _f_value) {

    if (_n == 0) {

        throw std::runtime_error("Error in metII::FiniteDifferencePlus::FiniteDifferencePlus(std::vector<double>, std::size_t): Invalid quantity of parts (n)! Please ensure that the quantity of parts is greater than zero.");

    }

    if (_boundaries.size() != 2 && _boundaries.size() != 4) {

        throw std::runtime_error("Error in metII::FiniteDifferencePlus::FiniteDifferencePlus(std::vector<double>, std::size_t): Invalid quantity of boundaries! Please ensure that the quantity of boundaries is 2 or 4 as metII::FiniteDifferencePlus class only supports one-dimensional and two-dimensional BVP.");

    }

    this->n = _n;
    this->boundaries = _boundaries;
    this->f_value = _f_value;

}

metII::Vector metII::FiniteDifferencePlus::solve_system_of_equations (metII::Matrix A, metII::Vector b) const {
    metII::Vector permutation_vector(std::pair<int, int>(0, A.m_size() - 1)); 
    std::pair<metII::Matrix, metII::Matrix> LU_pair = A.get_LU_pair(permutation_vector);  
    metII::Matrix L = LU_pair.first; 
    metII::Matrix U = LU_pair.second; 
    metII::Vector x = metII::LU_solver(L, U, permutation_vector, b); 
    return x; 
}

std::size_t metII::FiniteDifferencePlus::get_n () const {

    return this->n;

}
void metII::FiniteDifferencePlus::set_n (std::size_t _n) {

    if (_n == 0 || _n % 2 == 1) {

        throw std::runtime_error("Error in metII::FiniteDifferencePlus::set_n(std::size_t): Invalid number of parts (n)! Please ensure that the number of parts is greater than zero.");

    }

    this->n = _n;

}

std::vector<metII::boundary> metII::FiniteDifferencePlus::get_boundaries () const {

    return this->boundaries;

}
void metII::FiniteDifferencePlus::set_boundaries (std::vector<metII::boundary> _boundaries) {

    if (_boundaries.size() == 0 || _boundaries.size() % 2 == 1) {

        throw std::runtime_error("Error in metII::FiniteDifferencePlus::set_boundaries(std::size_t): Invalid quantity of boundaries! Please ensure that the quantity of boundaries is an even number.");

    }

    this->boundaries = _boundaries;

}

double metII::FiniteDifferencePlus::get_f_value () const {

    return this->f_value;

}
void metII::FiniteDifferencePlus::set_f_value (double _f_value) {

    this->f_value = _f_value;

}

metII::Vector metII::FiniteDifferencePlus::compute_nodes (BVP_kernel_plus kernel) const {

    int
        domain_dimension = boundaries.size() / 2,
        nodes_per_row = this->get_n() - 1,
        quantity_of_nodes = std::pow(nodes_per_row, domain_dimension);
    metII::Matrix A(quantity_of_nodes, quantity_of_nodes);
    metII::Vector b(quantity_of_nodes, this->get_f_value());

    if (domain_dimension == 1) {

        double
            node_position = this->get_boundaries()[0].position,
            delta_position = (this->get_boundaries()[1].position - this->get_boundaries()[0].position) / ( (double) this->get_n() );

        for (int i = 0; i < quantity_of_nodes; i++) {

            node_position += delta_position;

            A(i, i) = kernel[1](node_position);

            // Left node
            if (i == 0) { 

                b[i] -= this->get_boundaries()[0].value_at * kernel[0](node_position);

            } else {

                A(i, i - 1) = kernel[0](node_position);

            }

            // Right node
            if (i == quantity_of_nodes - 1) { 

                b[i] -= this->get_boundaries()[1].value_at * kernel[2](node_position);

            } else {

                A(i, i + 1) = kernel[2](node_position);

            }

        }

    }

    // TODO: Implement FiniteDifferencePlus for two dimensions.

    return this->solve_system_of_equations(A, b);

}