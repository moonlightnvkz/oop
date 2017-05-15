//
// Created by moonlightnvkz on 08.05.17.
//

#include "../../include/model/CardContainer.h"
#include "../../include/model/Card.h"

bool CardContainer::push_back(Card &card) {
    if (is_suitable(card)) {
        cards.push_back(card);
        card.set_side(Card::eSide::Face);
        return true;
    }
    return false;
}

void CardContainer::pop_back() {
    if (cards.size() == 0) {
        return;
    }
    cards.pop_back();
}

bool CardContainer::is_suitable(const Card &card) {
    return true;
}

const Card &CardContainer::peek(size_t idx_from_back) {
    size_t size = cards.size();
    if (idx_from_back >= size) {
        throw std::logic_error("There is no cards");
    }
    return cards[size - idx_from_back];
}

const Card &CardContainer::back() const {
    if (cards.size() > 0) {
        return cards.back();
    } else {
        throw std::logic_error("There is no cards");
    }
}
