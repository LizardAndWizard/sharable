#pragma once
#include<iostream>
#include <vector>
using namespace std;

class GameOfLife {
public:
    GameOfLife();
    void run();
private:
    const int gridRows = 20;
    const int gridCols = 20;
    vector<vector<bool>> board;

    void printBoard() const;
    int countLiveNeighbors(int row, int col) const;
    void nextGeneration();
};