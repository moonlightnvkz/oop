//
// Created by moonlightnvkz on 20.02.17.
//

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include "MedianFilter.h"

using std::vector;
using std::string;

template <typename T>
const T& clamp(const T &v, const T &lo, const T &hi) {
    return v < lo ? lo : v > hi ? hi : v;
}

vector<cv::Vec3b> get_aperture(const cv::Mat &image, int row, int col, int aperture_lin_sz) {
    vector<cv::Vec3b> pixels;
    int i_l = row - aperture_lin_sz / 2;
    int i_r = row + aperture_lin_sz / 2;
    int j_l = col - aperture_lin_sz / 2;
    int j_r = col + aperture_lin_sz / 2;
    for (    int i = i_l; i <= i_r; ++i) {
        for (int j = j_l; j <= j_r; ++j) {
            int r = clamp(i, 0, image.rows);
            int c = clamp(j, 0, image.cols);
            pixels.push_back(image.at<cv::Vec3b>(r, c));
        }
    }
    return pixels;
}

cv::Vec3b get_median(vector<cv::Vec3b> &aperture, int channels, cv::Vec3b central_pixel, unsigned threshold) {
    size_t size = aperture.size();
    for (unsigned channel = 0; channel < channels; ++channel) {
        std::sort(aperture.begin(), aperture.end(), [=](cv::Vec3b a, cv::Vec3b b) {
            return a.val[channel] < b.val[channel];
        });

        cv::Vec3b median = aperture.at(size / 2);

        if (aperture.at(size / 2 - threshold).val[channel] > central_pixel.val[channel] ||
            aperture.at(size / 2 + threshold).val[channel] < central_pixel.val[channel]) {
            central_pixel.val[channel] = median.val[channel];
        }
    }
    return central_pixel;
}

bool median_filter(const std::string &input, unsigned aperture_lin_sz, unsigned threshold, const std::string &output) {
    assert(threshold <= aperture_lin_sz * aperture_lin_sz / 2);

    cv::Mat image = cv::imread(input, CV_LOAD_IMAGE_COLOR);
    if (!image.data) {
        return false;
    }

    for (unsigned r = 0; r < image.rows; ++r) {
        for (unsigned c = 0; c < image.cols; ++c) {
            vector<cv::Vec3b> aperture = get_aperture(image, r, c, aperture_lin_sz);
            image.at<cv::Vec3b>(r, c) = get_median(aperture, image.channels(), image.at<cv::Vec3b>(r, c), threshold);
        }
    }

    cv::imwrite(output, image);
    image.release();
    return true;
}