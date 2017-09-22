//
// Created by moonlightnvkz on 05.09.17.
//

#pragma once

#include <type_traits>

template<bool Expression>
typename std::enable_if<Expression, void>::type STATIC_ASSERT(const char *) {
}