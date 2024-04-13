#ifndef GRAYSCALEIMAGE_HPP_
#define GRAYSCALEIMAGE_HPP_

#include <vector>
#include <array>
#include <opencv4/opencv2/core.hpp>

namespace metII {

    class GrayscaleImage {

        private:
            std::vector<std::vector<float>> pixels_values;
            std::size_t height, width;

        public:

            GrayscaleImage (std::size_t height = 0, std::size_t width = 0);
            GrayscaleImage (cv::Mat img);

            float operator () (std::size_t row, std::size_t column) const;
            float& operator () (std::size_t row, std::size_t column);

            std::size_t get_width () const;
            std::size_t get_height () const;

            void normalize_scale (float min = 0.0f, float max = 1.0f);

    };

}

#endif