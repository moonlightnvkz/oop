//
// Created by moonlightnvkz on 26.02.17.
//

#include <cstddef>
#include <algorithm>
#include "RadixTranslation.h"

namespace RadixTranslation {
    namespace {
        void long_number_fix(LongNumber &a, const unsigned base) {
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

        void long_number_add(LongNumber &a, const int b, const unsigned base) {
            a.at(0) += b;
            long_number_fix(a, base);
        }

        void long_number_mult(LongNumber &a, const int b, const unsigned base) {
            for (auto &i : a) {
                i *= b;
            }
            long_number_fix(a, base);
        }

/// \return remainder of division
        int long_number_div(LongNumber &a, const int b, const unsigned base) {
            int carry = 0;

            for (auto i = a.rbegin(); i != a.rend(); ++i) {
                int curr = *i + carry * base;
                *i = curr / b;
                carry = curr % b;
            }
            long_number_fix(a, base);
            return carry;
        }
    }

    LongNumber translate_to_dec(const LongNumber &number, const unsigned base) {
        if (base <= 1) {
            return {};
        }
        LongNumber res(1);
        for (size_t i = 0; i < number.size(); ++i) {
            long_number_mult(res, base, 10);
            long_number_add(res, number.at(i), 10);
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

    LongNumber translate_from_dec(LongNumber number, const unsigned base) {
        if (base <= 1) {
            return {};
        }
        LongNumber res;
        std::reverse(number.begin(), number.end());
        while (!(number.size() <= 1 && number.at(0) == 0)) {
            res.push_back(long_number_div(number, base, 10));
        };
        if (res.size() == 0) res.push_back(0);
        std::reverse(res.begin(), res.end());
        return res;
    }
}