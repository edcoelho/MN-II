#include "EdgeDetector.hpp"
#include "GaussianFilter.hpp"
#include "SobelFilterX.hpp"
#include "SobelFilterY.hpp" 
#include "LaplaceFilter.hpp"
#include <cmath>

metII::EdgeDetector::EdgeDetector (float threshold, metII::image img) {

    this->threshold = threshold;
    this->original_image = img;
    this->current_image = img;

}

metII::image metII::EdgeDetector::get_original_image () const {

    return this->original_image;

}

metII::image metII::EdgeDetector::get_current_image () const {

    return this->current_image;

}

void metII::EdgeDetector::set_image (metII::image i) {

    this->original_image = i;
    this->current_image = i;

}

void metII::EdgeDetector::revert_image () {

    this->current_image = this->original_image;

}

void metII::EdgeDetector::gradient () {
    metII::image img = this->current_image; 
    GaussianFilter gauss_filter; 
    SobelFilterX sobel_filter_x; 
    SobelFilterY sobel_filter_y; 

    // Image suavization by the gaussian filter
    img = gauss_filter.convolution(img); 

    metII::image A = sobel_filter_x.correlation(img); 
    metII::image B = sobel_filter_y.correlation(img); 
    metII::image D(A.size(), std::vector<std::array<float, 3>>(A[0].size(), {0.0f, 0.0f, 0.0f})); 

    std::size_t i,j,color_chanel; 
    for (i = 0; i < A.size(); i++) { 
        for (j = 0; j < A[0].size(); j++) {
            for (color_chanel = 0; color_chanel < 3; color_chanel++){
                D[i][j][color_chanel] = std::sqrt(std::pow(A[i][j][color_chanel],2) + std::pow(B[i][j][color_chanel],2)) < this->threshold? 0: 1; 
            }
        }
    }
    this->current_image = D; 
}   

void metII::EdgeDetector::laplace () {
    metII::image img = this->current_image; 
    LaplaceFilter laplace_filter;
    GaussianFilter gauss_filter; 
    // Image suavization by the gaussian filter
    img = gauss_filter.convolution(img); 

    metII::image A = laplace_filter.correlation(img); 
    float tolerance = 0.0001 ; 
    std::size_t i,j,color_chanel; 
    for (i = 0; i < A.size(); i++) { 
        for (j = 0; j < A[0].size(); j++) {
            for (color_chanel = 0; color_chanel < 3; color_chanel++) {
                A[i][j][color_chanel] = (A[i][j][color_chanel] < tolerance)? 0: 1; 
            }
        }
    }
    this->current_image = A; 
}