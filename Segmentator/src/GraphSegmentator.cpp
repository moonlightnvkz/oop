//
// Created by moonlightnvkz on 08.04.17.
//

#include <algorithm>
#include "GraphSegmentator.h"

DSU GraphSegmentator::segmentate(size_t num_vertices, weighted_edges_array_t &edges, double threshold) {
    std::sort(edges.begin(), edges.end(), [] (const weighted_edge_t &a, const weighted_edge_t &b) {
        return a.first < b.first;
    });

    DSU dsu;
    for (size_t i = 0; i < num_vertices; ++i) {
        dsu.add_set(i);
    }
    std::vector<double> thresholds(num_vertices, threshold);

    size_t num_edges = edges.size();
    for (size_t i = 0; i < num_edges; ++i) {
        const weighted_edge_t &edge = edges[i];

        size_t a = dsu.find_set(edge.second.first);
        size_t b = dsu.find_set(edge.second.second);

        if (a != b) {
            if (edge.first < thresholds[a] && edge.first < thresholds[b]) {
                dsu.unite_sets(a, b);
                a = dsu.find_set(a);
                thresholds[a] = edge.first + threshold / dsu.size(a);
            }
        }
    }
    return dsu;
}
