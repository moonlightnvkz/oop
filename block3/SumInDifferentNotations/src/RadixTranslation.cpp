//
// Created by moonlightnvkz on 26.02.17.
//

#include <cassert>
#include <cstddef>
#include <algorithm>
#include "RadixTranslation.h"

using std::reverse;

static void long_number_fix(LongNumber &a, unsigned base) {
    for (size_t i = 0; i < a.size() && !(i == a.size() - 1 && a.at(i) < base); ++i) {
        if (i >= a.size() - 1) {
            a.resize(a.size() + 1);
        }
        a.at(i + 1) += a.at(i) / base;
        a.at(i) %= base;
    };
    while ((a.size() > 1) && (a.back() == 0)) {
        a.pop_back();
    }
}

static void long_number_add(LongNumber &a, int b, unsigned base) {
    a.at(0) += b;
    long_number_fix(a, base);
}

static void long_number_mult(LongNumber &a, int b, unsigned base) {
    for (auto &i : a) {
        i *= b;
    }
    long_number_fix(a, base);
}

/// \return remainder of division
static int long_number_div(LongNumber &a, int b, unsigned base) {
    int carry = 0;

    for (auto i = a.rbegin(); i != a.rend(); ++i) {
        int curr = *i + carry * base;
        *i = curr / b;
        carry = curr % b;
    }
    long_number_fix(a, base);
    return carry;
}

LongNumber translate_to_dec(LongNumber number, unsigned base) {
    assert(base > 1);
    LongNumber res(1);
    for (size_t i = 0; i < number.size(); ++i) {
        long_number_mult(res, base, 10);
        long_number_add(res, number.at(i), 10);
    }
    reverse(res.begin(), res.end());
    return res;
}

LongNumber translate_from_dec(LongNumber number, unsigned base) {
    assert(base > 1);
    LongNumber res;
    reverse(number.begin(), number.end());
    while (!(number.size() <= 1 && number.at(0) == 0)) {
        res.push_back(long_number_div(number, base, 10));
    };
    if (res.size() == 0) res.push_back(0);
    reverse(res.begin(), res.end());
    return res;
}
