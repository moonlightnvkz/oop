//
// Created by moonlightnvkz on 23.02.17.
//

#pragma once

#include <vector>
#include <unordered_map>

class DSU {
public:
    void add_set(const size_t s);

    size_t find_set(const size_t s);

    void unite_sets(size_t s1, size_t s2);

private:
    std::vector<size_t> parents;
    std::vector<size_t> ranks;

    DSU& operator=(const DSU&) = delete;
    DSU& operator=(const DSU&&) = delete;
};


