//
// Created by moonlightnvkz on 07.05.17.
//

#include "../include/Foundation.h"

bool Foundation::is_complete() const {
    for(const auto &stack : stacks) {
        const Card *card = stack.peek_card();
        if (card == nullptr || card->get_rank() != Card::eRank::King) {
            return false;
        }
    }
    return true;
}

Foundation &Foundation::operator=(Foundation &&that) {
    if (this != &that) {
        this->stacks = std::move(that.stacks);
    }
    return *this;
}
