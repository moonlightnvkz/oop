//
// Created by moonlightnvkz on 09.04.17.
//

#pragma once


#include <vector>
#include <cstddef>

class BalancedHistogramThresholder {
public:
    std::vector<unsigned>::const_iterator get_threshold(const std::vector<unsigned> &hist);

    unsigned get_weight(std::vector<unsigned>::const_iterator begin,
                        std::vector<unsigned>::const_iterator end);
};


