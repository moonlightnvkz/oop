#include <gtest/gtest.h>
#include "../include/Cache.h"

template<typename Cache>
class CacheApplierTest : public ::testing::Test {
public:
    CacheApplierTest()
            : cache(new Cache) {
    }

    std::shared_ptr<Cache> cache;
};

typedef ::testing::Types<MemoryCache, FileCache, PoorManMemoryCache> CacheTypes;
TYPED_TEST_CASE(CacheApplierTest, CacheTypes);

TYPED_TEST(CacheApplierTest, BaseMethodsTest) {
    CacheApplier cache(this->cache);
    std::string key1 = "agh", val1 = "098";
    std::string key2 = "abc", val2 = "123", val2_ = "456";
    std::string key3 = "acb", val3 = "132";
    std::string key4 = "bcb", val4 = "768";
    cache.write_to_cache(key1, val1);
    cache.write_to_cache(key2, val2);
    cache.write_to_cache(key3, val3);
    cache.write_to_cache(key4, val4);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    EXPECT_EQ(cache.read_from_cache(key2), val2);
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key2), val2);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    cache.write_to_cache(key2, val2_);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    EXPECT_EQ(cache.read_from_cache(key2), val2_);
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    cache.remove_from_cache(key2);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    cache.remove_from_cache(key1);
    EXPECT_EQ(cache.read_from_cache(key1), "");
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    cache.remove_from_cache(key4);
    EXPECT_EQ(cache.read_from_cache(key1), "");
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), "");
    cache.remove_from_cache(key3);
    EXPECT_EQ(cache.read_from_cache(key1), "");
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), "");
}

template<typename Cache>
class CacheApplierStaticTest : public ::testing::Test {
public:
    using type = Cache;
};

TYPED_TEST_CASE(CacheApplierStaticTest, CacheTypes);

TYPED_TEST(CacheApplierStaticTest, BaseMethodsTest) {
    CacheApplierStatic<typename TestFixture::type> cache;
    std::string key1 = "agh", val1 = "098";
    std::string key2 = "abc", val2 = "123", val2_ = "456";
    std::string key3 = "acb", val3 = "132";
    std::string key4 = "bcb", val4 = "768";
    cache.write_to_cache(key1, val1);
    cache.write_to_cache(key2, val2);
    cache.write_to_cache(key3, val3);
    cache.write_to_cache(key4, val4);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    EXPECT_EQ(cache.read_from_cache(key2), val2);
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key2), val2);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    cache.write_to_cache(key2, val2_);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    EXPECT_EQ(cache.read_from_cache(key2), val2_);
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    cache.remove_from_cache(key2);
    EXPECT_EQ(cache.read_from_cache(key1), val1);
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    cache.remove_from_cache(key1);
    EXPECT_EQ(cache.read_from_cache(key1), "");
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), val4);
    cache.remove_from_cache(key4);
    EXPECT_EQ(cache.read_from_cache(key1), "");
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), val3);
    EXPECT_EQ(cache.read_from_cache(key4), "");
    cache.remove_from_cache(key3);
    EXPECT_EQ(cache.read_from_cache(key1), "");
    EXPECT_EQ(cache.read_from_cache(key2), "");
    EXPECT_EQ(cache.read_from_cache(key3), "");
}