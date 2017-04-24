//
// Created by moonlightnvkz on 08.04.17.
//

#pragma once


#include <opencv2/core/mat.hpp>

class BackgroundRemover {
public:
    BackgroundRemover(size_t sensitivity, double sigma,
                      int area_size = 0, unsigned kernel = 4);

    cv::Mat remove_background(const cv::Mat &img) throw(std::exception);

    double sigma() const;

    void sigma(double _sigma);

    size_t sensitivity() const;

    void sensitivity(size_t _sensitivity);

    int area_size() const;

    void area_size(int _area_size);

    unsigned kernel() const;

    void kernel(unsigned _kernel);

private:
    double _sigma;
    size_t _sensitivity;
    int _area_size;
    unsigned _kernel;
};