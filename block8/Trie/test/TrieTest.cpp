#include <gtest/gtest.h>
#include <Trie.hpp>

TEST(TrieTest, TrieInsertTest) {
    Trie<int> trie;
    auto begin = trie.begin();
    EXPECT_EQ(begin, trie.end());
    EXPECT_TRUE(trie.empty());
    auto res = trie.insert("abc", 1);
    EXPECT_EQ(trie.size(), 1u);
    EXPECT_TRUE(res.second);
    EXPECT_EQ(*res.first, 1);
    auto find = trie.find("abc");
    EXPECT_EQ(find, res.first);
    EXPECT_EQ(trie.erase("abc"), 3u);

    trie.insert("abc", 1);
    res = trie.insert("ab", 2);
    EXPECT_EQ(trie.size(), 2u);
    EXPECT_TRUE(res.second);
    EXPECT_EQ(*res.first, 2);
    EXPECT_EQ(trie.find("ab"), res.first);
    EXPECT_EQ(trie.erase("ab"), 1u);
    EXPECT_EQ(trie.size(), 1u);
    EXPECT_EQ(*trie.find("abc"), 1);
    EXPECT_EQ(trie.erase("abc"), 3u);
    EXPECT_TRUE(trie.empty());
    std::vector<std::pair<std::string, int>> v{{"abc", 1}, {"bca", 2}};
    trie.insert(v.begin(), v.end());
    EXPECT_EQ(trie.size(), 2u);
    EXPECT_EQ(*trie.find("abc"), 1);
    EXPECT_EQ(*trie.find("bca"), 2);
    EXPECT_EQ(trie.erase("abc"), 3u);
    EXPECT_EQ(trie.erase("bca"), 3u);
    EXPECT_TRUE(trie.empty());
    trie.insert(v.begin(), v.end());
    trie.erase(trie.find("abc"), ++trie.find("bca"));
    EXPECT_TRUE(trie.empty());
    trie.insert(v.begin(), v.end());
    auto it = trie.begin();
    EXPECT_EQ(*it, 1);
    EXPECT_EQ(it.key(), "abc");
    ++it;
    EXPECT_EQ(*it, 2);
    EXPECT_EQ(it.key(), "bca");
    ++it;
    EXPECT_EQ(it, trie.end());
    EXPECT_TRUE(it.key().empty());
    Trie<int>::const_iterator it2 = static_cast<const Trie<int>>(trie).begin();
}