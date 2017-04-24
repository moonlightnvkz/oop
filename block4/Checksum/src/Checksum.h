//
// Created by moonlightnvkz on 27.03.17.
//

#pragma once

#include <cstdint>
#include <istream>
#include <vector>

class Checksum {
public:
    Checksum() = delete;

    static bool calc_crc16(std::istream &is, uint16_t &checksum);

    static bool check_crc16(std::istream &is, uint16_t expected);
};


