#include "image_processing/GradientEdgeDetector.hpp"
#include "image_processing/GaussianFilter.hpp"
#include "image_processing/SobelFilterX.hpp"
#include "image_processing/SobelFilterY.hpp"
#include <cmath>

metII::GradientEdgeDetector::GradientEdgeDetector (metII::GrayscaleImage img, float threshold) : metII::EdgeDetector (img) {

    this->threshold = threshold;

}

float metII::GradientEdgeDetector::get_threshold () {

    return this->threshold;

}
void metII::GradientEdgeDetector::set_threshold (float threshold) {

    this->threshold = threshold;

}

void metII::GradientEdgeDetector::detect () {

    metII::GrayscaleImage img = this->get_current_image(); 
    GaussianFilter gauss_filter; 
    SobelFilterX sobel_filter_x; 
    SobelFilterY sobel_filter_y; 

    // Image suavization by the gaussian filter
    img = gauss_filter.convolution(img); 

    metII::GrayscaleImage A = sobel_filter_x.correlation(img); 
    metII::GrayscaleImage B = sobel_filter_y.correlation(img); 
    metII::GrayscaleImage D(A.get_height(), A.get_width());

    std::size_t i, j; 
    for (i = 0; i < A.get_height(); i++) { 

        for (j = 0; j < A.get_width(); j++) {

            D(i, j) = std::sqrt(std::pow(A(i, j), 2) + std::pow(B(i, j), 2)) < this->get_threshold() ? 0 : 1;

        }

    }

    this->set_current_image(D); 

}