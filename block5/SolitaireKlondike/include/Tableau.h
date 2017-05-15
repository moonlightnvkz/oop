//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


#include <array>
#include "TableauStack.h"

class Tableau {
public:
    Tableau() { };

    TableauStack &get_stack(size_t i) { return stacks.at(i); }

    void swap_stack(size_t i, size_t j) { std::swap(stacks.at(i), stacks.at(j)); }
private:
    std::array<TableauStack, 7> stacks;
};


