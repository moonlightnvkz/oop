//
// Created by moonlightnvkz on 05.09.17.
//

#pragma once

#include <cstddef>
#include <utility>
#include <vector>
#include <memory>
#include <numeric>
#include <algorithm>
#include <random>
#include <iterator>

template<typename Iterator>
class shuffle_range {
public:
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;

    // Uses mt19937
    shuffle_range(Iterator begin, Iterator end)
            : mFirst(begin), mLast(end), mOrder(static_cast<unsigned long>(std::distance(begin, end))) {
        std::iota(mOrder.begin(), mOrder.end(), 0);
        std::shuffle(mOrder.begin(), mOrder.end(), std::mt19937(std::random_device{}()));
    }

    template<typename URNG>
    shuffle_range(Iterator begin, Iterator end, URNG &&g)
            : mFirst(begin), mLast(end), mOrder(static_cast<unsigned long>(std::distance(begin, end))) {
        std::iota(mOrder.begin(), mOrder.end(), 0);
        std::shuffle(mOrder.begin(), mOrder.end(), std::forward<URNG>(g));
    }

    virtual ~shuffle_range() = default;

    //
    // <shuffle_iterator>
    //
    class shuffle_iterator :
            public std::iterator<std::forward_iterator_tag, shuffle_range<Iterator>> {
    public:
        virtual ~shuffle_iterator() = default;

        shuffle_iterator& operator++() {
            ++mCurrentOrder;
            mCurrent = mFirst;
            std::advance(mCurrent, *mCurrentOrder);
            return *this;
        }

        Iterator operator*() {
            return mCurrent;
        }

        Iterator* operator->() {
            return &mCurrent;
        }

        bool operator==(const shuffle_iterator &rhs) {
            return mCurrentOrder == rhs.mCurrentOrder &&
                   mFirst == rhs.mFirst &&
                   mCurrent == rhs.mCurrent;
        }

        bool operator!=(const shuffle_iterator &rhs) {
            return !(*this == rhs);
        }

    private:
        using OrderItType = typename std::vector<difference_type>::iterator;
        shuffle_iterator(OrderItType order, Iterator first)
                : mCurrentOrder(std::move(order)), mFirst(first), mCurrent(first) {
            std::advance(mCurrent, *mCurrentOrder);
        }

        OrderItType mCurrentOrder;

        Iterator mFirst;

        Iterator mCurrent;

        friend class shuffle_range<Iterator>;
    };
    //
    //  </shuffle_iterator>
    //

    shuffle_iterator begin() {
        return shuffle_iterator(mOrder.begin(), mFirst);
    }

    shuffle_iterator end() {
        return shuffle_iterator(mOrder.end(), mFirst);
    }

protected:
    Iterator mFirst;

    Iterator mLast;

    std::vector<difference_type> mOrder;
};

template<typename Iterator>
shuffle_range<Iterator> make_shuffle(Iterator first, Iterator last) {
    return shuffle_range(first, last);
}

template<typename Iterator, typename URNG>
shuffle_range<Iterator> make_shuffle(Iterator first, Iterator last, URNG &&g) {
    return shuffle_range(first, last, std::forward<URNG>(g));
}