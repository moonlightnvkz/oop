//
// Created by moonlightnvkz on 09.04.17.
//

#include "IntensityHistogramCalculator.h"
#include "WrongChannelsAmountException.h"


std::vector<unsigned> IntensityHistogramCalculator::get_hist(const cv::Mat &img) {
    std::vector<unsigned> hist(256);
    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            uchar lum = get_intensity(img, x, y);
            ++hist[lum];
        }
    }
    return hist;
}

uchar IntensityHistogramCalculator::get_intensity(const cv::Mat &img, int x, int y) throw(std::exception) {
    if (img.type() != CV_8UC3) {
        throw WrongChannelsAmountException();
    }
    int channels = img.channels();
    return static_cast<uchar>(img.data[(y * img.cols + x) * channels + 0] * B +
                              img.data[(y * img.cols + x) * channels + 1] * G +
                              img.data[(y * img.cols + x) * channels + 2] * R);
}