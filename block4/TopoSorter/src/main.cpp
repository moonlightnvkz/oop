#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "TopoSorter.h"

using Name = TopoSorter::Name;
using Dependencies = TopoSorter::Dependencies;

int main()
{
    std::ifstream is("src/input");

    TopoSorter topoSorter(is);

    std::vector<std::string> res = topoSorter.sort();

    for (const auto &s : res) {
        std::cout << s << std::endl;
    }
}