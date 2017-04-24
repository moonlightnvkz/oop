//
// Created by moonlightnvkz on 08.04.17.
//

#include <opencv/cv.hpp>
#include "BackgroundRemover.h"
#include "GaussianFilter.h"
#include "IntensityHistogramCalculator.h"
#include "BalancedHistogramThresholder.h"
#include "WrongChannelsAmountException.h"

BackgroundRemover::BackgroundRemover(size_t sensitivity, double sigma, int area_size, unsigned kernel) :
        _sigma(sigma), _sensitivity(sensitivity), _area_size(area_size), _kernel(kernel) {

}

cv::Mat BackgroundRemover::remove_background(const cv::Mat &img) throw(std::exception) {
    if (img.type() != CV_8UC3) {
        throw WrongChannelsAmountException();
    }

    GaussianFilter filter(_sigma, _kernel);
    cv::Mat smooth(img.clone());

    filter.apply(smooth, GaussianFilter::Type::Horizontal);
    filter.apply(smooth, GaussianFilter::Type::Vertical);


    using Lum = IntensityHistogramCalculator;
    std::vector<unsigned> hist = Lum::get_hist(smooth);
    uchar threshold = static_cast<uchar>(BalancedHistogramThresholder::get_threshold(hist));

    // Determinate background side ( < threshold or > threshold)
    unsigned avg = 0;
    for (int x = 0; x < smooth.cols; ++x) {
        avg += Lum::get_intensity(smooth, x, 0) < threshold;
        avg += Lum::get_intensity(smooth, x, smooth.rows - 1) < threshold;
    }
    for (int y = 1; y < smooth.rows - 1; ++y) {
        avg += Lum::get_intensity(smooth, 0, y) < threshold;
        avg += Lum::get_intensity(smooth, smooth.cols - 1, y) < threshold;
    }
    avg = static_cast<unsigned>(avg / (smooth.rows + smooth.cols - 2.0));

    std::function<bool(uchar, uchar)> comp;

    // Apply sensitivity parameter
    if (avg) {
        comp = std::less<uchar>();
        double val = threshold * _sensitivity / 100.0;
        threshold = val > 255 ? uchar(255) : static_cast<uchar>(val);   // Reduce threshold
    } else {
        comp = std::greater<uchar>();
        double val = 255 - (255 - threshold) * _sensitivity / 100.0;
        threshold = val < 0 ? uchar(0) : static_cast<uchar>(val);   // Increase threshold
    }

    cv::Mat output;
    cv::cvtColor(img, output, CV_BGR2BGRA);
    int channels = output.channels();
    int r_half = output.rows / 2;
    int c_half = output.cols / 2;
    int left = c_half - _area_size;
    int right = c_half + _area_size;
    int top = r_half - _area_size;
    int bot = r_half + _area_size;

    for (int y = 0; y < output.rows; ++y) {
        for (int x = 0; x < output.cols; ++x) {
            if (x <= left || x >= right || y <= top || y >= bot) {
                if (comp(Lum::get_intensity(smooth, x, y), threshold)) {
                    output.data[(y * output.cols + x) * channels + channels - 1] = 0;
                }
            }
        }
    }
    return output;
}

double BackgroundRemover::sigma() const {
    return _sigma;
}

void BackgroundRemover::sigma(double _sigma) {
    BackgroundRemover::_sigma = _sigma;
}

size_t BackgroundRemover::sensitivity() const {
    return _sensitivity;
}

void BackgroundRemover::sensitivity(size_t _sensitivity) {
    BackgroundRemover::_sensitivity = _sensitivity;
}

int BackgroundRemover::area_size() const {
    return _area_size;
}

void BackgroundRemover::area_size(int _area_size) {
    BackgroundRemover::_area_size = _area_size;
}

unsigned BackgroundRemover::kernel() const {
    return _kernel;
}

void BackgroundRemover::kernel(unsigned _kernel) {
    BackgroundRemover::_kernel = _kernel;
}
