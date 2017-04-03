//
// Created by moonlightnvkz on 19.03.17.
//

#pragma once
#include <string>
#include <vector>
#include <map>
#include <istream>

class TopoSorter {
public:
    using Name = std::string;
    using Dependencies = std::vector<std::string>;
    using Node = std::pair<Name, Dependencies>;

    TopoSorter() { }

    TopoSorter(std::istream &is);

    TopoSorter(const std::vector<Node> &nodes);

    ~TopoSorter() { }

    void add_node(const Node &node);

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