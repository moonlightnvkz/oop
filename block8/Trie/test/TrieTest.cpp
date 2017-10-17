#include <gtest/gtest.h>
#include <Trie.hpp>

TEST(InsertAndSize, TrieTest) {
    Trie<int> t;
    EXPECT_TRUE(t.empty());

    auto res = t.insert("a", 1);
    EXPECT_EQ(*res.first, 1);
    EXPECT_TRUE(res.second);
    EXPECT_EQ(t.size(), 1u);

    res = t.insert("b", 2);
    EXPECT_EQ(*res.first, 2);
    EXPECT_TRUE(res.second);
    EXPECT_EQ(t.size(), 2u);

    res = t.insert("ab", 3);
    EXPECT_EQ(*res.first, 3);
    EXPECT_TRUE(res.second);
    auto f = t.find("a");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 1);
    EXPECT_EQ(t.size(), 3u);

    res = t.insert("ac", 4);
    EXPECT_EQ(*res.first, 4);
    EXPECT_TRUE(res.second);
    f = t.find("a");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 1);
    f = t.find("ab");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 3);
    EXPECT_EQ(t.size(), 4u);

    std::vector<std::pair<std::string, int>> v{{"i", 'i'}, {"f", 'f'}, {"if", 'i' + 'f'}};
    t.insert(v.begin(), v.end());
    EXPECT_EQ(*t.find("i"), 'i');
    EXPECT_EQ(*t.find("f"), 'f');
    EXPECT_EQ(*t.find("if"), 'i' + 'f');
}

TEST(BracketOperator, TrieTest) {
    Trie<int> t;
    int &i = t["a"];
    EXPECT_EQ(i, 0);
    i = 1;
    EXPECT_EQ(t["a"], 1);
    EXPECT_EQ(*t.find("a"), 1);
    t["ab"] = 2;
    EXPECT_EQ(t["a"], 1);
    EXPECT_EQ(t["ab"], 2);
}

TEST(Erase, TrieTest) {
    Trie<int> t;
    constexpr int Count = 9;
    for (int i = 0; i < Count; ++i) {
        t.insert(std::to_string(i), i);
    }
    t.insert("5a", 25);
    t.insert("5ab", 26);
    t.insert("5abc", 27);
    t.insert("5ac", 28);
    t.insert("5acb", 29);
    ASSERT_EQ(t.erase("1"), 1u);
    ASSERT_EQ(t.erase("2"), 1u);
    ASSERT_EQ(t.erase("5"), 1u);
    ASSERT_EQ(t.erase("5a"), 1u);
    ASSERT_EQ(t.erase("5ab"), 1u);
    ASSERT_EQ(t.erase("5abc"), 2u);
    ASSERT_EQ(t.erase("5acb"), 1u);
    ASSERT_EQ(t.erase("5ac"), 3u);
    t.erase(t.find("6"));
    EXPECT_EQ(t.find("6"), t.end());
    t.erase(t.begin(), t.end());
    EXPECT_TRUE(t.empty());
    for (int i = 0; i < Count; ++i) {
        t.insert(std::to_string(i), i);
    }
    t.clear();
    EXPECT_TRUE(t.empty());
}

TEST(Find, TrieTest) {
    Trie<int> t;
    EXPECT_EQ(t.find("1"), t.end());
    t.insert("1", 1);
    auto f = t.find("1");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 1);
    EXPECT_EQ(f.key(), "1");
    t.insert("123", 3);
    f = t.find("1");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 1);
    EXPECT_EQ(f.key(), "1");
    f = t.find("123");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 3);
    EXPECT_EQ(f.key(), "123");
    t.erase("1");
    f = t.find("1");
    EXPECT_EQ(f, t.end());
    f = t.find("123");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 3);
    EXPECT_EQ(f.key(), "123");
}

TEST(GetSubTrie, TrieTest) {
    Trie<int> t;
    constexpr int Count = 9;
    for (int i = 0; i < Count; ++i) {
        t.insert(std::to_string(i), i);
        t.insert(std::to_string(i) + std::to_string(i+1), i+1);
        t.insert(std::to_string(i) + std::to_string(i+2), i+2);
    }

    auto ret = t.getSubTrie("ajhbcva");
    ASSERT_FALSE(ret.has_value());
    ret = t.getSubTrie("2");
    ASSERT_TRUE(ret.has_value());
    Trie<int>::SubTrie sub = ret.value();
    EXPECT_EQ(sub.getRootValue(), 2);
    auto f = sub.find("2");
    EXPECT_EQ(f, sub.end());
    f = sub.find("3");
    ASSERT_NE(f, sub.end());
    EXPECT_EQ(*f, 3);
    EXPECT_EQ(f.key(), "3");
    f = sub.find("4");
    ASSERT_NE(f, sub.end());
    EXPECT_EQ(*f, 4);
    EXPECT_EQ(f.key(), "4");
    sub.insert("5", 5);
    f = t.find("25");
    ASSERT_NE(f, t.end());
    EXPECT_EQ(*f, 5);
    EXPECT_EQ(f.key(), "25");
}