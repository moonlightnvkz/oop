//
// Created by moonlightnvkz on 08.04.17.
//

#include "GaussianFilter.h"

GaussianFilter::GaussianFilter(double sigma, int size) :
        sigma(std::max(sigma, 0.01)), size(size) {

    if (size < 0 || size % 2 != 1) {
        throw std::out_of_range("Size should be: size >= 0 and size % 2 == 1");
    }
    func = [=](int x) {
        double e = x / sigma;
        return exp(-0.5 * (e*e));
    };

    kernel.reserve(static_cast<size_t>(size));
    double sum = 0;
    int size2 = size / 2;
    for (int i = -size2; i <= size2; ++i) {
        double value = func(i);
        kernel.push_back(value);
        sum += value;
    }
    for (auto &v : kernel) {
        v /= sum;
    }
}

static int clamp(int x, int l, int r) {
    return x < l ? l : x > r ? r : x;
}

void GaussianFilter::apply(cv::Mat &img, GaussianFilter::Type type) {
    int channels = img.channels();
    cv::Mat tmp(img.clone());

    int size2 = size / 2;
    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            for (int c = 0; c < channels; ++c) {
                double sum = 0;
                for (int l = 0; l < size; ++l) {
                    int x_ = x, y_ = y;
                    switch (type) {
                        case Type::Horizontal:
                            x_ = clamp(x - l + size2, 0, img.cols);
                            break;
                        default:
                            y_ = clamp(y - l + size2, 0, img.rows);
                    }
                    sum += kernel[l] * img.data[(y_ * img.cols + x_) * channels + c];
                }
                tmp.data[(y * img.cols + x) * channels + c] = static_cast<uchar>(sum);
            }
        }    }
    img = std::move(tmp);
}
