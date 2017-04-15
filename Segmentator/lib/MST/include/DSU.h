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

    size_t size(const size_t s) const {
        return sizes.at(s);
    }

    size_t num_sets() const {
        return num;
    }
private:
    size_t num;
    std::vector<size_t> parents;
    std::vector<size_t> ranks;
    std::vector<size_t> sizes;
};


