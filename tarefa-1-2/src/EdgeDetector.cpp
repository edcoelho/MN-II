#include "EdgeDetector.hpp"
#include "GaussianFilter.hpp"
#include "SobelFilterX.hpp"
#include "SobelFilterY.hpp" 
#include "LaplaceFilter.hpp"
#include <cmath>

metII::EdgeDetector::EdgeDetector (metII::GrayscaleImage img) {

    this->original_image = img;
    this->current_image = img;

}

metII::GrayscaleImage metII::EdgeDetector::get_original_image () const {

    return this->original_image;

}

metII::GrayscaleImage metII::EdgeDetector::get_current_image () const {

    return this->current_image;

}

void metII::EdgeDetector::set_current_image (metII::GrayscaleImage i) {

    this->current_image = i;

}

void metII::EdgeDetector::set_image (metII::GrayscaleImage i) {

    this->original_image = i;
    this->current_image = i;

}

void metII::EdgeDetector::revert_image () {

    this->current_image = this->original_image;

}