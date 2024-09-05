#include "eigen/Householder.hpp"

metII::Matrix metII::Householder::householder_matrix (metII::Matrix symmetric_matrix, std::size_t column) const {

    metII::Vector w(symmetric_matrix.n_size(), 0.0), w_prime(symmetric_matrix.n_size(), 0.0), n;
    metII::Matrix H(symmetric_matrix.m_size(), symmetric_matrix.n_size(), 1.0, true);

    for (std::size_t i = column + 1; i < w.size(); i++) {

        w[i] = symmetric_matrix(i, column);

    }

    w_prime[column + 1] = w.norm();
    n = (w - w_prime).normalized();
    H = H - (n * 2.0 * n.transpose());

    return H;

}

std::pair<metII::Matrix, metII::Matrix> metII::Householder::compute (metII::Matrix symmetric_matrix) const {

    metII::Matrix H(symmetric_matrix.m_size(), symmetric_matrix.n_size(), 1.0, true), current_H, previous_A, current_A;

    previous_A = symmetric_matrix;

    for (std::size_t i = 0; i < symmetric_matrix.n_size() - 2; i++) {

        current_H = this->householder_matrix(previous_A, i);
        current_A = current_H.transpose() * previous_A * current_H;
        previous_A = current_A;
        H = H * current_H;

    }

    return std::pair<metII::Matrix, metII::Matrix>(H, current_A);

}