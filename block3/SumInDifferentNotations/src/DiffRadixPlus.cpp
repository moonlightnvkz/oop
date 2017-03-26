//
// Created by moonlightnvkz on 26.02.17.
//

#include <cstddef>
#include <regex>
#include "DiffRadixPlus.h"
#include "RadixTranslation.h"

namespace DiffRadixPlus {
    LongNumber my_plus(LongNumber a, const unsigned baseA,
                       LongNumber b, const unsigned baseB, const unsigned baseResult) {
        auto less_than_zero = [] (const int i) {return i < 0;};
        if (std::find_if(a.begin(), a.end(), less_than_zero) != a.end()) {
            return {};
        }
        if (std::find_if(b.begin(), b.end(), less_than_zero) != b.end()) {
            return {};
        }
        if (baseA < 2 || baseB < 2 || baseResult < 2) {
            return {};
        }
        a = RadixTranslation::translate_to_dec(a, baseA);
        b = RadixTranslation::translate_to_dec(b, baseB);
        const int baseDec = 10;
        bool carry = false;
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());
        for (size_t i = 0; i < std::max(a.size(), b.size()) || carry; ++i) {
            if (i == a.size()) {
                a.push_back(0);
            }
            a.at(i) += carry + (i < b.size() ? b.at(i) : 0);
            carry = a.at(i) >= baseDec;
            if (carry) {
                a.at(i) -= baseDec;
            }
        }
        std::reverse(a.begin(), a.end());
        return RadixTranslation::translate_from_dec(a, baseResult);
    }

    bool read(std::istream &is, LongNumber &A, unsigned &baseA,
              LongNumber &B, unsigned &baseB, unsigned &baseResult) {
        using sreg_iter = std::sregex_token_iterator;
        std::regex re("(\\s*:\\s*\")|(\"\\s*)");

        for (const auto &N : {make_pair(&A, &baseA), make_pair(&B, &baseB)}) {
            std::string line;
            if (!std::getline(is, line)) {
                return false;
            }

            std::vector<std::string> result{
                    sreg_iter(line.begin(), line.end(), re, -1), sreg_iter()
            };
            if (result.size() != 2) {
                return false;
            }
            int base;
            try {
                base = std::stoi(result[0]);
            } catch (std::exception e) {
                return false;
            }
            if (base < 2) {
                return false;
            } else {
                *N.second = unsigned(base);
            }
            for (char digit : result[1]) {
                if (std::isupper(digit)) {
                    N.first->push_back(digit - 'A' + 10);
                } else if (std::isdigit(digit)) {
                    N.first->push_back(digit - '0');
                } else {
                    return false;
                }
            }
        }
        return !(is >> baseResult).fail();
    }

    bool write(std::ostream &os, const LongNumber &A, const unsigned baseA) {
        if (!os) {
            return false;
        }
        os << baseA << ": \"";
        for (auto i = A.begin(); i != A.end() && os; ++i) {
            if (*i > 9) {
                os << char(*i + 'A' - 10);
            } else {
                os << *i;
            }
        }
        os << '\"';
        return !os.fail();
    }
}