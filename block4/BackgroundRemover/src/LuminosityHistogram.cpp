//
// Created by moonlightnvkz on 09.04.17.
//

#include "LuminosityHistogram.h"


namespace LumHist {
    LuminosityHistogram::LuminosityHistogram() {

    }

    std::vector<unsigned> LuminosityHistogram::get_hist(const cv::Mat &img) {
        std::vector<unsigned> hist(256);
        for (int y = 0; y < img.rows; ++y) {
            for (int x = 0; x < img.cols; ++x) {
                uchar lum = get_luminosity(img, x, y);
                ++hist[lum];
            }
        }
        return hist;
    }

    uchar LuminosityHistogram::get_luminosity(const cv::Mat &img, int x, int y) {
        int channels = img.channels();
        if (channels != 3) {
            throw WrongChannelsAmountException();
        }
        return static_cast<uchar>(img.data[(y * img.cols + x) * channels + 0] * B +
                                  img.data[(y * img.cols + x) * channels + 1] * G +
                                  img.data[(y * img.cols + x) * channels + 2] * R);
    }
}