//
// Created by moonlightnvkz on 08.04.17.
//

#pragma once


#include <opencv2/core/mat.hpp>
#include <functional>

class GaussianFilter {
public:
    GaussianFilter(double sigma, int size);

    enum class Type {
        Horizontal,
        Vertical
    };

    void apply(cv::Mat &img, Type type);

    double get_sigma() const {
        return sigma;
    }

    int get_size() const {
        return size;
    }

    const std::vector<double> &get_kernel() const {
        return kernel;
    }

private:
    double sigma;
    int size;
    std::function<double(int)> func;

    std::vector<double> kernel;
};


