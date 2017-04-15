//
// Created by moonlightnvkz on 08.04.17.
//

#include <opencv/cv.hpp>
#include "BackgroundRemover.h"
#include "GaussianFilter.h"
#include "LuminosityHistogram.h"
#include "BalancedHistogramThresholder.h"

namespace BackRem {
    BackgroundRemover::BackgroundRemover(size_t sensitivity, double sigma, int area_size, int kernel) :
            sigma(sigma), sensitivity(sensitivity), area_size(area_size), kernel(kernel) {

    }

    cv::Mat BackgroundRemover::remove_background(const cv::Mat &img) {
        if (img.type() != CV_8UC3) {
            throw WrongChannelsAmountException();
        }

        GaussianFilter filter(sigma, kernel);
        cv::Mat smooth(img);

        filter.apply(smooth, GaussianFilter::Type::Horizontal);
        filter.apply(smooth, GaussianFilter::Type::Vertical);

        LumHist::LuminosityHistogram lum;
        std::vector<unsigned> hist = lum.get_hist(smooth);

        BalancedHistogramThresholder thresholder;
        uchar threshold = static_cast<uchar>(thresholder.get_threshold(hist) - hist.begin());

        // Determinate background side ( < threshold or > threshold)
        unsigned avg = 0;
        for (int x = 0; x < smooth.cols; ++x) {
            avg += lum.get_luminosity(smooth, x, 0) < threshold;
            avg += lum.get_luminosity(smooth, x, smooth.rows - 1) < threshold;
        }
        for (int y = 1; y < smooth.rows - 1; ++y) {
            avg += lum.get_luminosity(smooth, 0, y) < threshold;
            avg += lum.get_luminosity(smooth, smooth.cols - 1, y) < threshold;
        }
        avg = static_cast<unsigned>(avg / (smooth.rows + smooth.cols - 2.0));

        std::function<bool(uchar, uchar)> comp;

        // Apply sensitivity parameter
        if (avg) {
            comp = std::less<uchar>();
            double val = threshold * sensitivity / 100.0;
            threshold = val > 255 ? uchar(255) : static_cast<uchar>(val);   // Reduce threshold
        } else {
            comp = std::greater<uchar>();
            double val = 255 - (255 - threshold) * sensitivity / 100.0;
            threshold = val < 0 ? uchar(0) : static_cast<uchar>(val);   // Increase threshold
        }

        cv::Mat output;
        cv::cvtColor(img, output, CV_BGR2BGRA);
        int channels = output.channels();
        int r_half = output.rows / 2;
        int c_half = output.cols / 2;
        int left = c_half - area_size;
        int right = c_half + area_size;
        int top = r_half - area_size;
        int bot = r_half + area_size;

        for (int y = 0; y < output.rows; ++y) {
            for (int x = 0; x < output.cols; ++x) {
                if (x <= left || x >= right || y <= top || y >= bot) {
                    if (comp(lum.get_luminosity(smooth, x, y), threshold)) {
                        output.data[(y * output.cols + x) * channels + channels - 1] = 0;
                    }
                }
            }
        }
        return output;
    }
}