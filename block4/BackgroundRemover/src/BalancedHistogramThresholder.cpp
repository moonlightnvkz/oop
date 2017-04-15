//
// Created by moonlightnvkz on 09.04.17.
//

#include "BalancedHistogramThresholder.h"

std::vector<unsigned>::const_iterator
BalancedHistogramThresholder::get_threshold(const std::vector<unsigned> &hist) {
    auto itl = hist.begin();
    auto itr = hist.end() - 1;
    auto m = itl + (itr - itl) / 2;
    unsigned wl = get_weight(hist.begin(), m);
    unsigned wr = get_weight(m + 1, hist.end());

    while (itl <= itr) {
        if (wr > wl) {
            wr -= *itr--;
            if (itl + (itr - itl) / 2 < m) {
                wr += *m;
                wl -= *m--;
            }
        } else {
            wl -= *itl++;
            if (itl + (itr - itl) / 2 > m) {
                wr -= *m;
                wl += *m++;
            }
        }
    }
    return m;
}

unsigned BalancedHistogramThresholder::get_weight(std::vector<unsigned>::const_iterator begin,
                                                  std::vector<unsigned>::const_iterator end) {
    unsigned res = 0;
    while (begin != end) {
        res += *begin++;
    }
    return res;
}
