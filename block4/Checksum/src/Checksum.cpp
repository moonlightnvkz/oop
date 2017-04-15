//
// Created by moonlightnvkz on 27.03.17.
//

#include "Checksum.h"

uint16_t Checksum::calc_crc16(std::istream &is) {
    const ushort generator = 0x1021;
    ushort crc = 0;

    char byte;
    while(is >> byte) {
        crc ^= (byte << 8);
        for (int i = 0; i < 8; i++) {
            if ((crc & 0x8000) != 0) {
                crc = ((crc << 1) ^ generator);
            }
            else {
                crc <<= 1;
            }
        }
    }
    if (!is.eof()) {
        throw std::ios_base::failure("Failed to read from stream");
    }
    return crc;
}

bool Checksum::check_crc16(std::istream &is, uint16_t expected) {
    return calc_crc16(is) == expected;
}
