#include "GameOfLife.h"

GameOfLife::GameOfLife()
{
    srand(time(nullptr));

    for (int i = 0; i < gridRows; i++)
    {
        board.push_back(vector<bool>(gridCols));
        for (int j = 0; j < gridCols; j++)
        {
            board[i][j] = rand() % 2 == 0;
        }
    }
}

void GameOfLife::run()
{
    int genCount = 0;

    while (true) {
        cout << "Generation " << genCount << ": " << endl;
        printBoard();

        int choice;
        cout << "1- next generation, 0 - quit" << endl;
        cin >> choice;

        if (choice)
        {
            nextGeneration();
        }
        else
        {
            break;
        }
        genCount++;
    }
}

void GameOfLife::printBoard() const
{
    for (int i = 0; i < gridRows; i++)
    {
        for (int j = 0; j < gridCols; j++)
        {
            cout << (board[i][j] ? "X" : "*");
        }
        cout << endl;
    }
}

int GameOfLife::countLiveNeighbors(int row, int col) const
{
    int count = 0;

    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            if (i >= 0 && i < gridRows && j >= 0 && j < gridCols && !(i == row && j == col))
            {
                if (board[i][j])
                {
                    count++;
                }
            }
        }
    }

    return count;
}

void GameOfLife::nextGeneration()
{
    vector<vector<bool>> newBoard(gridRows, vector<bool>(gridCols));

    for (int i = 0; i < gridRows; i++)
    {
        for (int j = 0; j < gridCols; j++)
        {
            int liveNeighbors = countLiveNeighbors(i, j);
            if (board[i][j])
            {
                if (liveNeighbors == 2 || liveNeighbors == 3) {
                    newBoard[i][j] = true;
                }
            }
        }
    }
    board = newBoard;
}