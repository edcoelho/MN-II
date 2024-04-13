#include "EdgeDetector.hpp"
#include "GaussianFilter.hpp"
#include "SobelFilterX.hpp"
#include "SobelFilterY.hpp" 
#include "LaplaceFilter.hpp"
#include <cmath>

metII::EdgeDetector::EdgeDetector (float threshold, metII::GrayscaleImage img) {

    this->threshold = threshold;
    this->original_image = img;
    this->current_image = img;

}

metII::GrayscaleImage metII::EdgeDetector::get_original_image () const {

    return this->original_image;

}

metII::GrayscaleImage metII::EdgeDetector::get_current_image () const {

    return this->current_image;

}

void metII::EdgeDetector::set_image (metII::GrayscaleImage i) {

    this->original_image = i;
    this->current_image = i;

}

void metII::EdgeDetector::revert_image () {

    this->current_image = this->original_image;

}

void metII::EdgeDetector::gradient () {

    metII::GrayscaleImage img = this->current_image; 
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

            D(i, j) = std::sqrt(std::pow(A(i, j), 2) + std::pow(B(i, j), 2)) < this->threshold ? 0 : 1;

        }

    }

    this->current_image = D; 
}   

void metII::EdgeDetector::laplace () {

    metII::GrayscaleImage img = this->current_image; 
    LaplaceFilter laplace_filter;
    GaussianFilter gauss_filter; 
    // Image suavization by the gaussian filter
    img = gauss_filter.convolution(img); 

    metII::GrayscaleImage A = laplace_filter.correlation(img);
    A.normalize_scale(0.1f, -0.1f);
    float tolerance = 0.02;

    std::size_t i, j;
    for (i = 0; i < A.get_height(); i++) {

        for (j = 0; j < A.get_width(); j++) {

            A(i, j) = std::abs(A(i, j)) < tolerance ? 0 : 1;

        }

    }

    this->current_image = A; 
}