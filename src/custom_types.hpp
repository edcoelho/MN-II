#ifndef MET_II_CUSTOM_TYPES_HPP
#define MET_II_CUSTOM_TYPES_HPP

#include <array>

namespace metII {

    // Image processing

    typedef std::array<std::array<float, 3>, 3> kernel3;

    // Integration

    enum quadrature_type { NEWTON_COTES, GAUSS_LEGENDRE };

}

#endif