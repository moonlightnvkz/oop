//
// Created by moonlightnvkz on 24.04.17.
//

#include <ostream>
#include "../include/User.h"

bool operator==(const User &a, const User &b) {
    return a.id() == b.id() &&
           a.startTs() == b.startTs() &&
           a.endTs() == b.endTs();
}

std::ostream &operator<<(std::ostream &os, const User &user) {
    return os << user.startTs() << " - "
              << user.endTs() << " "
              << user.id() << " ";
}
