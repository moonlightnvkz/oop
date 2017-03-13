//
// Created by moonlightnvkz on 20.02.17.
//

#pragma once
#include <string>
#include <opencv2/core/core.hpp>

bool median_filter(const std::string &input,
                   unsigned aperture_lin_sz,
                   unsigned threshold,
                   const std::string &output);

bool median_filter(const cv::Mat &image,
                   unsigned aperture_lin_sz,
                   unsigned threshold,
                   cv::Mat &output);