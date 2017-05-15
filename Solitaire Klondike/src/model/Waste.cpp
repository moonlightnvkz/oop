//
// Created by moonlightnvkz on 07.05.17.
//

#include "../../include/model/Waste.h"
#include "../../include/model/CardDeck.h"
#include "../../include/model/Card.h"

void Waste::move_card_to_deck() {
    if (size() == 0) {
        return;
    }
    Card &top = const_cast<Card&>(back());
    pop_back();
    deck->push_back(top);
}

bool Waste::push_back(Card &card) {
    card.set_side(Card::eSide::Face);
    return CardContainer::push_back(card);
}
