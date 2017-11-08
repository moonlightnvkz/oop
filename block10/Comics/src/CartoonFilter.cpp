#include <cassert>
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>
#include "CartoonFilter.h"

void CartoonFilter::apply(const cv::Mat &src, cv::Mat &dst, double meanShiftSp, double meanshiftSr,
                          int gaussianKernelWidth, int gaussianKernelHeight,
                          double gaussianSigma, int threshold1, int threshold2, int aperture) {
    size_t chCount = static_cast<size_t>(src.channels());
    assert(chCount > 0);
    assert(src.data);
    std::vector<cv::Mat> channels(chCount);

    cv::Mat gray;
    cv::Mat meanShift(src);
//    cv::Mat meanShift;
//    cv::pyrMeanShiftFiltering(src, meanShift, meanShiftSp, meanshiftSr);
    cv::cvtColor(meanShift, gray, CV_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(gaussianKernelWidth, gaussianKernelHeight), gaussianSigma);

    cv::Mat canny;
    cv::Canny(gray, canny, threshold1, threshold2, aperture);

    cv::split(meanShift, channels);
    for (auto &channel : channels) {
        channel -= canny;
    }
    cv::merge(channels, dst);
}
