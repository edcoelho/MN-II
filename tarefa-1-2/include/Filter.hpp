#ifndef FILTER_HPP_
#define FILTER_HPP_

#include "custom_types.hpp"

namespace metII {

    class Filter {

        private:

            metII::kernel3 kernel;

        public:

            Filter (metII::kernel3 kernel = metII::kernel3());

            void set_kernel (metII::kernel3 k);
            metII::kernel3 const& get_kernel () const;

            // Apply correlation to a image.
            metII::image correlation (const metII::image img);

            // Apply convolution to a image.
            metII::image convolution (const metII::image img);

    };

}

#endif