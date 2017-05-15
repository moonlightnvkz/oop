//
// Created by moonlightnvkz on 24.04.17.
//

#include <iomanip>
#include <map>
#include "Crowd.h"
#include "User.h"

Crowd::Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
             std::vector<User *> &&users) :
        _location(location), _startTs(startTs), _endTs(endTs), _users(std::move(users)),
        _max_calculated(false), _avg_calculated(false) {
}

Crowd::Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
             const std::vector<User *> &users) :
        _location(location), _startTs(startTs), _endTs(endTs), _users(users),
        _max_calculated(false), _avg_calculated(false) {
}

std::ostream &operator<<(std::ostream &os, Crowd &crowd) {
    os << crowd.location() << std::endl;
    os << '\t' << "Time: " << crowd.startTs() << " - " << crowd.endTs() << std::endl;
    os << '\t' << "Max n. people: " << crowd.max_n() << std::endl;
    os << '\t' << "Avg n. people: " << crowd.avg_n() << std::endl;
    os << '\t' << "User's id: ";
    for (const auto & user : crowd.users()) {
        os << "\t\t" << user->id() << std::endl;
    }
    return os;
}

void Crowd::calc_max() {
    std::map<Timestamp, unsigned> timeline;
    for (const auto &user : _users) {
        timeline[user->startTs()] = 0;
        timeline[user->endTs()] = 0;
    }
    for (const auto &user : _users) {
        const Timestamp &startTs = user->startTs();
        const Timestamp &endTs = user->endTs();
        auto start_it = timeline.find(startTs);
        for (auto it = start_it; it != timeline.end() && it->first <= endTs; ++it) {
            ++it->second;
        }
    }
    _max_n = 0;
    for (const auto moment : timeline) {
        if (moment.second > _max_n) {
            _max_n = moment.second;
        }
    }
    _max_calculated = true;
}

void Crowd::add_user(User *user) {
    _users.push_back(user);
    _avg_calculated = false;
}

unsigned int Crowd::max_n() {
    if (!_max_calculated) {
        calc_max();
    }
    return _max_n;
}

unsigned int Crowd::avg_n() {
    if (!_avg_calculated) {
        calc_avg();
    }
    return _avg_n;
}

static const Timestamp& clamp( const Timestamp& v, const Timestamp& lo, const Timestamp& hi)
{
    return v < lo ? lo : hi < v ? hi : v;
}
void Crowd::calc_avg() {
    double avg = 0;
    double period = _endTs - _startTs;
    for (const auto &user : _users) {
        avg += (clamp(user->endTs(), _startTs, _endTs) - clamp(user->startTs(), _startTs, _endTs)) / period;
    }
    _avg_n = static_cast<unsigned>(avg);
    _avg_calculated = true;
}
