//
// Created by akarpovskii on 11.09.17.
//

#pragma once

#include <type_traits>
#include <iterator>
#include <algorithm>

namespace radix_sort {
    template <class RandomAccessIterator, class Compare>
    typename std::enable_if<!std::is_integral<std::iterator_traits<RandomAccessIterator>::value_type>::value, void>::type
    sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        std::sort(first, last, comp);
    };

//    template<typename RandomAccessIterator, typename Compare, bool IsIntegral>
//    void sort_
}