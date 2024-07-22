#ifndef METII_QR_HPP_
#define METII_QR_HPP_

#include "eigen/Vector.hpp"
#include "eigen/Matrix.hpp"
#include <utility>

namespace metII {

    class QR {

        private:

            metII::Matrix jacobi_matrix (metII::Matrix symmetric_matrix, std::size_t row, std::size_t column) const;

        public:

            std::pair<metII::Matrix, metII::Matrix> decompose (metII::Matrix symmetric_matrix) const;

            // Returns the accumulated Q matrices products and a vector with the eigenvalues.
            std::pair<metII::Matrix, metII::Vector> compute (metII::Matrix symmetric_matrix, double epsilon = 1e-6) const;

    };

}

#endif