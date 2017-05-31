//
// Created by moonlightnvkz on 08.05.17.
//

#include <cstddef>
#include "../include/FoundationStack.h"

bool FoundationStack::is_suitable(const Card *card) const {
    const Card *top = peek_card();
    if (card == nullptr) {
        return true;
    }
    if (top == nullptr) {
        return card->get_rank() == Card::eRank::Ace;
    }
    return static_cast<size_t>(top->get_rank()) == static_cast<size_t>(card->get_rank()) - 1
           && top->get_suit() == card->get_suit();
}

FoundationStack &FoundationStack::operator=(FoundationStack &&that) {
    if (this != &that) {
        this->cards = std::move(that.cards);
    }
    return *this;
}
