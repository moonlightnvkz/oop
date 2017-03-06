//
// Created by moonlightnvkz on 23.02.17.
//

#pragma once

#include <vector>
#include <cstddef>

// точка с №... и координатами на плоскости (..., ...)
typedef std::pair<int, std::pair<int, int>> point_t;

// ребро между точками №... и №...
typedef std::pair<size_t, size_t> edge_t;

// ребро с весом ... между точками №... и №...
typedef std::pair<double, std::pair<size_t, size_t>> weighted_edge_t;

typedef std::vector<point_t> points_array_t;

typedef std::vector<weighted_edge_t> weighted_edges_array_t;


// Ищет путь в полном графе, построенном по вершинам points
weighted_edges_array_t build(const points_array_t& points);

// Путь в заданном графе
weighted_edges_array_t build(size_t points_amount, weighted_edges_array_t &edges);