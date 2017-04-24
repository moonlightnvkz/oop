//
// Created by moonlightnvkz on 08.04.17.
//

#include <cassert>
#include "GaussianFilter.h"

GaussianFilter::GaussianFilter(double sigma, unsigned size) :
        _sigma(std::max(sigma, 0.01)) {

    assert(size % 2 == 1);
    auto func = [=](int x) {
        return exp(- x*x / (2 * sigma*sigma));
    };

    _kernel.reserve(static_cast<size_t>(size));
    double sum = 0;
    int size2 = size / 2;
    for (int i = -size2; i <= size2; ++i) {
        double value = func(i);
        _kernel.push_back(value);
        sum += value;
    }
    for (auto &v : _kernel) {
        v /= sum;
    }
}

static int clamp(int x, int l, int r) {
    return x < l ? l : x > r ? r : x;
}

void GaussianFilter::apply(cv::Mat &img, GaussianFilter::Type type) {
    int channels = img.channels();
    cv::Mat tmp(img.clone());

    int size = static_cast<int>(_kernel.size());
    int size2 = size / 2;
    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            for (int c = 0; c < channels; ++c) {
                double sum = 0;
                for (int l = 0; l < size; ++l) {
                    int x_ = type == Type::Horizontal ? clamp(x + l - size2, 0, img.cols - 1) : x;
                    int y_ = type == Type::Vertical   ? clamp(y + l - size2, 0, img.cols - 1) : y;

                    sum += _kernel[l] * img.data[(y_ * img.cols + x_) * channels + c];
                }
                tmp.data[(y * img.cols + x) * channels + c] = static_cast<uchar>(sum);
            }
        }
    }
    img = std::move(tmp);
}
