#ifndef EDGEDETECTOR_HPP_
#define EDGEDETECTOR_HPP_

#include "custom_types.hpp"

namespace metII {

    class EdgeDetector {

        private:

            float threshold;
            metII::image original_image;
            metII::image current_image;

        public:

            EdgeDetector (float threshold = 0.5, metII::image img = metII::image());

            float get_threshold ();
            void set_threshold (float threshold);

            metII::image get_original_image () const;

            metII::image get_current_image () const;

            // Set the original and current images.
            void set_image (metII::image i);

            // Discard changes in the current image.
            void revert_image ();

            // Apply gradient edge detector to the current image.
            void gradient ();

            // Apply laplacian edge detector to the current image.
            void laplace ();

    };

}

#endif