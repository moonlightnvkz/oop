//
// Created by moonlightnvkz on 09.05.17.
//

#include "../../include/controller/Controller.h"

Controller::Controller()
        : waste(&deck) {

}

void Controller::turn_deck() {
    deck.move_card_to_waste();
}

void Controller::turn_waste() {
    waste.move_card_to_deck();
}

void Controller::card_from_waste_is_taken() {
    card_origin = std::bind(&Controller::take_card_from_waste, this);
}

void Controller::card_from_tableau_is_taken(unsigned i) {
    card_origin = std::bind(&Controller::take_card_from_tableau, this, i);
}

void Controller::tableau_stack_tale_is_taken(unsigned i, int amount) {
    stack_origin = std::bind(&Controller::take_tableau_stack_tale, this, i, amount);
}

Card Controller::take_card_from_waste() {
    Card top = waste.back();
    waste.pop_back();
    return top;
}

Card Controller::take_card_from_tableau(unsigned i) {
    TableauStack &stack = tableau.get_stack(i);
    Card top = stack.back();
    stack.pop_back();
    return top;
}

TableauStack Controller::take_tableau_stack_tale(unsigned i, int amount) {
    TableauStack stack = tableau.get_stack(i);
    if (amount < 0) {
        return stack;
    }
    TableauStack tale = stack.tale(static_cast<size_t>(amount));
    stack.pop_tale(static_cast<size_t>(amount));
    return tale;
}

void Controller::clear_origins() {
    card_origin = nullptr;
    stack_origin = nullptr;
}

bool Controller::put_card_to_tableau_stack(Card &card, unsigned j) {
    if (!card_origin) {
        throw std::logic_error("No cards have been taken");
    }
    return tableau.get_stack(j).push_back(card);
}

bool Controller::put_card_to_foundation_stack(Card &card, unsigned j) {
    if (!card_origin) {
        throw std::logic_error("No cards have been taken");
    }
    return foundation.get_stack(j).push_back(card);
}

bool Controller::put_tableau_stack(const TableauStack &stack, unsigned j) {
    if (!stack_origin) {
        throw std::logic_error("No stack has been taken");
    }
    return tableau.get_stack(j).push_back(stack);
}

void Controller::release_back() {
    clear_origins();
}
