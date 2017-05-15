//
// Created by moonlightnvkz on 07.05.17.
//

#include "../include/Foundation.h"

bool Foundation::is_complete() {
    for(const auto stack : stacks) {
        if (stack.back().get_rank() != Card::eRank::King) {
            return false;
        }
    }
    return true;
}
