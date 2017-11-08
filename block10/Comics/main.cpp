#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>
#include "src/CartoonFilter.h"

static const constexpr int  ESC = 27;

void printHelp() {
    std::cout << "Usage: Comics <image>" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printHelp();
        return 0;
    }

    cv::Mat image = cv::imread(argv[1]);
    if (!image.data) {
        std::cerr << "Failed to load the image " << argv[1] << std::endl;
        return 1;
    }

    cv::imshow("original",image);

    cv::namedWindow("Parameters");
    int meanShiftSp = 10, meanShiftSr = 20;
    int gaussianKernelHalfWidth = 3, gaussianKernelHalfHeight = 3;
    int gaussianSigma = 15;
    int cannyThreshold1 = 50, cannyThreshold2 = 150, cannyHalfAperture = 2;
    cv::createTrackbar("Meanshift spatial window", "Parameters", &meanShiftSp, 50, nullptr);
    cv::setTrackbarMin("Meanshift spatial window", "Parameters", 0);
    cv::createTrackbar("Meanshift color window", "Parameters", &meanShiftSr, 100, nullptr);
    cv::setTrackbarMin("Meanshift spatial window", "Parameters", 0);
    cv::createTrackbar("Gaussian kernel half width", "Parameters", &gaussianKernelHalfWidth, 10, nullptr);
    cv::setTrackbarMin("Gaussian kernel half width", "Parameters", 0);
    cv::createTrackbar("Gaussian kernel half height", "Parameters", &gaussianKernelHalfHeight, 10, nullptr);
    cv::setTrackbarMin("Gaussian kernel half height", "Parameters", 0);
    cv::createTrackbar("Gaussian sigma", "Parameters", &gaussianSigma, 100, nullptr);
    cv::setTrackbarMin("Gaussian sigma", "Parameters", 0);
    cv::createTrackbar("Threshold 1", "Parameters", &cannyThreshold1, 1000, nullptr);
    cv::setTrackbarMin("Threshold 1", "Parameters", 0);
    cv::createTrackbar("Threshold 2", "Parameters", &cannyThreshold1, 1000, nullptr);
    cv::setTrackbarMin("Threshold 2", "Parameters", 0);
    cv::createTrackbar("Half Aperture", "Parameters", &cannyHalfAperture, 3, nullptr);
    cv::setTrackbarMin("Half Aperture", "Parameters", 1);
    cv::Mat dst;
    while(true) {
        CartoonFilter::apply(image, dst, meanShiftSp, meanShiftSr,
                             gaussianKernelHalfWidth * 2 + 1, gaussianKernelHalfHeight * 2 + 1, gaussianSigma / 10.0,
                             cannyThreshold1, cannyThreshold2, cannyHalfAperture * 2 + 1);
        cv::imshow("comics", dst);
        int k = cv::waitKey(1) & 0xFF;
        if (k == ESC) {
            break;
        }
    }
    cv::destroyAllWindows();
    cv::imwrite("./tmp2.jpg", dst);
    return 0;
}