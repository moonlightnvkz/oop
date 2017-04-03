//
// Created by moonlightnvkz on 26.02.17.
//

#include <cstddef>
#include <regex>
#include <iostream>
#include "DiffRadixPlus.h"
#include "RadixTranslation.h"

namespace DiffRadixPlus {
    LongNumber my_plus(LongNumber a, const unsigned baseA,
                       LongNumber b, const unsigned baseB, const unsigned baseResult) {
        if (std::find_if(a.begin(), a.end(),
                         [=] (const int i) {return i < 0 || i >= baseA;}) != a.end()) {
            return {};
        }
        if (std::find_if(b.begin(), b.end(),
                         [=] (const int i) {return i < 0 || i >= baseB;}) != b.end()) {
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
        std::regex re_base("(\\s*:\\s*)");   // "*: "
        std::regex re_digits("(\\s*,\\s*)");    // ", "

        for (const auto &N : {make_pair(&A, &baseA), make_pair(&B, &baseB)}) {
            std::string line;
            if (!std::getline(is, line)) {
                return false;
            }

            std::vector<std::string> result{
                    sreg_iter(line.begin(), line.end(), re_base, -1), sreg_iter()
            };
            if (result.size() != 2) {
                return false;
            }

            int base;
            try {
                base = std::stoi(result[0]);
            } catch (std::exception &e) {
                return false;
            }
            if (base < 0) {
                return false;
            } else {
                *N.second = unsigned(base);
            }
            if (result[1].at(0) == '"') {
                if (result[1].back() != '"') {
                    return false;
                }
                for (auto digit = result[1].begin() + 1; digit != result[1].end() - 1; ++digit) {
                    int d;
                    if (std::isupper(*digit)) {
                        d = *digit - 'A' + 10;
                    } else if (std::isdigit(*digit)) {
                        d = *digit - '0';
                    } else {
                        return false;
                    }
                    N.first->push_back(d);
                }
            } else {
                std::vector<std::string> digits{
                        sreg_iter(result[1].begin(), result[1].end(), re_digits, -1), sreg_iter()
                };
                for (const auto &digit : digits) {
                    try {
                        N.first->push_back(std::stoi(digit));
                    } catch (std::exception &e) {
                        std::cerr << e.what();
                        return false;
                    }
                }
            }
        }
        return !(is >> baseResult).fail() && baseResult >= 2;
    }

    bool write(std::ostream &os, const LongNumber &A, const unsigned baseA) {
        if (!os) {
            return false;
        }
        bool pretty = baseA < 36;
        if (pretty && std::find_if(A.begin(), A.end(), [=] (const char c) {
            return c >= baseA;
        }) != A.end()) {
            pretty = false;
        }
        os << baseA << ": ";
        if (pretty) {
            os << '\"';
            for (auto i = A.begin(); i != A.end() && os; ++i) {
                if (*i > 9) {
                    os << char(*i + 'A' - 10);
                } else {
                    os << *i;
                }
            }
            os << '\"';
        } else {
            os << *A.begin();
            for (auto i = A.begin() + 1; i != A.end() && os; ++i) {
                os << ", " << *i;
            }
        }
        return !os.fail();
    }
}