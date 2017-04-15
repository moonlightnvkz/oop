//
// Created by moonlightnvkz on 09.04.17.
//

#pragma once


#include <opencv2/core/mat.hpp>

namespace LumHist{

    class WrongChannelsAmountException : public std::exception {
    public:
        virtual const char *what() const noexcept override {
            return std::exception::what();
        };

        virtual ~WrongChannelsAmountException() override {};
    };

    class LuminosityHistogram {
    public:
        LuminosityHistogram();

        std::vector<unsigned> get_hist(const cv::Mat &img);

        uchar get_luminosity(const cv::Mat &img, int x, int y);

    private:
        static constexpr const double R = 0.3333;
        static constexpr const double G = 0.3333;
        static constexpr const double B = 0.3333;
    };
}