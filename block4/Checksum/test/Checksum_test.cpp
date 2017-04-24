//
// Created by moonlightnvkz on 17.04.17.
//

#include <sstream>
#include <gtest/gtest.h>
#include "../src/Checksum.h"

using Param_t = std::pair<const char *, uint16_t>;

class ChecksumTest : public testing::TestWithParam<Param_t> {
public:
    virtual void SetUp() override {
        ss.str(GetParam().first);
    }

    virtual void TearDown() override {
        ss.str("");
    }

    std::stringstream ss;
};


TEST_P(ChecksumTest, ChecksumTest_Che_Test) {
    uint16_t checksum;
    EXPECT_TRUE(Checksum::calc_crc16(ss, checksum));
    EXPECT_EQ(checksum, GetParam().second);
}

Param_t params_pos[] = {
        {"123456789", 0x31C3},
        {"fhowej10", 0x7447},
        {"afiojquihr`89414u1", 0x89BE},
        {"e131391", 0x1D7A},
        {"0", 0x3653},
        {"wkfni23h8rh1hr1o", 0xCF8},
        {"", 0x0},
        {"-132", 0xBA8A}
};

INSTANTIATE_TEST_CASE_P(ChecksumTest_Test, ChecksumTest, testing::ValuesIn(params_pos));