#ifndef FILTER_HPP_
#define FILTER_HPP_

#include "custom_types.hpp"
#include "GrayscaleImage.hpp"

namespace metII {

    class Filter {

        private:

            metII::kernel3 kernel;

        public:

            Filter (metII::kernel3 kernel = metII::kernel3{{{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}});

            void set_kernel (metII::kernel3 k);
            metII::kernel3 const& get_kernel () const;

            // Apply correlation to a image.
            metII::GrayscaleImage correlation (const metII::GrayscaleImage img);

            // Apply convolution to a image.
            metII::GrayscaleImage convolution (const metII::GrayscaleImage img);

    };

}

#endif