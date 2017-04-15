//
// Created by moonlightnvkz on 20.02.17.
//

#include <vector>
#include <opencv2/imgcodecs.hpp>
#include "MedianFilter.h"

#define GET_PIXEL(image, r, c, ch, channels) (image.data[(r * image.cols + c) * channels + ch])

using std::vector;
using std::string;

namespace {
    const int &clamp(const int &v, const int &lo, const int &hi) {
        return v < lo ? lo : v > hi ? hi : v;
    }


    vector<uchar> get_aperture(const cv::Mat &image, int row, int col, int channel, int aperture_half_sz) {
        vector<uchar> pixels;
        int channels = image.channels();
        int i_l = row - aperture_half_sz;
        int i_r = row + aperture_half_sz;
        int j_l = col - aperture_half_sz;
        int j_r = col + aperture_half_sz;
        for (int i = i_l; i <= i_r; ++i) {
            for (int j = j_l; j <= j_r; ++j) {
                int r = clamp(i, 0, image.rows);
                int c = clamp(j, 0, image.cols);
                pixels.push_back(GET_PIXEL(image, r, c, channel, channels));
            }
        }
        return pixels;
    }

    uchar get_median(vector<uchar> &aperture, uchar central_pixel, unsigned threshold) {
        size_t size = aperture.size();
        std::sort(aperture.begin(), aperture.end(), [](const uchar &a, const uchar &b) {
            return a < b;
        });

        size_t m = size / 2;
        uchar median = uchar(aperture.at(m));

        if (aperture.at(m - threshold) > central_pixel ||
            aperture.at(m + threshold) < central_pixel) {
            central_pixel = median;
        }
        return central_pixel;
    }
}

namespace MedianFilter {
    bool
    median_filter(const std::string &input, unsigned aperture_lin_sz, unsigned threshold, const std::string &output) {
        if (threshold > aperture_lin_sz * aperture_lin_sz / 2) {
            return false;
        }

        cv::Mat image = cv::imread(input);
        cv::Mat out(image.rows, image.cols, image.type());

        if (!median_filter(image, aperture_lin_sz, threshold, out)) {
            return false;
        }

        cv::imwrite(output, out);
        return true;
    }

    bool median_filter(const cv::Mat &image, unsigned aperture_lin_sz, unsigned threshold, cv::Mat &output) {
        if (threshold > aperture_lin_sz * aperture_lin_sz / 2) {
            return false;
        }
        if (!image.data) {
            return false;
        }
        unsigned aperture_half_sz = aperture_lin_sz / 2;
        const int channels = image.channels();
        for (int r = 0; r < image.rows; ++r) {
            for (int c = 0; c < image.cols; ++c) {
                for (int ch = 0; ch < channels; ++ch) {
                    vector<uchar> aperture = get_aperture(image, r, c, ch, aperture_half_sz);
                    GET_PIXEL(output, r, c, ch, channels) =
                            get_median(aperture, GET_PIXEL(image, r, c, ch, channels), threshold);
                }
            }
        }
        return true;
    }
}