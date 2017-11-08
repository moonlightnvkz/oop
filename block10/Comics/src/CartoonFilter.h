#pragma once


#include <opencv2/core/mat.hpp>

class CartoonFilter {
public:
    CartoonFilter() = delete;

    static void apply(const cv::Mat &src, cv::Mat &dst, double meanShiftSp = 20.0, double meanshiftSr = 45.0,
                      int gaussianKernelWidth = 7, int gaussianKernelHeight = 7,
                      double gaussianSigma = 1.5, int threshold1 = 50, int threshold2 = 150, int aperture = 5);
};


