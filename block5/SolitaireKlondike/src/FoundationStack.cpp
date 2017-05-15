//
// Created by moonlightnvkz on 08.05.17.
//

#include <cstddef>
#include "../include/FoundationStack.h"

bool FoundationStack::is_suitable(const Card &card) {
    if (cards.empty()) {
        return card.get_rank() == Card::eRank::Ace;
    }
    const Card &top = back();
    return static_cast<size_t>(top.get_rank()) == static_cast<size_t>(card.get_rank()) - 1
                 && top.get_suit() == card.get_suit();

}
