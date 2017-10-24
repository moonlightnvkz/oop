#include <gtest/gtest.h>
#include "../include/Cache.h"

template<typename Cache>
class CacheTest : public ::testing::Test {
public:
    Cache cache;
};

typedef ::testing::Types<MemoryCache, FileCache, PoorManMemoryCache> CacheTypes;
TYPED_TEST_CASE(CacheTest, CacheTypes);

TYPED_TEST(CacheTest, BaseMethodsTest) {
    TypeParam cache = this->cache;
    std::string key1 = "agh", val1 = "098";
    std::string key2 = "abc", val2 = "123", val2_ = "456";
    std::string key3 = "acb", val3 = "132";
    std::string key4 = "bcb", val4 = "768";
    cache.write(key1, val1);
    cache.write(key2, val2);
    cache.write(key3, val3);
    cache.write(key4, val4);
    EXPECT_EQ(cache.read(key1), val1);
    EXPECT_EQ(cache.read(key2), val2);
    EXPECT_EQ(cache.read(key3), val3);
    EXPECT_EQ(cache.read(key4), val4);
    EXPECT_EQ(cache.read(key3), val3);
    EXPECT_EQ(cache.read(key2), val2);
    EXPECT_EQ(cache.read(key1), val1);
    cache.write(key2, val2_);
    EXPECT_EQ(cache.read(key1), val1);
    EXPECT_EQ(cache.read(key2), val2_);
    EXPECT_EQ(cache.read(key3), val3);
    EXPECT_EQ(cache.read(key4), val4);
    cache.remove(key2);
    EXPECT_EQ(cache.read(key1), val1);
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), val3);
    EXPECT_EQ(cache.read(key4), val4);
    cache.remove(key1);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), val3);
    EXPECT_EQ(cache.read(key4), val4);
    cache.remove(key4);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), val3);
    EXPECT_EQ(cache.read(key4), "");
    cache.remove(key3);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), "");
}

TEST(NullCacheTest, MethodsTest) {
    NullCache cache;
    std::string key1 = "agh", val1 = "098";
    std::string key2 = "abc", val2 = "123", val2_ = "456";
    std::string key3 = "acb", val3 = "132";
    cache.write(key1, val1);
    cache.write(key2, val2);
    cache.write(key3, val3);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key1), "");
    cache.write(key2, val2_);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), "");
    cache.remove(key2);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), "");
    cache.remove(key1);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), "");
    cache.remove(key3);
    EXPECT_EQ(cache.read(key1), "");
    EXPECT_EQ(cache.read(key2), "");
    EXPECT_EQ(cache.read(key3), "");
}

TEST(PoorManMemoryCacheTest, OverflowTest) {
    PoorManMemoryCache cache(10);
    EXPECT_EQ(cache.size(), 10);
    for (int i = 0; i < 10; ++i) {
        cache.write(std::to_string(i), std::to_string(i));
    }
    EXPECT_EQ(cache.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(cache.read(std::to_string(i)), std::to_string(i));
    }
    cache.write(std::to_string(10), std::to_string(10));
    EXPECT_EQ(cache.size(), 10);
    for (int i = 1; i < 11; ++i) {
        EXPECT_EQ(cache.read(std::to_string(i)), std::to_string(i));
    }
    EXPECT_FALSE(cache.has(std::to_string(0)));
}