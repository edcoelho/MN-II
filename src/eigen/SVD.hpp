#ifndef METII_SVD_HPP_
#define METII_SVD_HPP_

#include "eigen/Matrix.hpp"
#include <tuple>

namespace metII {

    class SVD {

        public:

            std::tuple<metII::Matrix, metII::Matrix, metII::Matrix> decompose (metII::Matrix matrix) const;

    };

}

#endif