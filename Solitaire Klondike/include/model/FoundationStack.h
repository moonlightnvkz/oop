//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once

#include <vector>
#include "CardContainer.h"

class FoundationStack :public CardContainer{
public:
    virtual ~FoundationStack() {};

    virtual bool is_suitable(const Card &card) override;
};


