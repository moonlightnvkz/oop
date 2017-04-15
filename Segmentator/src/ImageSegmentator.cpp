//
// Created by moonlightnvkz on 08.04.17.
//
#include <MST.h>
#include <DSU.h>
#include "ImageSegmentator.h"
#include "GaussianFilter.h"
#include "GraphSegmentator.h"

ImageSegmentator::ImageSegmentator(double sigma, double threshold, size_t min_size) :
        sigma(sigma), threshold(threshold), min_size(min_size) {

}

cv::Mat ImageSegmentator::segmentate(const cv::Mat &img, size_t &num_css) {
    GaussianFilter filter(sigma, 4);
    cv::Mat smooth(img.clone());
    filter.apply(smooth, GaussianFilter::Type::Vertical);
    filter.apply(smooth, GaussianFilter::Type::Horizontal);

    weighted_edges_array_t edges(unsigned(img.rows * img.cols * 4));
    size_t num = 0;

    for (int y = 0; y < smooth.rows; ++y) {
        for (int x = 0; x < smooth.cols; ++x) {
            if (x < smooth.cols-1) {
                edges[num].second.first = size_t(y * smooth.cols + x);
                edges[num].second.second = size_t(y * smooth.cols + (x+1));
                edges[num].first = distance(img, x, y, x+1, y);
                num++;
            }

            if (y < smooth.rows-1) {
                edges[num].second.first = size_t(y * smooth.cols + x);
                edges[num].second.second = size_t((y+1) * smooth.cols + x);
                edges[num].first = distance(img, x, y, x, y+1);
                num++;
            }

            if ((x < smooth.cols-1) && (y < smooth.rows-1)) {
                edges[num].second.first = size_t(y * smooth.cols + x);
                edges[num].second.second = size_t((y+1) * smooth.cols + (x+1));
                edges[num].first = distance(img, x, y, x+1, y+1);
                num++;
            }

            if ((x < smooth.cols-1) && (y > 0)) {
                edges[num].second.first = size_t(y * smooth.cols + x);
                edges[num].second.second = size_t((y-1) * smooth.cols + (x+1));
                edges[num].first = distance(img, x, y, x+1, y-1);
                num++;
            }
        }
    }

    GraphSegmentator segm;
    DSU dsu = segm.segmentate(size_t(img.rows * img.cols), edges, threshold);

    for (size_t i = 0; i < num; ++i) {
        size_t a = dsu.find_set(edges[i].second.first);
        size_t b = dsu.find_set(edges[i].second.second);

        if (a != b && (dsu.size(a) < min_size || dsu.size(b) < min_size)) {
            dsu.unite_sets(a, b);
        }
    }

    num_css = dsu.num_sets();

    cv::Mat output(img.rows, img.cols, img.type());

    int channels = img.channels();
    std::vector<std::vector<uchar>> colors(size_t(img.cols * img.rows), std::vector<uchar>(size_t(channels)));

    for (int i = 0; i < img.rows * img.cols; ++i) {
        for (int c = 0; c < channels; ++c) {
            colors[i][c] = uchar(i % 197 *c);   // truly random number
        }
    }

    for (int y = 0; y < img.rows; ++y) {
        for (int x = 0; x < img.cols; ++x) {
            size_t comp = dsu.find_set(size_t(y * img.cols + x));
            for (int c = 0; c < channels; ++c) {
                output.data[(y * img.cols + x) * channels + c] = colors[comp][c];
            }
        }
    }

    return output;
}

double ImageSegmentator::distance(const cv::Mat &img, int x1, int y1, int x2, int y2) {
    double sum = 0;
    int channels = img.channels();
    for (int c = 0; c < channels; ++c) {
        uchar v1 = img.data[(y1 * img.cols + x1) * channels + c];
        uchar v2 = img.data[(y2 * img.cols + x2) * channels + c];
        sum += (v1-v2)*(v1-v2);
    }
    double r = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    return sqrt(r + sum);
}
