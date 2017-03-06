//
// Created by moonlightnvkz on 23.02.17.
//

#include <cmath>
#include <algorithm>
#include "MST.h"
#include "DSU.h"

static void make_edges(const points_array_t &points, weighted_edges_array_t &edges) {
    for (auto f = points.begin(); f != points.end(); ++f) {
        for (auto s = f + 1; s != points.end(); ++s) {
            edges.push_back(std::make_pair(
                    sqrt((f->second.first  - s->second.first) * ( f->second.first  - s->second.first) +
                         (f->second.second - s->second.second) * (f->second.second - s->second.second)),
                    std::make_pair(f->first, s->first)
                            )
            );
        }
    }
}

static inline unsigned from_vertex(const weighted_edge_t &edge) {
    return (unsigned) edge.second.first;
}

static inline unsigned to_vertex(const weighted_edge_t &edge) {
    return (unsigned) edge.second.second;
}

weighted_edges_array_t kruskal(size_t points_amount, weighted_edges_array_t &edges) {
    std::sort(edges.begin(), edges.end(), [](weighted_edge_t a, weighted_edge_t b) {
        return a.first < b.first;
    });
    DSU dsu;
    for (size_t i = 1; i <= points_amount; ++i) {
        dsu.add_set(i);
    }
    weighted_edges_array_t res;
    for (auto edge : edges) {
        auto f = from_vertex(edge), s = to_vertex(edge);
        if (dsu.find_set(f) != dsu.find_set(s)) {
            res.push_back(edge);
            dsu.unite_sets(f, s);
        }
    }
    return res;
}

weighted_edges_array_t build(const points_array_t &points) {
    weighted_edges_array_t edges;
    make_edges(points, edges);
    return build(points.size(), edges);
}

weighted_edges_array_t build(size_t points_amount, weighted_edges_array_t &edges) {
    auto res = kruskal(points_amount, edges);

    std::sort(res.begin(), res.end(), [](weighted_edge_t a, weighted_edge_t b) {
        return a.second < b.second;
    });
    return res;
}
