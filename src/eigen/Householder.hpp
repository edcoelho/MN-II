#ifndef METII_HOUSEHOLDER_HPP_
#define METII_HOUSEHOLDER_HPP_

#include "eigen/Matrix.hpp"
#include <utility>

namespace metII {

    class Householder {

        private:

            metII::Matrix householder_matrix (metII::Matrix symmetric_matrix, std::size_t column) const;

        public:

            // Returns the accumulated Householder matrices products and the tridiagonal matrix.
            std::pair<metII::Matrix, metII::Matrix> compute (metII::Matrix symmetric_matrix) const;

    };

}

#endif