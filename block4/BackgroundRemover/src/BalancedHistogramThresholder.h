//
// Created by moonlightnvkz on 09.04.17.
//

#pragma once


#include <vector>
#include <cstddef>

class BalancedHistogramThresholder {
public:
    BalancedHistogramThresholder() = delete;

    static unsigned get_threshold(const std::vector<unsigned> &hist);
};


