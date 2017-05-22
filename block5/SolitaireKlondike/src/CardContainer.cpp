//
// Created by moonlightnvkz on 08.05.17.
//

#include <stdexcept>
#include "../include/CardContainer.h"

bool CardContainer::push_back(const std::shared_ptr<Card> &card) {
    if (card == nullptr) {
        return true;
    }
    if (is_suitable(card)) {
        cards.push_back(std::move(card));
        card->set_side(Card::eSide::Face);
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

bool CardContainer::is_suitable(const std::shared_ptr<Card> &card) const {
    return true;
}

std::shared_ptr<Card> CardContainer::get_card(size_t idx_from_back) const {
    size_t size = cards.size();
    if (size == 0) {
        return nullptr;
    }
    if (idx_from_back >= size) {
        idx_from_back = size - 1;
    }
    return cards[size - idx_from_back - 1];
}

CardContainer &CardContainer::operator=(const CardContainer &that) {
    if (this != &that) {
        this->cards = that.cards;
    }
    return *this;
}

CardContainer &CardContainer::operator=(CardContainer &&that) {
    if (this != &that) {
        this->cards = that.cards;
    }
    return *this;
}
