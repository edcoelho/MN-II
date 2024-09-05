#ifndef METII_QR_HPP_
#define METII_QR_HPP_

#include "eigen/Vector.hpp"
#include "eigen/Matrix.hpp"
#include <utility>

namespace metII {

    class QR {

        private:

            double epsilon;

            metII::Matrix jacobi_matrix (metII::Matrix symmetric_matrix, std::size_t row, std::size_t column) const;

        public:

            QR (double _epsilon = 1e-6);

            double get_epsilon () const;
            void set_epsilon (double _epsilon);

            std::pair<metII::Matrix, metII::Matrix> decompose (metII::Matrix symmetric_matrix) const;

            // Returns a matrix with the eigenvectors as columns and a vector with the eigenvalues.
            std::pair<metII::Matrix, metII::Vector> compute (metII::Matrix symmetric_matrix) const;

    };

}

#endif