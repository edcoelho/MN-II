#include "LaplaceEdgeDetector.hpp"
#include "GaussianFilter.hpp"
#include "LaplaceFilter.hpp"
#include <cmath>

metII::LaplaceEdgeDetector::LaplaceEdgeDetector (metII::GrayscaleImage img, float tolerance) : metII::EdgeDetector(img) {

    this->tolerance = tolerance;

}

float metII::LaplaceEdgeDetector::get_tolerance () {

    return this->tolerance;

}
void metII::LaplaceEdgeDetector::set_tolerance (float t) {

    this->tolerance = t;

}

void metII::LaplaceEdgeDetector::detect () {

    metII::GrayscaleImage img = this->get_current_image(); 
    LaplaceFilter laplace_filter;
    GaussianFilter gauss_filter; 
    // Image suavization by the gaussian filter
    img = gauss_filter.convolution(img); 

    metII::GrayscaleImage A = laplace_filter.correlation(img);
    A.normalize_scale(-0.1f, 0.1f);

    std::size_t i, j;
    for (i = 0; i < A.get_height(); i++) {

        for (j = 0; j < A.get_width(); j++) {

            A(i, j) = std::abs(A(i, j)) < this->get_tolerance() ? 0 : 1;

        }

    }

    this->set_current_image(A);

}