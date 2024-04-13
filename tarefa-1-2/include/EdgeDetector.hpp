#ifndef EDGEDETECTOR_HPP_
#define EDGEDETECTOR_HPP_

#include "GrayscaleImage.hpp"

namespace metII {

    class EdgeDetector {

        private:

            float threshold;
            metII::GrayscaleImage original_image;
            metII::GrayscaleImage current_image;

        public:

            EdgeDetector (float threshold = 0.5f, metII::GrayscaleImage img = metII::GrayscaleImage());

            float get_threshold ();
            void set_threshold (float threshold);

            metII::GrayscaleImage get_original_image () const;

            metII::GrayscaleImage get_current_image () const;

            // Set the original and current images.
            void set_image (metII::GrayscaleImage i);

            // Discard changes in the current image.
            void revert_image ();

            // Apply gradient edge detector to the current image.
            void gradient ();

            // Apply laplacian edge detector to the current image.
            void laplace ();

    };

}

#endif