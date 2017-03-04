//
// Created by moonlightnvkz on 20.02.17.
//

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include "MedianFilter.h"

using namespace std;

vector<cv::Vec3b> get_aperture(const cv::Mat &image, int row, int col, int aperture_lin_sz) {
    vector<cv::Vec3b> pixels;
    for (    int i = row - aperture_lin_sz / 2; i <= row + aperture_lin_sz / 2; ++i) {
        for (int j = col - aperture_lin_sz / 2; j <= col + aperture_lin_sz / 2; ++j) {

            if (i >= 0 && i < image.rows && j >= 0 && j < image.cols) {
                pixels.push_back(image.at<cv::Vec3b>(i, j));
                continue;
            }
            if (i >= 0 && i < image.rows) {
                pixels.push_back(image.at<cv::Vec3b>(i, col));
                continue;
            }
            if (j >= 0 && j < image.cols) {
                pixels.push_back(image.at<cv::Vec3b>(row, j));
                continue;
            }
            // Any else
            pixels.push_back(image.at<cv::Vec3b>(row, col));
        }
    }
    return pixels;
}

cv::Vec3b get_median(vector<cv::Vec3b> aperture, cv::Vec3b central_pixel, unsigned threshold) {
    size_t size = aperture.size();

    for (unsigned channel = 0; channel < 3; ++channel) {
        sort(aperture.begin(), aperture.end(), [=](cv::Vec3b a, cv::Vec3b b) {
            return a.val[channel] < b.val[channel];
        });

        /*
         * In this case median = (a[1] + a[2]) / 2
         *  [][X][X][]
         */
        cv::Vec3b median = aperture.at((size - 1) / 2) / 2 + aperture.at(size / 2) / 2;

        if (aperture.at((size - 1) / 2 - threshold).val[channel] > central_pixel.val[channel] ||
            aperture.at( size      / 2 + threshold).val[channel] < central_pixel.val[channel]) {
            central_pixel.val[channel] = median.val[channel];
        }
    }
    return central_pixel;
}

bool median_filter(std::string input, unsigned aperture_lin_sz, unsigned threshold, std::string output) {
    assert(threshold <= aperture_lin_sz * aperture_lin_sz / 2);

    cv::Mat image = cv::imread(input, CV_LOAD_IMAGE_COLOR);
    if (!image.data) {
        cout << "Could not open or find the image" << endl;
        return false;
    }

    for (unsigned r = 0; r < image.rows; ++r) {
        for (unsigned c = 0; c < image.cols; ++c) {
            vector<cv::Vec3b> aperture = get_aperture(image, r, c, aperture_lin_sz);
            image.at<cv::Vec3b>(r, c) = get_median(aperture, image.at<cv::Vec3b>(r, c), threshold);
        }
    }

    cv::imwrite(output, image);
    image.release();
    return true;
}