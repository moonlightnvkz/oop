//
// Created by moonlightnvkz on 07.05.17.
//

#include "../include/Waste.h"
#include "../include/CardDeck.h"

void Waste::move_card_to_deck() {
    if (size() == 0) {
        return;
    }
    const std::shared_ptr<Card> &top = get_card();
    pop_back();
    deck->push_back(top);
}

bool Waste::push_back(const std::shared_ptr<Card> &card) {
    if (card == nullptr) {
        return true;
    }
    if (!CardContainer::push_back(card)) {
        return false;
    }
    cards.back()->set_side(Card::eSide::Face);
    return true;
}
