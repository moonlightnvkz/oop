//
// Created by moonlightnvkz on 23.04.17.
//

#include <gtest/gtest.h>
#include "../src/ManifestWriter.h"
#include "../src/ManifestReader.h"

class ManifestReadWriteTest : public testing::TestWithParam<Manifest> {
public:
    virtual void SetUp() override {
        ManifestWriter::write(ss, GetParam());
    }

    virtual void TearDown() override {
        ss.str("");
    }

    std::stringstream ss;
};

static void verify(Manifest res, Manifest expected) {
    ASSERT_EQ(res.size(), expected.size());
    size_t size = res.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(res[i].first, expected[i].first);
        EXPECT_EQ(res[i].second, expected[i].second);
    }
}

TEST_P(ManifestReadWriteTest, ManifestReaderTest_Ma_Test) {
    Manifest res;
    EXPECT_TRUE(ManifestReader::read(ss, res));
    verify(res, GetParam());
}

Manifest params[] = {
        {{"1", 1}},
        {{"1", 1}, {"2", 1}},
        {{"", 1}, {"2", 1}},
        {{}}
};

INSTANTIATE_TEST_CASE_P(ManifestReaderTest, ManifestReadWriteTest, testing::ValuesIn(params));