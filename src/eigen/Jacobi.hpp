#ifndef METII_JACOBI_HPP_
#define METII_JACOBI_HPP_

#include "eigen/Vector.hpp"
#include "eigen/Matrix.hpp"
#include <utility>

namespace metII {

    class Jacobi {

        private:

            std::pair<metII::Matrix, metII::Matrix> sweep (metII::Matrix symmetric_matrix) const;

            metII::Matrix jacobi_matrix (metII::Matrix symmetric_matrix, std::size_t row, std::size_t column) const;

        public:

            // Returns the accumulated Jacobi matrices products and a vector with the eigenvalues.
            std::pair<metII::Matrix, metII::Vector> compute (metII::Matrix symmetric_matrix, double epsilon = 1e-6) const;

    };

}

#endif