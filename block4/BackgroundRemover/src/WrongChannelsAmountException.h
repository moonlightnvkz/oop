//
// Created by moonlightnvkz on 17.04.17.
//

#pragma once
#include <exception>

class WrongChannelsAmountException : public std::exception {
public:
    virtual const char *what() const noexcept override {
        return std::exception::what();
    };

    virtual ~WrongChannelsAmountException() override {};
};


