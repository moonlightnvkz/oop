#include <iostream>
#include <fstream>
#include "RadixTranslation.h"
#include "DiffRadixPlus.h"

using namespace DiffRadixPlus;

int main() {
    LongNumber a, b;
    unsigned baseA, baseB, baseResult;
    std::ifstream is("input");
    if (!DiffRadixPlus::read(is, a, baseA, b, baseB, baseResult)) {
        return 1;
    }
    LongNumber res = DiffRadixPlus::my_plus(a, baseA, b, baseB, baseResult);
    for (auto i : res) {
        std::cout << i;
    }
    std::ofstream of("output");
    if (!DiffRadixPlus::write(of, res, baseResult)) {
        return 2;
    }
    return 0;
}