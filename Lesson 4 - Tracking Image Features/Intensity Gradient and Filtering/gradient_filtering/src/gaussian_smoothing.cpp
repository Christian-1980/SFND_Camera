#include <iostream>
#include <numeric>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

void gaussianSmoothing1()
{
    // load image from file
    cv::Mat img;
    img = cv::imread("../images/img1gray.png");
  
    // create filter kernel
    float gauss_data[25] = {1, 4, 7, 4, 1,
                            4, 16, 26, 16, 4,
                            7, 26, 41, 26, 7,
                            4, 16, 26, 16, 4,
                            1, 4, 7, 4, 1};
    cv::Mat kernel= cv::Mat(5, 5, CV_32F, gauss_data);
  
  	// TODO: Divide each element of the kernel by the sum of all the values in the kernel.
    // Calculate the sum of all elements in the kernel
    float kernel_sum = cv::sum(kernel).dot(cv::Scalar::ones());;

    // Create a new matrix to store the normalized kernel
    cv::Mat normalized_kernel = cv::Mat(5, 5, CV_32F);

    // Iterate through the kernel and normalize each element
    for (int i = 0; i < kernel.rows; i++) {
        for (int j = 0; j < kernel.cols; j++) {
            normalized_kernel.at<float>(i, j) = kernel.at<float>(i, j) / kernel_sum;
        }
    }

    // Print the original and normalized kernels (optional)
    std::cout << "Original Kernel:\n" << kernel << std::endl;
    std::cout << "\nKernel Sum: " << kernel_sum << std::endl;
    std::cout << "\nNormalized Kernel:\n" << normalized_kernel << std::endl;

    // apply filter
    cv::Mat result;
    cv::filter2D(img, result, -1, normalized_kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    // show result
    string windowName = "Gaussian Blurring";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, result);
    cv::waitKey(0); // wait for keyboard input before continuing
}

int main()
{
    gaussianSmoothing1();
}