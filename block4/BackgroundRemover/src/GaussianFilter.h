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

    double sigma() const {
        return _sigma;
    }

    unsigned size() const {
        return static_cast<unsigned>(_kernel.size());
    }

    const std::vector<double> &kernel() const {
        return _kernel;
    }

private:
    double _sigma;
    std::vector<double> _kernel;
};


