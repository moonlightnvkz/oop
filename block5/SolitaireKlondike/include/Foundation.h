//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


#include <array>
#include "FoundationStack.h"

class Foundation {
public:
    Foundation() { }

    virtual ~Foundation() { }

    Foundation(Foundation &&foundation) : stacks(std::move(foundation.stacks)) { }

    FoundationStack &get_stack(size_t i) { return stacks.at(i); }

    bool is_complete() const;

    Foundation &operator=(Foundation &&that);

private:
    std::array<FoundationStack, 4> stacks;
};


