//
// Created by moonlightnvkz on 09.04.17.
//

#include <numeric>
#include <functional>
#include "BalancedHistogramThresholder.h"

unsigned BalancedHistogramThresholder::get_threshold(const std::vector<unsigned> &hist) {
    auto itl = hist.begin();
    auto itr = hist.end() - 1;
    auto m = itl + (itr - itl) / 2;

    unsigned wl = std::accumulate(hist.begin(), m, unsigned(0), std::plus<unsigned>());
    unsigned wr = std::accumulate(m + 1, hist.end(), unsigned(0), std::plus<unsigned>());

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
    return static_cast<unsigned>(std::distance(hist.begin(), m));
}
