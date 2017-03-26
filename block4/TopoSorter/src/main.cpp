#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TopoSorter.h"

using sreg_iter = std::sregex_token_iterator;

int main()
{
    std::ifstream is("src/input");

    std::vector<std::pair<TopoSorter::Name , TopoSorter::Dependencies >> nodes;
    std::regex re("(\\s*=\\s*)|(\\s*\\,\\s*)"); // '=' or ',' surrounded with 0 or more spaces

    while (is) {
        std::string in;
        std::getline(is, in);
        if (!is) {
            break;
        }
        std::vector<std::string> result{
                sreg_iter(in.begin(), in.end(), re, -1), sreg_iter()
        };

        auto it = result.begin();
        TopoSorter::Name name{*it++};
        TopoSorter::Dependencies dependencies{it, result.end()};
        nodes.push_back(std::make_pair(name, dependencies));
    }
    TopoSorter topoSorter(nodes);

    std::vector<std::string> res = topoSorter.sort();

    for (const auto &s : res) {
        std::cout << s << std::endl;
    }
}