//
// Created by moonlightnvkz on 08.05.17.
//

#include <cstddef>
#include "../include/TableauStack.h"

bool TableauStack::push_back(const TableauStack &stack) {
    const std::vector<Card> cards = stack.get_cards();
    if (size() > 0 && is_suitable(cards[0])) {
        for (const auto &c : cards) {
            this->cards.push_back(c);
        }
        return true;
    }
    return false;
}

bool TableauStack::is_suitable(const Card &card) {
    if (cards.empty()) {
        return card.get_rank() == Card::eRank::King;
    }
    const Card &top = back();
    return static_cast<size_t>(top.get_rank()) == static_cast<size_t>(card.get_rank()) + 1
           && top.is_black() != card.is_black();
}

void TableauStack::pop_tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    for (size_t i = 0; i < amount; ++i) {
        cards.pop_back();
    }
}

void TableauStack::pop_back() {
    CardContainer::pop_back();
    if (cards.size() > 0) {
        cards.back().set_side(Card::eSide::Face);
    }
}

TableauStack TableauStack::tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    return TableauStack(std::vector<Card>(cards.end() - amount, cards.end()));
}
