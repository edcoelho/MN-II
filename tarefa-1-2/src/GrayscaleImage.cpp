#include "GrayscaleImage.hpp"

metII::GrayscaleImage::GrayscaleImage (std::size_t height, std::size_t width) {

    this->pixels_values = std::vector<std::vector<float>>(height, std::vector<float>(width, 0.0f));;
    this->height = height;
    this->width = width;

}

metII::GrayscaleImage::GrayscaleImage (cv::Mat img) {

    float r, g, b, gray_value;
    int i, j;

    this->pixels_values = std::vector<std::vector<float>>(img.rows, std::vector<float>());
    this->height = img.rows;
    this->width = img.cols;

    for (i = 0; i < img.rows; i++) {

        for (j = 0; j < img.cols; j++) {

            r = (float) img.at<cv::Vec3b>(i, j)[0];
            g = (float) img.at<cv::Vec3b>(i, j)[1];
            b = (float) img.at<cv::Vec3b>(i, j)[2];
            gray_value = 0.299 * r + 0.587 * g + 0.114 * b; // NTSC standard for grayscale

            this->pixels_values[i].push_back(gray_value/255.0f);

        }

    }

}

float metII::GrayscaleImage::operator () (std::size_t row, std::size_t column) const {

    return this->pixels_values[row][column];

}
float& metII::GrayscaleImage::operator () (std::size_t row, std::size_t column) {

    return this->pixels_values[row][column];

}

std::size_t metII::GrayscaleImage::get_width () const {

    return this->width;

}
std::size_t metII::GrayscaleImage::get_height () const {

    return this->height;

}

void metII::GrayscaleImage::normalize_scale (float max, float min) {

    float actual_max, actual_min;
    std::size_t i, j;

    // Find the maximum and minimum pixels values of the image.
    if (this->get_height() > 0 && this->get_width() > 0) {

        actual_max = this->operator()(0, 0);
        actual_min = this->operator()(0, 0);

    }
    for (i = 0; i < this->get_height(); i++) {

        for (j = 0; j < this->get_width(); j++) {

            if (this->operator()(i, j) > actual_max) actual_max = this->operator()(i, j);
            if (this->operator()(i, j) < actual_min) actual_min = this->operator()(i, j);

        }

    }

    // Normalize pixels values.
    for (i = 0; i < this->get_height(); i++) {

        for (j = 0; j < this->get_width(); j++) {

            this->operator()(i, j) = (this->operator()(i, j) - actual_min) * (max - min) / (actual_max - actual_min) + min;

        }

    }

}