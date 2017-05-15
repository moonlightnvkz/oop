//
// Created by moonlightnvkz on 09.05.17.
//

#pragma once


#include <iterator>
class Card;

class CardContainerIterator {
public:
    using difference_type = typename std::iterator<std::random_access_iterator_tag, Card*>::difference_type;

    CardContainerIterator() : _ptr(nullptr) {}
    CardContainerIterator(Card** rhs) : _ptr(rhs) {}
    CardContainerIterator(const CardContainerIterator &rhs) : _ptr(rhs._ptr) {}
    inline CardContainerIterator& operator+=(difference_type rhs) {_ptr += rhs; return *this;}
    inline CardContainerIterator& operator-=(difference_type rhs) {_ptr -= rhs; return *this;}
    inline Card*& operator*() const {return *_ptr;}
    inline Card** operator->() const {return _ptr;}
    inline Card*& operator[](difference_type rhs) const {return _ptr[rhs];}

    inline CardContainerIterator& operator++() {++_ptr; return *this;}
    inline CardContainerIterator& operator--() {--_ptr; return *this;}
    inline CardContainerIterator operator++(int) {CardContainerIterator tmp(*this); ++_ptr; return tmp;}
    inline CardContainerIterator operator--(int) {CardContainerIterator tmp(*this); --_ptr; return tmp;}
    inline difference_type operator-(const CardContainerIterator& rhs) const {return _ptr-rhs._ptr;}
    inline CardContainerIterator operator+(difference_type rhs) const {return CardContainerIterator(_ptr+rhs);}
    inline CardContainerIterator operator-(difference_type rhs) const {return CardContainerIterator(_ptr-rhs);}
    friend inline CardContainerIterator operator+(difference_type lhs, const CardContainerIterator& rhs) {return CardContainerIterator(lhs+rhs);}
    friend inline CardContainerIterator operator-(difference_type lhs, const CardContainerIterator& rhs) {return CardContainerIterator(lhs-rhs);}

    inline bool operator==(const CardContainerIterator& rhs) const {return _ptr == rhs._ptr;}
    inline bool operator!=(const CardContainerIterator& rhs) const {return _ptr != rhs._ptr;}
    inline bool operator>(const CardContainerIterator& rhs) const {return _ptr > rhs._ptr;}
    inline bool operator<(const CardContainerIterator& rhs) const {return _ptr < rhs._ptr;}
    inline bool operator>=(const CardContainerIterator& rhs) const {return _ptr >= rhs._ptr;}
    inline bool operator<=(const CardContainerIterator& rhs) const {return _ptr <= rhs._ptr;}
private:
    Card** _ptr;
};


