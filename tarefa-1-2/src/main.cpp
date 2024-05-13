#include <stdlib.h>
#include <iostream>

#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "GrayscaleImage.hpp"
#include "LaplaceEdgeDetector.hpp"
#include "GradientEdgeDetector.hpp"
#include "LaplaceFilter.hpp"
#include "GaussianFilter.hpp"
#include "SobelFilterX.hpp"
#include "SobelFilterY.hpp"

int main (int argc, char * argv[]) {

    // Read the image passed as parameter.
    cv::Mat cv_image = cv::imread(argv[1]);

    if (cv_image.empty()) {

        std::cout << "Error: Failed to read the given image " << argv[1] << std::endl;
        return EXIT_FAILURE;

    }

    // Convert the image to metII grayscale structure.
    metII::GrayscaleImage image(cv_image);

    // Modify the image.
    // metII::GradientEdgeDetector gradient_ed(image, 0.5f);
    // ed.detect();
    // image = ed.get_current_image();
    // ...

    // Draw the image in the OpenCV Mat.
    for (int i = 0; i < cv_image.rows; i++) {

        for (int j = 0; j < cv_image.cols; j++) {

            for (int k = 0; k < 3; k++) {

                cv_image.at<cv::Vec3b>(i, j)[k] = (uchar) (image(i, j) * 255.0f);

            }

        }

    }

    // Create a window.
    cv::namedWindow("Tarefa 1.2", cv::WINDOW_AUTOSIZE);

    // Display the image.
    cv::imshow("Tarefa 1.2", cv_image);

    // Wait for any keyboard input and destroy the window.
    cv::waitKey(0);
    cv::destroyAllWindows();

    return EXIT_SUCCESS;

}