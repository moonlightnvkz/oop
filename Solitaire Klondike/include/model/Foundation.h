//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


#include <array>
#include "FoundationStack.h"

class Foundation {
public:
    Foundation() {};

    FoundationStack &get_stack(size_t i) { return stacks.at(i); }

    bool is_complete();

private:
    std::array<FoundationStack, 4> stacks;
};


