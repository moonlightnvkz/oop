//
// Created by moonlightnvkz on 24.04.17.
//

#pragma once

#include <string>
#include <ctime>
/*
 * YYYY-MM-DDThh:mm:ss	2005-08-09T18:31:42	9 августа 2005 года 18 часов 31 минута 42 секунды
 */

struct Timestamp {
    unsigned years;
    unsigned months;
    unsigned days;
    unsigned hours;
    unsigned minutes;
    unsigned seconds;

    explicit operator std::string() const;

    friend std::ostream &operator<<(std::ostream &os, const Timestamp &ts);

    friend std::istream &operator>>(std::istream &is, Timestamp &ts);

    friend bool operator==(const Timestamp &a, const Timestamp &b);

    friend bool operator<(const Timestamp &a, const Timestamp &b);

    friend bool operator>(const Timestamp &a, const Timestamp &b);

    friend bool operator<=(const Timestamp &a, const Timestamp &b);

    friend bool operator>=(const Timestamp &a, const Timestamp &b);

    friend double operator-(const Timestamp &a, const Timestamp &b);
};

std::ostream &operator<<(std::ostream &os, const Timestamp &ts);

std::istream &operator>>(std::istream &is, Timestamp &ts);

bool operator==(const Timestamp &a, const Timestamp &b);

bool operator<(const Timestamp &a, const Timestamp &b);

bool operator<(const Timestamp &a, const Timestamp &b);

bool operator>=(const Timestamp &a, const Timestamp &b);

bool operator>(const Timestamp &a, const Timestamp &b);

double operator-(const Timestamp &a, const Timestamp &b);