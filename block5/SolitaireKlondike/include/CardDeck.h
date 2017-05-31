//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once

#include <vector>
#include "CardContainer.h"

class Waste;

class CardDeck : public CardContainer{
public:
    CardDeck();

    ~CardDeck() { };

    void set_waste(Waste *waste) { this->waste = waste; }

    void move_card_to_waste();

    virtual bool push_back(std::unique_ptr<Card> &&card) override;

private:
    Waste *waste;
};


