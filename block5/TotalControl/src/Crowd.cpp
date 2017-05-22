//
// Created by moonlightnvkz on 24.04.17.
//

#include <iomanip>
#include <map>
#include "../include/Crowd.h"
#include "../include/User.h"

Crowd::Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
             std::vector<std::shared_ptr<User>> &&users) :
        location_(location), startTs_(startTs), endTs_(endTs), users_(std::move(users)),
        max_calculated_(false), avg_calculated_(false) {
}

Crowd::Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
             const std::vector<std::shared_ptr<User>> &users) :
        location_(location), startTs_(startTs), endTs_(endTs), users_(users),
        max_calculated_(false), avg_calculated_(false) {
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
    for (const auto &user : users_) {
        timeline[user->startTs()] = 0;
        timeline[user->endTs()] = 0;
    }
    for (const auto &user : users_) {
        const Timestamp &startTs = user->startTs();
        const Timestamp &endTs = user->endTs();
        auto start_it = timeline.find(startTs);
        for (auto it = start_it; it != timeline.end() && it->first <= endTs; ++it) {
            ++it->second;
        }
    }
    max_n_ = 0;
    for (const auto moment : timeline) {
        if (moment.second > max_n_) {
            max_n_ = moment.second;
        }
    }
    max_calculated_ = true;
}

void Crowd::add_user(std::shared_ptr<User> user) {
    users_.push_back(user);
    avg_calculated_ = false;
}

unsigned int Crowd::max_n() {
    if (!max_calculated_) {
        calc_max();
    }
    return max_n_;
}

unsigned int Crowd::avg_n() {
    if (!avg_calculated_) {
        calc_avg();
    }
    return avg_n_;
}

static const Timestamp& clamp( const Timestamp& v, const Timestamp& lo, const Timestamp& hi)
{
    return v < lo ? lo : hi < v ? hi : v;
}
void Crowd::calc_avg() {
    double avg = 0;
    double period = endTs_ - startTs_;
    for (const auto &user : users_) {
        avg += (clamp(user->endTs(), startTs_, endTs_) - clamp(user->startTs(), startTs_, endTs_)) / period;
    }
    avg_n_ = static_cast<unsigned>(avg);
    avg_calculated_ = true;
}

