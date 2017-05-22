//
// Created by moonlightnvkz on 29.04.17.
//

#include <map>
#include "../include/CrowdFinder.h"
#include "../include/Crowd.h"
#include "../include/User.h"
#include "../include/Location.h"

static bool time_interval_intersects(const Timestamp &start1, const Timestamp &end1,
                                     const Timestamp &start2, const Timestamp &end2) {
    return start1 <= end2 && end1 >= start2;
}

std::vector<Crowd> CrowdFinder::find(const std::vector<Location> &list) {
    std::vector<Crowd> crowds;
    for (const auto &loc : list) {
        std::map<Timestamp, std::pair<int, int>> timeline;    // <Timestamp, amount, derivate>
        const std::vector<std::shared_ptr<User>> &users = loc.users();
        for (const auto &user : users) {
            timeline[user->startTs()] = {0, 0};
            timeline[user->endTs()] = {0, 0};
        }
        for (const auto &user : users) {
            const Timestamp &startTs = user->startTs();
            const Timestamp &endTs = user->endTs();
            auto start_it = timeline.find(startTs);
            ++start_it->second.second;
            --timeline.find(endTs)->second.second;
            for (auto it = start_it; it != timeline.end() && it->first <= endTs; ++it) {
                ++it->second.first;
            }
        }

        Timestamp startTs, endTs;
        std::vector<std::shared_ptr<User>> users_in_crowd;
        bool flag = false;
        for (auto it = timeline.begin(); it != timeline.end(); ++it) {
            if (!flag && it->second.first >= critical_amount_) {
                startTs = it->first;
                flag = true;
            }
            if (flag && (it->second.first + it->second.second < critical_amount_ || it == std::prev(timeline.end()))) {
                endTs = it->first;
                for (const auto &user : users) {
                    if (time_interval_intersects(startTs, endTs, user->startTs(), user->endTs())) {
                        users_in_crowd.push_back(user);
                    }
                }
                crowds.push_back(Crowd(loc.name(), startTs, endTs, std::move(users_in_crowd)));
                flag = false;
            }
        }
    }
    return crowds;
}
