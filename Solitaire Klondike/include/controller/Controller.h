//
// Created by moonlightnvkz on 09.05.17.
//

#pragma once


#include <functional>
#include "../model/CardDeck.h"
#include "../model/Waste.h"
#include "../model/Foundation.h"
#include "../model/Tableau.h"

class Controller {
public:
    Controller();   // FIXME: pass view to the constructor. Make interface.

    void turn_deck();

    void turn_waste();

    void card_from_waste_is_taken();

    void card_from_tableau_is_taken(unsigned i);

    // if amount < 0 take the full stack
    void tableau_stack_tale_is_taken(unsigned i, int amount = -1);

    bool put_card_to_tableau_stack(Card &card, unsigned j);

    bool put_card_to_foundation_stack(Card &card, unsigned j);

    bool put_tableau_stack(const TableauStack &stack, unsigned j);

    void release_back();
private:

    Card take_card_from_waste();

    Card take_card_from_tableau(unsigned i);

    // if amount < 0 take the full stack
    TableauStack take_tableau_stack_tale(unsigned i, int amount = -1);

    void clear_origins();

    /*
     * View
     */

    CardDeck deck;

    Waste waste;

    Foundation foundation;

    Tableau tableau;

    std::function<const Card &(void)> card_origin;

    std::function<const TableauStack &(void)> stack_origin;
};


