//
// Created by moonlightnvkz on 19.03.17.
//
#include <algorithm>
#include "TopoSorter.h"

TopoSorter::TopoSorter(const std::vector<std::pair<TopoSorter::Name, TopoSorter::Dependencies>> &nodes) {
    for (const auto &node : nodes) {
        add_node(node);
    }
}

void TopoSorter::add_node(const std::pair<TopoSorter::Name, TopoSorter::Dependencies> &node) {
    auto &n = graph[node.first];
    n.first = Colors::White;
    n.second = node.second;
    for (const auto &d : node.second) {
        auto it = graph.find(d);
        if (it == graph.end()) {
            auto &n = graph[d];
            n.first = Colors::White;
            n.second = {};
        }
    }
}

std::vector<std::string> TopoSorter::sort() {
    std::vector<std::string> res;
    for (auto &node : graph) {
        node.second.first = Colors::White;
    }
    for (auto &node : graph) {
        if (!dfs(node.first, res)) {
            return { };
        }
    }
    return res;
}

bool TopoSorter::dfs(const TopoSorter::Name &name, std::vector<std::string> &res) {
    auto &node = graph.at(name);
    switch (node.first) {
        case Colors::Gray: return false;
        case Colors::Black: return true;
        default: node.first = Colors::Gray;
    }
    for (const Name &depend: node.second) {
        if (!dfs(depend, res)) {
            return false;
        }
    }
    res.push_back(name);
    node.first = Colors::Black;
    return true;
}