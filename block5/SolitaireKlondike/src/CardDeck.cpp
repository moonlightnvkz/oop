//
// Created by moonlightnvkz on 07.05.17.
//

#include <stdexcept>
#include <algorithm>
#include "../include/CardDeck.h"
#include "../include/Waste.h"

CardDeck::CardDeck()
        : waste(nullptr) {
    constexpr const unsigned Amount = 52;
    constexpr const unsigned CPS = 13;  // Cards Per Suit
    for (unsigned i = 0; i < Amount; ++i) {
        cards.push_back(std::make_unique<Card>(static_cast<Card::eSuit>(i / CPS),
                                               static_cast<Card::eRank>(i % CPS)));
    }
    std::random_shuffle(cards.begin(), cards.end());
}

void CardDeck::move_card_to_waste() {
    if (waste == nullptr) {
        throw std::logic_error("waste is nullptr");
    }
    std::unique_ptr<Card> top = back();
    pop_back();
    waste->push_back(std::move(top));
}

bool CardDeck::push_back(std::unique_ptr<Card> &&card) {
    if (card == nullptr) {
        return true;
    }
    if (!CardContainer::push_back(std::move(card))) {
        return false;
    }
    cards.back()->set_side(Card::eSide::Back);
    return true;
}
