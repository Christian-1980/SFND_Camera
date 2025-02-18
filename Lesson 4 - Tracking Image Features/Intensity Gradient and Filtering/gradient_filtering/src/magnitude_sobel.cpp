#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void magnitudeSobel()
{
    // load image from file
    cv::Mat img;
    img = cv::imread("../images/img1gray.png");

    // convert image to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // apply smoothing using the GaussianBlur() function from the OpenCV
    cv::Mat smoothed_image;
    cv::GaussianBlur(imgGray, smoothed_image, cv::Size(5, 5), 2); // Kernel size 5x5, sigma=0

    // create filter kernels using the cv::Mat datatype both for x and y
    cv::Mat kernel_x = (cv::Mat_<float>(3, 3) << -1, 0, 1,
                                                 -2, 0, 2,
                                                 -1, 0, 1);

    cv::Mat kernel_y = (cv::Mat_<float>(3, 3) << -1, -2, -1,
                                                 0, 0, 0,
                                                 1, 2, 1);

    // apply filter using the OpenCv function filter2D()
    cv::Mat dx, dy;
    cv::filter2D(smoothed_image, dx, -1, kernel_x, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT); // -1 means output depth is the same as input
    cv::filter2D(smoothed_image, dy, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    

    // compute magnitude image based on the equation presented in the lesson 
    cv::Mat magnitude(dx.size(), CV_32F); // Create a float matrix for magnitude
    for (int i = 0; i < dx.rows; i++) {
        for (int j = 0; j < dx.cols; j++) {
            float dx_val = dx.at<float>(i, j);
            float dy_val = dy.at<float>(i, j);
            magnitude.at<float>(i, j) = std::sqrt(std::pow(dx_val, 2) + std::pow(dy_val, 2));
        }
    }

    // Convert magnitude to 8-bit for display
    cv::Mat magnitude_display;
    cv::normalize(magnitude, magnitude_display, 0, 255, cv::NORM_MINMAX, CV_8U);
    

    // show result
    string windowName = "Gaussian Blurring";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, magnitude_display);
    cv::waitKey(0); // wait for keyboard input before continuing
}

int main()
{
    magnitudeSobel();
}