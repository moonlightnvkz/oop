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
        cards.push_back(Card(static_cast<Card::eSuit>(i / CPS),
                             static_cast<Card::eRank>(i % CPS)));
    }
    std::random_shuffle(cards.begin(), cards.end());
}

void CardDeck::move_card_to_waste() {
    if (waste == nullptr) {
        throw std::logic_error("waste in nullptr");
    }
    Card &top = const_cast<Card&>(back());
    pop_back();
    waste->push_back(top);
}

bool CardDeck::push_back(Card &card) {
    card.set_side(Card::eSide::Back);
    return CardContainer::push_back(card);
}
