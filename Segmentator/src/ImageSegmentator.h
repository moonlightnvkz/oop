//
// Created by moonlightnvkz on 08.04.17.
//

#pragma once

#include <opencv2/core/mat.hpp>

class ImageSegmentator {
public:
    ImageSegmentator(double sigma, double threshold, size_t min_size);


    cv::Mat segmentate(const cv::Mat &img, size_t &num_css);

    double sigma;
    double threshold;
    size_t min_size;

private:
    double distance(const cv::Mat &img, int x1, int y1, int x2, int y2);
};


