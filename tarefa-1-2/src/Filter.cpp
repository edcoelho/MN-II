#include <math.h>
#include "Filter.hpp"

metII::Filter::Filter (metII::kernel3 kernel) {

    this->kernel = kernel;

}

void metII::Filter::set_kernel (metII::kernel3 k) {

    this->kernel = k;

}

metII::kernel3 const& metII::Filter::get_kernel () const {

    return this->kernel;

}

metII::GrayscaleImage metII::Filter::correlation (const metII::GrayscaleImage img) {

    std::size_t padding = this->get_kernel().size() >> 1;
    metII::GrayscaleImage new_image(img.get_height(), img.get_width());

    // Loop indexes.
    std::size_t image_i, image_j, kernel_i, kernel_j;

    // Indexes for pixels inside kernel area.
    std::size_t pixel_i, pixel_j;

    for (image_i = 0; image_i < img.get_height(); image_i++) {

        for (image_j = 0; image_j < img.get_width(); image_j++) {

            // Apply the kernel to the pixel.
            for (kernel_i = 0; kernel_i < this->get_kernel().size(); kernel_i++) {

                for (kernel_j = 0; kernel_j < this->get_kernel().size(); kernel_j++) {

                    pixel_i = image_i + kernel_i - padding;
                    pixel_j = image_j + kernel_j - padding;

                    if (pixel_i >= 0 && pixel_i < img.get_height() && pixel_j >= 0 && pixel_j < img.get_width()) {

                        new_image(image_i, image_j) = new_image(image_i, image_j) + img(pixel_i, pixel_j) * kernel[kernel_i][kernel_j];

                    }

                }

            }

        }

    }

    return new_image;

}

metII::GrayscaleImage metII::Filter::convolution (const metII::GrayscaleImage img) {

    std::size_t padding = this->get_kernel().size() >> 1;
    metII::GrayscaleImage new_image(img.get_height(), img.get_width());

    // Loop indexes.
    std::size_t image_i, image_j, kernel_i, kernel_j;

    // Indexes for pixels inside kernel area.
    std::size_t pixel_i, pixel_j;

    for (image_i = 0; image_i < img.get_height(); image_i++) {

        for (image_j = 0; image_j < img.get_width(); image_j++) {

            // Apply the kernel to the pixel.
            for (kernel_i = this->get_kernel().size() - 1; (int) kernel_i >= 0; kernel_i--) {

                for (kernel_j = this->get_kernel().size() - 1; (int) kernel_j >= 0; kernel_j--) {

                    pixel_i = image_i - kernel_i + padding;
                    pixel_j = image_j - kernel_j + padding;

                    if (pixel_i >= 0 && pixel_i < img.get_height() && pixel_j >= 0 && pixel_j < img.get_width()) {

                        new_image(image_i, image_j) = new_image(image_i, image_j) + img(pixel_i, pixel_j) * kernel[kernel_i][kernel_j];

                    }

                }

            }

        }

    }

    return new_image;

}