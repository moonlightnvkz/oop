//
// Created by moonlightnvkz on 24.04.17.
//

#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include "Timestamp.h"
/*
 * YYYY-MM-DDThh:mm:ss	2005-08-09T18:31:42	9 августа 2005 года 18 часов 31 минута 42 секунды
 */

Timestamp::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Timestamp &ts) {
    os << std::setfill('0');
    return os << ts.years << '-'
              << std::setw(2) << ts.months << '-'
              << std::setw(2) << ts.days << 'T'
              << std::setw(2) << ts.hours << ':'
              << std::setw(2) << ts.minutes << ':'
              << std::setw(2) << ts.seconds;
}

std::istream &operator>>(std::istream &is, Timestamp &ts) {
    // YYYY-MM-DDThh:mm:ss - count = 19
    is >> ts.years;
    is.ignore(1) >> ts.months;
    is.ignore(1) >> ts.days;
    is.ignore(1) >> ts.hours;
    is.ignore(1) >> ts.minutes;
    is.ignore(1) >> ts.seconds;
    return is;
}

bool operator==(const Timestamp &a, const Timestamp &b) {
    return    a.years   == b.years
           && a.months  == b.months
           && a.days    == b.days
           && a.hours   == b.hours
           && a.minutes == b.minutes
           && a.seconds == b.seconds;
}

bool operator<(const Timestamp &a, const Timestamp &b) {
    std::vector<unsigned> av{a.years, a.months, a.days, a.hours, a.minutes, a.seconds};
    std::vector<unsigned> bv{b.years, b.months, b.days, b.hours, b.minutes, b.seconds};
    return std::lexicographical_compare(av.begin(), av.end(),
                                        bv.begin(), bv.end());
}

bool operator>(const Timestamp &a, const Timestamp &b) {
    std::vector<unsigned> av{a.years, a.months, a.days, a.hours, a.minutes, a.seconds};
    std::vector<unsigned> bv{b.years, b.months, b.days, b.hours, b.minutes, b.seconds};
    return std::lexicographical_compare(av.begin(), av.end(),
                                        bv.begin(), bv.end(), std::greater<unsigned>());
}

bool operator<=(const Timestamp &a, const Timestamp &b) {
    return !(a > b);
}

bool operator>=(const Timestamp &a, const Timestamp &b) {
    return !(a < b);
}

double operator-(const Timestamp &a, const Timestamp &b) {
    std::tm atm;
    atm.tm_year = a.years;
    atm.tm_mon = a.months;
    atm.tm_mday = a.days;
    atm.tm_hour = a.hours;
    atm.tm_min = a.minutes;
    atm.tm_sec = a.seconds;
    std::tm btm;
    btm.tm_year = b.years;
    btm.tm_mon = b.months;
    btm.tm_mday = b.days;
    btm.tm_hour = b.hours;
    btm.tm_min = b.minutes;
    btm.tm_sec = b.seconds;

    return difftime(mktime(&atm), mktime(&btm));
}