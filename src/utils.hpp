#ifndef MET_II_CUSTOM_TYPES_HPP
#define MET_II_CUSTOM_TYPES_HPP

#include <functional>
#include <vector>
#include <array>
#include "eigen/Vector.hpp"
#include "eigen/Matrix.hpp"

namespace metII {

    // Image processing

    typedef std::array<std::array<float, 3>, 3> kernel3;

    // Integration

    enum quadrature_type { NEWTON_COTES, GAUSS_LEGENDRE };

    // Eigen

    void print_vector (metII::Vector vector);
    void print_matrix (metII::Matrix matrix);

    // IVP

    void print_states (std::vector<metII::Vector> states, double delta);

    // BVP

    struct boundary {

        double position;
        double value_at;

    };

    typedef std::vector<std::function<double(double)>> BVP_kernel_plus;

}

#endif