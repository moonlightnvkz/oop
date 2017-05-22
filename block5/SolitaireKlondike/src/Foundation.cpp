//
// Created by moonlightnvkz on 07.05.17.
//

#include "../include/Foundation.h"

bool Foundation::is_complete() const {
    for(const auto &stack : stacks) {
        std::shared_ptr<Card> card = stack.get_card(0);
        if (card == nullptr || card->get_rank() != Card::eRank::King) {
            return false;
        }
    }
    return true;
}

Foundation &Foundation::operator=(const Foundation &that) {
    if (this != &that) {
        this->stacks = that.stacks;
    }
    return *this;
}

Foundation &Foundation::operator=(const Foundation &&that) {
    if (this != &that) {
        this->stacks = std::move(that.stacks);
    }
    return *this;
}
