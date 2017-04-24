//
// Created by moonlightnvkz on 27.03.17.
//

#include "Checksum.h"

bool Checksum::calc_crc16(std::istream &is, uint16_t &checksum) {
    const ushort generator = 0x1021;
    checksum = 0;

    char byte;
    while(is >> byte) {
        checksum ^= (byte << 8);
        for (int i = 0; i < 8; i++) {
            if ((checksum & 0x8000) != 0) {
                checksum = ((checksum << 1) ^ generator);
            }
            else {
                checksum <<= 1;
            }
        }
    }
    return is.eof();
}

bool Checksum::check_crc16(std::istream &is, uint16_t expected) {
    uint16_t checksum;
    return calc_crc16(is, checksum) && checksum == expected;
}
