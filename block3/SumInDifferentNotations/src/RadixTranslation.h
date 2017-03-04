//
// Created by moonlightnvkz on 26.02.17.
//

#pragma once

#include <vector>

typedef std::vector<int> LongNumber;

LongNumber translate_to_dec(LongNumber number, unsigned base);

LongNumber translate_from_dec(LongNumber number, unsigned base);