#include "Pathfinder.h"

using namespace std;


int main()
{
    int row_a, row_b;
    int col_a, col_b;
    bool walls = true;
    cout << "1 - walls, 0 - no walls: ";
    cin >> walls;

    cout << "Insert start point: ";
    cin >> row_a >> col_a;
    cout << "Insert end point: ";
    cin >> row_b >> col_b;

    if(row_a < 1 || row_a > 20 || row_b < 1 || row_b > 20 || col_a < 1 || col_a > 40 || col_b < 1 || col_b > 40)
    {
        cout << "Incorrect input\n";
    }

    Pathfinder path(row_a, col_a, row_b, col_b, walls);

    return 0;
}