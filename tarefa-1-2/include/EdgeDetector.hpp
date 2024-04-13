#ifndef EDGEDETECTOR_HPP_
#define EDGEDETECTOR_HPP_

#include "GrayscaleImage.hpp"

namespace metII {

    class EdgeDetector {

        private:

            metII::GrayscaleImage original_image;
            metII::GrayscaleImage current_image;

        protected:

            void set_current_image (metII::GrayscaleImage i);

        public:

            EdgeDetector (metII::GrayscaleImage img = metII::GrayscaleImage());

            metII::GrayscaleImage get_original_image () const;

            metII::GrayscaleImage get_current_image () const;

            // Set the original and current images.
            void set_image (metII::GrayscaleImage i);

            // Discard changes in the current image.
            void revert_image ();

            // Apply the edge detector to the current image.
            virtual void detect () = 0;

    };

}

#endif