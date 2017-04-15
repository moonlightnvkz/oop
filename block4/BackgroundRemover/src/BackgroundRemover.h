//
// Created by moonlightnvkz on 08.04.17.
//

#pragma once


#include <cstddef>
#include <opencv2/core/mat.hpp>
#include <limits>

namespace BackRem {
    class WrongChannelsAmountException : public std::exception {
    public:
        virtual ~WrongChannelsAmountException() override {};

        virtual const char *what() const noexcept override {
            return std::exception::what();
        }
    };

    class BackgroundRemover {
    public:
        BackgroundRemover(size_t sensitivity, double sigma,
                          int kernel = 4, int area_size = 0);

        cv::Mat remove_background(const cv::Mat &img);

        double sigma;
        size_t sensitivity;
        int area_size;
        int kernel;
    };
}