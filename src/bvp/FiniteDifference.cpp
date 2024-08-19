#include "FiniteDifference.hpp"
#include <stdexcept>
#include <cmath>
#include <vector>

metII::FiniteDifference::FiniteDifference (std::size_t _n, metII::Matrix _kernel, std::vector<metII::boundary> _boundaries, double _f_value) {

    if (_n == 0) {

        throw std::runtime_error("Error in metII::FiniteDifference::FiniteDifference(metII::Matrix, std::vector<double>, std::size_t): Invalid quantity of parts (n)! Please ensure that the quantity of parts is greater than zero.");

    }

    if (_boundaries.size() != 2 && _boundaries.size() != 4) {

        throw std::runtime_error("Error in metII::FiniteDifference::FiniteDifference(metII::Matrix, std::vector<double>, std::size_t): Invalid quantity of boundaries! Please ensure that the quantity of boundaries is 2 or 4 as metII::FiniteDifference class only supports one-dimensional and two-dimensional BVP.");

    }

    this->n = _n;
    this->kernel = _kernel;
    this->boundaries = _boundaries;
    this->f_value = _f_value;

}

metII::Vector metII::FiniteDifference::solve_system_of_equations (metII::Matrix A, metII::Vector b) const {
    metII::Vector permutation_vector(std::pair<int, int>(0, A.m_size() - 1)); 
    std::pair<metII::Matrix, metII::Matrix> LU_pair = A.get_LU_pair(permutation_vector);  
    metII::Matrix L = LU_pair.first; 
    metII::Matrix U = LU_pair.second; 
    metII::Vector x = metII::LU_solver(L, U, permutation_vector, b); 
    return x; 
}

std::size_t metII::FiniteDifference::get_n () const {

    return this->n;

}
void metII::FiniteDifference::set_n (std::size_t _n) {

    if (_n == 0 || _n % 2 == 1) {

        throw std::runtime_error("Error in metII::FiniteDifference::set_n(std::size_t): Invalid number of parts (n)! Please ensure that the number of parts is greater than zero.");

    }

    this->n = _n;

}

metII::Matrix metII::FiniteDifference::get_kernel () const {

    return this->kernel;

}
void metII::FiniteDifference::set_kernel (metII::Matrix _kernel) {

    this->kernel = _kernel;

}

std::vector<metII::boundary> metII::FiniteDifference::get_boundaries () const {

    return this->boundaries;

}
void metII::FiniteDifference::set_boundaries (std::vector<metII::boundary> _boundaries) {

    if (_boundaries.size() == 0 || _boundaries.size() % 2 == 1) {

        throw std::runtime_error("Error in metII::FiniteDifference::set_boundaries(std::size_t): Invalid quantity of boundaries! Please ensure that the quantity of boundaries is an even number.");

    }

    this->boundaries = _boundaries;

}

std::size_t metII::FiniteDifference::get_f_value () const {

    return this->f_value;

}
void metII::FiniteDifference::set_f_value (std::size_t _f_value) {

    this->f_value = _f_value;

}

metII::Vector metII::FiniteDifference::compute_nodes () const {

    int
        domain_dimension = boundaries.size() / 2,
        nodes_per_row = this->get_n() - 1,
        quantity_of_nodes = std::pow(nodes_per_row, domain_dimension);
    metII::Matrix A(quantity_of_nodes, quantity_of_nodes);
    metII::Vector b(quantity_of_nodes, this->get_f_value());

    if (domain_dimension == 1) {

        for (int i = 0; i < quantity_of_nodes; i++) {

            A(i, i) = this->get_kernel()(0, 1);

            // Left node
            if (i == 0) { 

                b[i] -= this->get_boundaries()[0].value_at * this->get_kernel()(0, 0);

            } else {

                A(i, i - 1) = this->get_kernel()(0, 0);

            }

            // Right node
            if (i == quantity_of_nodes - 1) { 
                
                b[i] -= this->get_boundaries()[1].value_at * this->get_kernel()(0, 2);
                
            } else {

                A(i, i + 1) = this->get_kernel()(0, 2);

            }

        }

    } else {

        int column, row;

        for (int i = 0; i < quantity_of_nodes; i++) {

            column = i % nodes_per_row;
            row = std::floor(i / nodes_per_row);

            A(i, i) = this->get_kernel()(1, 1);

            // Left node
            if (column == 0) {

                b[i] -= this->get_boundaries()[0].value_at * this->get_kernel()(1, 0);

            } else {

                A(i, i - 1) = this->get_kernel()(1, 0);

            }

            // Right node
            if (column == nodes_per_row - 1) { 

                b[i] -= this->get_boundaries()[1].value_at * this->get_kernel()(1, 2);
                
            } else {

                A(i, i + 1) = this->get_kernel()(1, 2);

            }

            // Bottom node
            if (row == nodes_per_row - 1) {

                b[i] -= this->get_boundaries()[2].value_at * this->get_kernel()(2, 1);

            } else {

                A(i, (row + 1) * nodes_per_row + column) = this->get_kernel()(2, 1);

            }

            // Top node
            if (row == 0) {

                b[i] -= this->get_boundaries()[3].value_at * this->get_kernel()(0, 1);

            } else {

                A(i, (row - 1) * nodes_per_row + column) = this->get_kernel()(0, 1);

            }

        }

    }

    return this->solve_system_of_equations(A, b);

}