//
// Created by moonlightnvkz on 08.04.17.
//

#pragma once
#include <DSU.h>
#include <MST.h>

class GraphSegmentator {
public:
    DSU segmentate(size_t num_vertices, weighted_edges_array_t &edges, double threshold);
};


