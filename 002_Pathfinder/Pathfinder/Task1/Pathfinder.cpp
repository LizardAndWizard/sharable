#include "Pathfinder.h"
using namespace std;

int Pathfinder::get_rnd(double chance_of_1)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

    double random_value = dis(gen);

    if (random_value < chance_of_1) {
        return 1;
    }
    else {
        return 0;
    }
}

Pathfinder::Pathfinder(int row_a, int col_a, int row_b, int col_b, bool walls)
{
    this->row_a = row_a;
    this->col_a = col_a;
    this->row_b = row_b;
    this->col_b = col_b;
    this->walls = walls;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == row_a - 1 && j == col_a - 1) || (i == row_b - 1 && j == col_b - 1)) {
                map[i][j] = 0;
            }
            else if (walls)
            {
                map[i][j] = get_rnd(0.25);
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }

    adjacency_list_t adjacency_list(rows * cols + 1); 

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == 1) {
                continue;
            }
            if (i > 0 && map[i - 1][j] != 1) {
                adjacency_list[i * cols + j].push_back(neighbor((i - 1) * cols + j, 1));  // Connect to the above cell
            }
            if (j > 0 && map[i][j - 1] != 1) {
                adjacency_list[i * cols + j].push_back(neighbor(i * cols + j - 1, 1));  // Connect to the left cell
            }
            if (j < cols - 1 && map[i][j + 1] != 1) {
                adjacency_list[i * cols + j].push_back(neighbor(i * cols + j + 1, 1));  // Connect to the right cell
            }
            if (i < rows - 1 && map[i + 1][j] != 1) {
                adjacency_list[i * cols + j].push_back(neighbor((i + 1) * cols + j, 1));  // Connect to the below cell
            }
        }
    }

    if (walls)
    {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (map[i][j] == 1) {
                    adjacency_list[rows * cols].push_back(neighbor(i * cols + j, max_weight));
                }
            }
        }
    }

    vector<weight_t> min_distance;
    vector<vertex_t> previous;
    DijkstraComputePaths((row_a - 1) * cols + col_a - 1, adjacency_list, min_distance, previous);
    list<vertex_t> path = DijkstraGetShortestPathTo((row_b - 1) * cols + col_b - 1, previous);
    list<vertex_t> adjusted_path = path;

    drawMap(adjusted_path, map, row_a, col_a, row_b, col_b);
    Sleep(100);

    for (const vertex_t& vertex : adjusted_path)
    {
        int row = vertex / cols;
        int col = vertex % cols;
        map[row][col] = 2;
        drawMap(adjusted_path, map, row_a, col_a, row_b, col_b);
        Sleep(100);
    }
}

void Pathfinder::DijkstraComputePaths(vertex_t source, const adjacency_list_t& adjacency_list, vector<weight_t>& min_distance, vector<vertex_t>& previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    set<pair<weight_t, vertex_t>> vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        const vector<neighbor>& neighbors = adjacency_list[u];
        for (const neighbor& neighbor_iter : neighbors)
        {
            vertex_t v = neighbor_iter.target;
            weight_t weight = neighbor_iter.weight;

            if (weight == max_weight)
                continue;

            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v])
            {
                vertex_queue.erase(make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(make_pair(min_distance[v], v));
            }
        }
    }
}

list<vertex_t> Pathfinder::DijkstraGetShortestPathTo(vertex_t vertex, const vector<vertex_t>& previous)
{
    list<vertex_t> path;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

void Pathfinder::drawMap(const list<vertex_t>& adjusted_path, int map[20][40], int row_a, int col_a, int row_b, int col_b)
{
    system("cls");
    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 40; ++j)
        {
            if (i == row_a - 1 && j == col_a - 1)
                cout << 'S';
            else if (i == row_b - 1 && j == col_b - 1)
                cout << 'E';
            else if (map[i][j] == 1)
                cout << '@';
            else if (map[i][j] == 2)
                cout << '+';
            else
                cout << '/';
        }
        cout << endl;
    }
}