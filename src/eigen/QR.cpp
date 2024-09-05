#include "eigen/QR.hpp"
#include <cmath>

metII::QR::QR (double _epsilon) {

    this->epsilon = _epsilon;

}

double metII::QR::get_epsilon () const {

    return this->epsilon;

}
void metII::QR::set_epsilon (double _epsilon) {

    this->epsilon = _epsilon;

}

metII::Matrix metII::QR::jacobi_matrix (metII::Matrix symmetric_matrix, std::size_t row, std::size_t column) const {

    metII::Matrix J_ij(symmetric_matrix.m_size(), symmetric_matrix.n_size(), 1.0, true);
    double theta;

    if (std::abs(symmetric_matrix(row, column)) <= this->get_epsilon()) {
        
        return J_ij;

    }

    if (std::abs(symmetric_matrix(column, column)) <= this->get_epsilon()) {

        theta = M_PI_2;

        if (symmetric_matrix(row, column) >= 0.0) {

            theta *= -1.0;

        }

    } else {

        theta = std::atan(-1.0 * symmetric_matrix(row, column) / symmetric_matrix(column, column));

    }

    J_ij(row, row) = std::cos(theta);
    J_ij(column, column) = J_ij(row, row);
    J_ij(row, column) = std::sin(theta);
    J_ij(column, row) = -J_ij(row, column);

    return J_ij;

}

std::pair<metII::Matrix, metII::Matrix> metII::QR::decompose (metII::Matrix symmetric_matrix) const {

    metII::Matrix
        Q_traspose(symmetric_matrix.m_size(), symmetric_matrix.n_size(), 1.0, true),
        J_ij,
        new_R,
        old_R = symmetric_matrix;

    for (std::size_t j = 0; j < symmetric_matrix.n_size() - 1; j++) {

        for (std::size_t i = j + 1; i < symmetric_matrix.n_size(); i++) {

            J_ij = this->jacobi_matrix(old_R, i, j);
            new_R = J_ij * old_R;
            old_R = new_R;
            Q_traspose = J_ij * Q_traspose;

        }

    }

    return std::pair<metII::Matrix, metII::Matrix>(Q_traspose.transpose(), new_R);

}

std::pair<metII::Matrix, metII::Vector> metII::QR::compute (metII::Matrix symmetric_matrix) const {

    metII::Matrix
        P(symmetric_matrix.m_size(), symmetric_matrix.n_size(), 1.0, true),
        new_A,
        old_A = symmetric_matrix;

    std::pair<metII::Matrix, metII::Matrix> qr_matrices;

    metII::Vector eigenvalues(symmetric_matrix.n_size());

    double sum = 1.0;

    while (sum > this->get_epsilon()) {

        qr_matrices = this->decompose(old_A);
        new_A = qr_matrices.second * qr_matrices.first;
        old_A = new_A;
        P = P * qr_matrices.first;

        sum = 0.0;
        for (std::size_t i = 1; i < new_A.n_size(); i++) {

            for (std::size_t j = 0; j < i; j++) {

                sum += std::pow(new_A(i, j), 2);

            }

        }

    }

    for (std::size_t i = 0; i < new_A.n_size(); i++) {

        eigenvalues[i] = new_A(i, i);

    }

    return std::pair<metII::Matrix, metII::Vector>(P, eigenvalues);

}