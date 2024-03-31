#include <math.h>
#include "Filter.hpp"

metII::Filter::Filter(metII::image image, metII::kernel3 kernel)
{

    this->original_image = image;
    this->current_image = image;
    this->kernel = kernel;
}

void metII::Filter::set_kernel (metII::kernel3 k) {

    this->kernel = k;

}

metII::kernel3 const& metII::Filter::get_kernel () const {

    return this->kernel;

}

metII::image metII::Filter::get_original_image () const {

    return this->original_image;

}

metII::image metII::Filter::get_current_image () const {

    return this->current_image;

}

void metII::Filter::set_image (metII::image i) {

    this->original_image = i;
    this->current_image = i;

}

void metII::Filter::correlation () {

    std::size_t padding = this->get_kernel().size() >> 1;
    metII::image old_image = this->current_image;

    // Loop indexes.
    std::size_t image_i, image_j, kernel_i, kernel_j, color_channel;

    // Indexes for pixels inside kernel area.
    std::size_t pixel_i, pixel_j;

    for (image_i = 0; image_i < old_image.size(); image_i++) {

        for (image_j = 0; image_j < old_image[0].size(); image_j++) {

            // Reset the pixel.
            for (color_channel = 0; color_channel < 3; color_channel++) {

                this->current_image[image_i][image_j][color_channel] = 0.0f;

            }

            // Apply the kernel to the pixel.
            for (kernel_i = 0; kernel_i < this->get_kernel().size(); kernel_i++) {

                for (kernel_j = 0; kernel_j < this->get_kernel().size(); kernel_j++) {

                    pixel_i = image_i + kernel_i - padding;
                    pixel_j = image_j + kernel_j - padding;

                    if (pixel_i >= 0 && pixel_i < old_image.size() && pixel_j >= 0 && pixel_j < old_image[0].size()) {

                        for (color_channel = 0; color_channel < 3; color_channel++) {

                            this->current_image[image_i][image_j][color_channel] += old_image[pixel_i][pixel_j][color_channel] * kernel[kernel_i][kernel_j];

                        }

                    }

                }

            }

        }

    }

}

void metII::Filter::convolution () {

    std::size_t padding = this->get_kernel().size() >> 1;
    metII::image old_image = this->current_image;

    // Loop indexes.
    std::size_t image_i, image_j, kernel_i, kernel_j, color_channel;

    // Indexes for pixels inside kernel area.
    std::size_t pixel_i, pixel_j;

    for (image_i = 0; image_i < old_image.size(); image_i++) {

        for (image_j = 0; image_j < old_image[0].size(); image_j++) {

            // Reset the pixel.
            for (color_channel = 0; color_channel < 3; color_channel++) {

                this->current_image[image_i][image_j][color_channel] = 0.0f;

            }

            // Apply the kernel to the pixel.
            for (kernel_i = this->get_kernel().size() - 1; (int) kernel_i >= 0; kernel_i--) {

                for (kernel_j = this->get_kernel().size() - 1; (int) kernel_j >= 0; kernel_j--) {

                    pixel_i = image_i - kernel_i + padding;
                    pixel_j = image_j - kernel_j + padding;

                    if (pixel_i >= 0 && pixel_i < old_image.size() && pixel_j >= 0 && pixel_j < old_image[0].size()) {

                        for (color_channel = 0; color_channel < 3; color_channel++) {

                            this->current_image[image_i][image_j][color_channel] += old_image[pixel_i][pixel_j][color_channel] * kernel[kernel_i][kernel_j];

                        }

                    }

                }

            }

        }

    }

}

void metII::Filter::revert_image () {

    this->current_image = this->original_image;

}