#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <windows.h>
#include <limits>
#include <set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <random>

using namespace std;

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight) : target(arg_target), weight(arg_weight) {}
};

typedef vector<vector<neighbor>> adjacency_list_t;

class Pathfinder
{
private:
    bool walls = true;
    unsigned static const int rows = 20;
    unsigned static const int cols = 40;
    int map[rows][cols];
    int row_a, row_b;
    int col_a, col_b;
    list<vertex_t> path;
    int get_rnd(double chance_of_1);
    void DijkstraComputePaths(vertex_t source, const adjacency_list_t& adjacency_list, vector<weight_t>& min_distance, vector<vertex_t>& previous);
    list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const vector<vertex_t>& previous);
public:
    Pathfinder(int row_a, int col_a, int row_b, int col_b, bool walls);
    void drawMap(const list<vertex_t>& adjusted_path, int map[20][40], int row_a, int col_a, int row_b, int col_b);
};
