#include "EdgeDetector.hpp"

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