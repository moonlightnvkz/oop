//
// Created by moonlightnvkz on 26.02.17.
//

#include <cstddef>
#include "DiffRadixPlus.h"
#include "RadixTranslation.h"

using namespace std;

LongNumber my_plus(LongNumber a, unsigned baseA,
                LongNumber b, unsigned baseB, unsigned baseResult) {
    a = translate_to_dec(a, baseA);
    b = translate_to_dec(b, baseB);
    const int baseDec = 10;
    bool carry = false;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; ++i) {
        if (i == a.size()) {
            a.push_back(0);
        }
        a.at(i) += carry + (i < b.size() ? b.at(i) : 0);
        carry = a.at(i) >= baseDec;
        if (carry) {
            a.at(i) -= baseDec;
        }
    }

    return translate_from_dec(a, baseResult);
}
