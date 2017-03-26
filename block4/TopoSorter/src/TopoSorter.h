//
// Created by moonlightnvkz on 19.03.17.
//

#pragma once
#include <string>
#include <vector>
#include <map>

class TopoSorter {
public:
    using Name = std::string;
    using Dependencies = std::vector<std::string>;

    TopoSorter() { }

    TopoSorter(const std::vector<std::pair<Name, Dependencies>> &nodes);

    TopoSorter(const TopoSorter &that) {
        graph = that.graph;
    }

    TopoSorter(TopoSorter &&that) noexcept {
        graph = std::move(that.graph);
    }

    ~TopoSorter() { }

    TopoSorter &operator=(const TopoSorter &that) {
        graph = that.graph;
        return *this;
    }

    TopoSorter &operator=(TopoSorter &&that) noexcept {
        graph = std::move(that.graph);
        return *this;
    }

    void add_node(const std::pair<Name, Dependencies> & node);

    std::vector<std::string> sort();

private:
    enum class Colors {
        White,
        Gray,
        Black
    };

    std::map<Name, std::pair<Colors, Dependencies>> graph;

    bool dfs(const TopoSorter::Name &name, std::vector<std::string> &res);
};