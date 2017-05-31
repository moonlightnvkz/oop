//
// Created by moonlightnvkz on 07.05.17.
//

#include "../include/Waste.h"
#include "../include/CardDeck.h"

void Waste::move_card_to_deck() {
    if (size() == 0) {
        return;
    }
    std::unique_ptr<Card> top = back();
    pop_back();
    deck->push_back(std::move(top));
}

bool Waste::push_back(std::unique_ptr<Card> &&card) {
    if (card == nullptr) {
        return true;
    }
    if (!CardContainer::push_back(std::move(card))) {
        return false;
    }
    cards.back()->set_side(Card::eSide::Face);
    return true;
}
