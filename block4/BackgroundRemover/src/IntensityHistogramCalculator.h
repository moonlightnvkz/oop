//
// Created by moonlightnvkz on 09.04.17.
//

#pragma once


#include <opencv2/core/mat.hpp>

class IntensityHistogramCalculator {
public:
    IntensityHistogramCalculator() = delete;

    static std::vector<unsigned> get_hist(const cv::Mat &img);

    static uchar get_intensity(const cv::Mat &img, int x, int y) throw(std::exception);

private:
    static constexpr const double R = 0.2126;
    static constexpr const double G = 0.7152;
    static constexpr const double B = 0.0722;
};