//
// Created by moonlightnvkz on 08.04.17.
//

#pragma once


#include <opencv2/core/mat.hpp>
#include <functional>

class GaussianFilter {
public:
    GaussianFilter(double sigma, unsigned size);

    enum class Type {
        Horizontal,
        Vertical
    };

    void apply(cv::Mat &img, Type type);

    double get_sigma() const {
        return sigma;
    }

    unsigned get_size() const {
        return size;
    }
private:
    double sigma;
    unsigned size;
    std::function<double(int)> func;

    std::vector<double> mask;
};


