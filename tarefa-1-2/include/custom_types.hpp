#ifndef CUSTOM_TYPES_HPP
#define CUSTOM_TYPES_HPP

#include <vector>
#include <array>

namespace metII {

    typedef std::vector<std::vector<std::array<float, 3>>> image;
    typedef std::array<std::array<float, 3>, 3> kernel3;

}

#endif