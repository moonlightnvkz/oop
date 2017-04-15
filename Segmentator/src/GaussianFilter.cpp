//
// Created by moonlightnvkz on 08.04.17.
//

#include "GaussianFilter.h"

GaussianFilter::GaussianFilter(double sigma, unsigned size) :
        sigma(sigma), size(size) {
    unsigned len = unsigned(ceil(sigma * size)) + 1;

    func = [=](int x) {
        double e = x / sigma;
        return exp(-0.5 * (e*e));
    };

    mask.reserve(len);
    double sum = 0;
    for (unsigned i = 0; i < len; ++i) {
        double value = func(i);
        mask.push_back(value);
        sum += i == 0 ? fabs(value) : 2 * fabs(value);
    }
    for (auto &v : mask) {
        v /= sum;
    }
}

void GaussianFilter::apply(cv::Mat &img, GaussianFilter::Type type) {
    int channels = img.channels();
    int len = int(mask.size());
    cv::Mat tmp(img.clone());

    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            for (int c = 0; c < channels; ++c) {
                double sum = mask[0] * img.data[(y * img.cols + x) * channels + c];
                for (int l = 1; l < len; ++l) {
                    int xmin = x, xmax = x, ymin = y, ymax = y;
                    switch (type) {
                        case Type::Horizontal:
                            xmin = std::max(x - l, 0);
                            xmax = std::min(x + l, img.cols - 1);
                            break;
                        default:
                            ymin = std::max(y - l, 0);
                            ymax = std::min(y + l, img.rows - 1);
                    }
                    sum += mask[l] *
                            (img.data[(ymin * img.cols + xmin) * channels + c] +
                             img.data[(ymax * img.cols + xmax) * channels + c]
                            );
                }
                tmp.data[(y * img.cols + x) * channels + c] = uchar(sum);
            }
        }
    }
    img = std::move(tmp);
}
