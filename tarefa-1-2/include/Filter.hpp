#ifndef FILTER_HPP_
#define FILTER_HPP_

#include "custom_types.hpp"

namespace metII {

    class Filter {

        private:

            metII::image original_image;
            metII::image current_image;
            metII::kernel3 kernel;

        public:

            Filter (metII::image image = metII::image(), metII::kernel3 kernel = metII::kernel3());

            void set_kernel (metII::kernel3 k);
            metII::kernel3 const& get_kernel () const;

            metII::image get_original_image () const;

            metII::image get_current_image () const;

            // Set the original and current images.
            void set_image (metII::image i);

            // Apply correlation to the current image.
            void correlation ();

            // Apply convolution to the current image.
            void convolution ();

            // Discard changes in the current image.
            void revert_image ();

    };

}

#endif