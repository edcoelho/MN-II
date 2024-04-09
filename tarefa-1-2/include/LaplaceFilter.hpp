#ifndef LAPLACEFILTER_HPP_
#define LAPLACEFILTER_HPP_

#include "Filter.hpp"

namespace metII {

    class LaplaceFilter : public Filter {

        public:

            LaplaceFilter (metII::image image = metII::image());

    };

}

#endif