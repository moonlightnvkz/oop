//
// Created by moonlightnvkz on 26.02.17.
//

#pragma once

#include <vector>
#include <istream>
#include <ostream>

namespace DiffRadixPlus {
    typedef std::vector<int> LongNumber;
    bool read(std::istream &is, LongNumber &A, unsigned &baseA,
              LongNumber &B, unsigned &baseB, unsigned &baseResult);

    bool write(std::ostream &os, const LongNumber &A, const unsigned baseA);

    LongNumber my_plus(LongNumber A, const unsigned baseA,
                       LongNumber B, const unsigned baseB, const unsigned baseResult);

}