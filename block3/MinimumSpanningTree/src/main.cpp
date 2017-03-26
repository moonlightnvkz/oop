#include <iostream>
#include <fstream>
#include <vector>
#include "MST.h"

using namespace std;

int main() {
    ifstream in("input");
    ofstream out("output");

    vector<point_t> points;
    while (!in.eof()) {
        char delim;
        int id, x, y;
        in >> id >> delim >> x >> delim >> y;
        points.push_back(make_pair(id, make_pair(x, y)));
    }

    weighted_edges_array_t res = build(points);
    for (const auto& point : res) {
        out << point.second.first << " - " << point.second.second << endl;
    }
    return 0;
}