#ifndef MET_II_GRADIENTEDGEDETECTOR_HPP_
#define MET_II_GRADIENTEDGEDETECTOR_HPP_

#include "image_processing/EdgeDetector.hpp"

namespace metII {

    class GradientEdgeDetector : public EdgeDetector {

        private:

            float threshold;

        public:

            GradientEdgeDetector (metII::GrayscaleImage img = metII::GrayscaleImage(), float threshold = 0.5f);

            float get_threshold ();
            void set_threshold (float threshold);

            void detect () override;

    };

}

#endif