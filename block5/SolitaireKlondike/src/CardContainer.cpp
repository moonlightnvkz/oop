//
// Created by moonlightnvkz on 08.05.17.
//

#include <stdexcept>
#include "../include/CardContainer.h"

bool CardContainer::push_back(std::unique_ptr<Card> &&card) {
    if (card == nullptr) {
        return true;
    }
    if (is_suitable(card.get())) {
        card->set_side(Card::eSide::Face);
        cards.push_back(std::move(card));
        return true;
    }
    return false;
}

std::unique_ptr<Card> CardContainer::back() {
    std::unique_ptr<Card> res = cards.size() > 0 ?
                                std::move(cards.back()) : std::move(std::unique_ptr<Card>(nullptr));
    //pop_back();
    return std::move(res);
}

void CardContainer::pop_back() {
    if (cards.size() == 0) {
        return;
    }
    cards.pop_back();
}

bool CardContainer::is_suitable(const Card *card) const {
    return true;
}

const Card *CardContainer::peek_card(size_t idx_from_back) const {
    size_t size = cards.size();
    if (size == 0) {
        return nullptr;
    }
    if (idx_from_back >= size) {
        idx_from_back = size - 1;
    }
    return cards[size - idx_from_back - 1].get();
}

CardContainer &CardContainer::operator=(CardContainer &&that) {
    if (this != &that) {
        this->cards = std::move(that.cards);
    }
    return *this;
}
