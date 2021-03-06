//
// Created by moonlightnvkz on 10.04.17.
//

#include <gtest/gtest.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>
#include "../src/GaussianFilter.h"

static cv::Scalar random_color(cv::RNG &rng)
{
    int icolor = (unsigned) rng;
    return cv::Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255 );
}

static int draw_random_lines(cv::Mat &image, cv::RNG &rng)
{
    constexpr const int Number = 150;
    constexpr const int Line_type = 8;
    cv::Point pt1, pt2;
    int w = image.cols;
    int h = image.rows;

    for( int i = 0; i < Number; i++ )
    {
        pt1.x = rng.uniform(0, w);
        pt1.y = rng.uniform(0, w);
        pt2.x = rng.uniform(0, h);
        pt2.y = rng.uniform(0, h);

        cv::line(image, pt1, pt2, random_color(rng), rng.uniform(1, 10), Line_type);
    }
    return 0;
}

static double get_standard_deviation(const cv::Mat &img, const cv::Mat &sample) {
    double error = 0;
    int size = img.rows * img.cols * img.channels();
    for (int i = 0; i < size; ++i) {
        error += (img.data[i] - sample.data[i]) * (img.data[i] - sample.data[i]);
    }
    error /= size;
    error = sqrt(error);
    return error;
}

TEST(Gaussian__Test, Gaussian__Test_G_Test) {
    cv::Mat image = cv::Mat::zeros(500, 500, CV_8UC3 );
    cv::RNG rng(124815714);
    draw_random_lines(image, rng);
    cv::Mat sample_cv(image.clone());

    GaussianFilter filter(0.5, 5);
    auto kernel = filter.kernel();
    filter.apply(image, GaussianFilter::Type::Vertical);
    filter.apply(image, GaussianFilter::Type::Horizontal);

    cv::GaussianBlur(sample_cv, sample_cv, cv::Size(5, 5), 0.5, 0.5);

    FAIL() << "Standard deviation from the model: "
           << get_standard_deviation(image, sample_cv);
}