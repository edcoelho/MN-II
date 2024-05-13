#ifndef LAPLACEEDGEDETECTOR_HPP_
#define LAPLACEEDGEDETECTOR_HPP_

#include "EdgeDetector.hpp"

namespace metII {

    class LaplaceEdgeDetector : public metII::EdgeDetector {

        private:

            // Tolerance to zero crossings detection.
            float tolerance;

        public:

            LaplaceEdgeDetector (metII::GrayscaleImage img = metII::GrayscaleImage(), float tolerance = 0.01);

            float get_tolerance ();
            void set_tolerance (float t);

            void detect () override;

    };

}

#endif