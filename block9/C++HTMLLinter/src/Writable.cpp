#include <ostream>
#include "../include/Writable.h"

Writable::Writable(const std::string &text)
        : mText(text) {
}

Writable::Writable(std::string &&text)
        : mText(std::move(text)) {
}

bool Writable::write(std::ostream &out) {
    return out << mText ? true : false; // Because CLion static analyzer breaks on this line
}