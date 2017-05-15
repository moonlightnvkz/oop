//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


#include <vector>
#include "CardContainer.h"

class CardDeck;

class Waste : public CardContainer{
public:
    Waste(CardDeck *deck) : deck(deck) {};

    void move_card_to_deck();

    virtual bool push_back(Card &card) override;
private:
    CardDeck *deck;
};


